#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

/*GPIO Inlcudes*/
#include <zephyr/drivers/gpio.h>
#include <hal/nrf_gpio.h>

#define LOG_LEVEL 4
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main);

/* external module includes */
#include "cJSON.h"

/* raafat includes */
#include "raafat_service.h"

/*Defines*/
#define RAAFAT_GPIO_CLR_PWR NRF_GPIO_PIN_MAP(0,20)  //CLR POWER

/* raafat data structure */
typedef struct raafat_data_s{
	int32_t an0; //0.2
	int32_t an1; //0.3
	int32_t an2; //0.4
	int32_t an3; //0.5
	int32_t an4; //0.28
}raafat_data_t;

/* function prototypes */
int raafat_json_stringify_data(raafat_data_t new_raafat_data);

/* Global declarations */
static raafat_data_t raafat_data = {0};
char raafat_json_data[600];

int main(void)
{
    /*config CLR_PWR as output and set high so that MCU powers up*/
    nrf_gpio_cfg_output(RAAFAT_GPIO_CLR_PWR);
    nrf_gpio_pin_set(RAAFAT_GPIO_CLR_PWR);

	printk("Raafat Hello World!\n");

    /* Raafat BLE service initialization*/
	raafat_service_init();

    /* read adc, bmm150, bmi323 and store in raafat data before stringify*/

    /* stringify inital raafat data*/
    raafat_json_stringify_data(raafat_data);

	for (;;) {
		/* send json packet every second */
        if(raafat_service_send_json_packet() != EACCES)
        {
		    raafat_json_stringify_data(raafat_data);
        }  
		k_sleep(K_SECONDS(5));
	}
}


int raafat_json_stringify_data(raafat_data_t new_raafat_data)
{
    // Create root JSON object
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) {
        printk("Error creating JSON object!\n");
        return 1;
    }

    // Create adc object
    cJSON *adc = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "adc", adc);

    // Add adc values
    cJSON *adc_values = cJSON_CreateObject();
    cJSON_AddNumberToObject(adc_values, "adc1", raafat_data.an0);
    cJSON_AddNumberToObject(adc_values, "adc2", raafat_data.an1);
    cJSON_AddNumberToObject(adc_values, "adc3", raafat_data.an2);
    cJSON_AddNumberToObject(adc_values, "adc4", raafat_data.an3);
    cJSON_AddNumberToObject(adc_values, "adc5", raafat_data.an4);
    cJSON_AddItemToObject(adc, "values", adc_values);

    // Create gyro object
    cJSON *gyro = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "gyro", gyro);

    // Add gyro values
    cJSON_AddNumberToObject(gyro, "gyro_x", 0.123);
    cJSON_AddNumberToObject(gyro, "gyro_y", -0.456);
    cJSON_AddNumberToObject(gyro, "gyro_z", 0.789);

    // Create accelerometer object
    cJSON *accelerometer = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "accelerometer", accelerometer);

    // Add accelerometer values
    cJSON_AddNumberToObject(accelerometer, "accel_x", 1.23);
    cJSON_AddNumberToObject(accelerometer, "accel_y", -2.34);
    cJSON_AddNumberToObject(accelerometer, "accel_z", 3.45);

    // Create magnetometer object
    cJSON *magnetometer = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "magnetometer", magnetometer);

    // Add magnetometer values
    cJSON_AddNumberToObject(magnetometer, "mag_x", -123);
    cJSON_AddNumberToObject(magnetometer, "mag_y", 456);
    cJSON_AddNumberToObject(magnetometer, "mag_z", -789);

    // Print the JSON packet
    char *json_packet = cJSON_PrintUnformatted(root);

    // Free memory
    cJSON_Delete(root);
	snprintf(raafat_json_data,sizeof(raafat_json_data),"%s",json_packet);
	printk("json packet : \n %s", raafat_json_data);
    cJSON_free(json_packet);
}
