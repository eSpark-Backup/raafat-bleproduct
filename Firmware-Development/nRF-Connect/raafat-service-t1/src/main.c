#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

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

/*Defines*/
#define RAAFAT_GPIO_CLR_PWR NRF_GPIO_PIN_MAP(0,20)  //CLR POWER

/* Global declarations */
static raafat_data_t raafat_data = {0};

int main(void)
{
    /*config CLR_PWR as output and set high so that MCU powers up*/
    nrf_gpio_cfg_output(RAAFAT_GPIO_CLR_PWR);
    nrf_gpio_pin_set(RAAFAT_GPIO_CLR_PWR);

	printk("Raafat Hello World!\n");

    /* Raafat BLE service initialization*/
	raafat_service_init();
    raafat_adc_init();

    /* read adc, bmm150, bmi323 and store in raafat data before stringify*/
    raafat_adc_read(&raafat_data);

    /* stringify inital raafat data*/
    raafat_json_stringify_data(&raafat_data);

	for (;;) {
        /* update json packet every interval */
        raafat_adc_read(&raafat_data);

		/* send json packet every second after getting new sensor values*/
        if(raafat_service_send_json_packet() != EACCES)
        {
		    raafat_json_stringify_data(&raafat_data);
        }  
		k_sleep(K_SECONDS(5));
	}
}
