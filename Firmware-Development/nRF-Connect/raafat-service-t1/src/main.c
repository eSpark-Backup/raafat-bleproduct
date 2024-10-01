#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <stdlib.h>

/*GPIO Inlcudes*/
#include <zephyr/drivers/gpio.h>
#include <hal/nrf_gpio.h>

#define LOG_LEVEL 4
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main);

/* raafat includes */
#include "raafat_service.h"
#include "raafat_json.h"
#include "raafat_data.h"
#include "raafat_adc.h"
#include "raafat_bmm150.h"
#include "raafat_rgb.h"
#include "bmi323.h"

#include "bq27426.h"

/*Defines*/
#define RAAFAT_GPIO_CLR_PWR NRF_GPIO_PIN_MAP(0,20)  //CLR POWER

/* Global declarations */
raafat_data_t* raafat_data = NULL;

// #define I2C0_NODE DT_NODELABEL(fuel_guage)
// static const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(I2C0_NODE);

// Set BATTERY_CAPACITY to the design capacity of your battery.
const unsigned int BATTERY_CAPACITY = 400; // e.g. 850mAh battery

void setupBQ27441(void)
{
  // Use lipo.begin() to initialize the BQ27441-G1A and confirm that it's
  // connected and communicating.
  if (begin()) // begin() will return true if communication is successful
  {
	// If communication fails, print an error message and loop forever.
    printk("Error: Unable to communicate with BQ27441.");
    printk("  Check wiring and try again.");
    printk("  (Battery must be plugged into Battery Babysitter!)");
    while (1) ;
  }
  printk("Connected to BQ27441!");
  
  // Uset lipo.setCapacity(BATTERY_CAPACITY) to set the design capacity
  // of your battery.
  setCapacity(BATTERY_CAPACITY);
}

void printBatteryStats()
{
  // Read battery stats from the BQ27441-G1A
//   unsigned int soc = soc(UNFILTERED); // Read state-of-charge (%)
  unsigned int volts = voltage(); // Read battery voltage (mV)
  int current = bq_current(AVG); // Read average current (mA)
  unsigned int fullCapacity = capacity(FULL); // Read full capacity (mAh)
//   unsigned int capacity = lcapacity(REMAIN); // Read remaining capacity (mAh)
  int power = bq_power(); // Read average power draw (mW)
  int health = soh(PERCENT); // Read state-of-health (%)

//   // Now print out those values:
//   String toPrint = String(soc) + "% | ";
//   toPrint += String(volts) + " mV | ";
//   toPrint += String(current) + " mA | ";
//   toPrint += String(capacity) + " / ";
//   toPrint += String(fullCapacity) + " mAh | ";
//   toPrint += String(power) + " mW | ";
//   toPrint += String(health) + "%";
  
  printk("\nBattery voltage %d mv, state of health %d, capacitiy %d, avg_current %d, power consumption %d mw\n", volts, health, fullCapacity, current, power);
  if(current > 0)
  {
    printk("Charging\n");
  }
  else
  {
    printk("Not Charging\n");
  }
}

int main(void)
{
    /*config CLR_PWR as output and set high so that MCU powers up*/
    // nrf_gpio_cfg_output(RAAFAT_GPIO_CLR_PWR);
    // nrf_gpio_pin_set(RAAFAT_GPIO_CLR_PWR);

	printk("Raafat Hello World! READING FUEL GUAGE\n");

    // uint8_t fuel_guage_read_buf[4] = {0};
    // unsigned int fuel_guage_read_buf = 0;
    setupBQ27441();

    /* allocate memory for storing raafat data */
    raafat_data = (raafat_data_t*)malloc(sizeof(struct raafat_data_s));

    /* Raafat BLE service initialization*/
	raafat_service_init();
    raafat_adc_init();
    raafat_bmm150_init();
	raafat_rgb_init(raafat_data);
    bmi323_init(raafat_data);

    raafat_data->raafat_json_packet = raafat_service_get_json_packet_ptr();

    /* read adc, bmm150, bmi323 and store in raafat data before stringify*/
    raafat_adc_read(raafat_data);
    raafat_bmm150_read(raafat_data);
    bmi323_read_acc();
    bmi323_read_gyro();
    bmi323_read_temp();

    /* stringify inital raafat data*/
    raafat_json_stringify_data(raafat_data);

	for (;;) {
        /* read and update json packet every interval */
        
        printk("====================================\n");

        // if (!device_is_ready(dev_i2c.bus)) {
        //         printk("I2C bus %s is not ready!\n\r",dev_i2c.bus->name);
        //         return 1;
        // }
        printBatteryStats();

        // uint8_t write_buffer[3] = {0xAA, 0x04, 0xAB};
        // // i2c_write_read_dt(&dev_i2c, write_buffer, 3, fuel_guage_read_buf, 2);
        // i2c_write_dt(&dev_i2c, write_buffer, 3);
        // // write_buffer[0] = 0xAB;
        // // i2c_write_dt(&dev_i2c, write_buffer, 1);

        // i2c_read_dt(&dev_i2c, &fuel_guage_read_buf[0], 2);
        // printk("Bat Volt1 = %u", fuel_guage_read_buf[0]);
        // printk("Bat Volt2 = %u", fuel_guage_read_buf[1]);

        // // Unit: mAh
        // uint16_t capacity = 400;
        // uint8_t capMSB = capacity >> 8;
        // uint8_t capLSB = capacity & 0x00FF;
        // uint8_t capacityData[2] = {capMSB, capLSB};



        raafat_adc_read(raafat_data);
        raafat_bmm150_read(raafat_data);
        bmi323_read_acc();
        bmi323_read_gyro();
        bmi323_read_temp();

        /* Stringify latest data to json string */
        raafat_json_stringify_data(raafat_data);

		/* send json packet every second after getting new sensor values*/
        raafat_service_send_json_packet();

        /* Delay between each read */  
		k_sleep(K_SECONDS(2));
	}
}

