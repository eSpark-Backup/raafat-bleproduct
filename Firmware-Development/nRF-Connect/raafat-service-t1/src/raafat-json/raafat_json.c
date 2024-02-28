#include "raafat_json.h"
#include "cJSON.h"

char raafat_json_data[600];

int raafat_json_stringify_data(raafat_data_t* new_raafat_data)
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
    cJSON_AddNumberToObject(adc_values, "AN1", new_raafat_data->an0);
    cJSON_AddNumberToObject(adc_values, "AN2", new_raafat_data->an1);
    cJSON_AddNumberToObject(adc_values, "AN3", new_raafat_data->an2);
    cJSON_AddNumberToObject(adc_values, "AN4", new_raafat_data->an3);
    cJSON_AddNumberToObject(adc_values, "AN5", new_raafat_data->an4);
    cJSON_AddItemToObject(adc, "values", adc_values);

    #ifdef RAAFAT_ENABLE_GYRO_PACKET
    // Create gyro object
    cJSON *gyro = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "gyro", gyro);

    // Add gyro values
    cJSON_AddNumberToObject(gyro, "gyro_x", 0.123);
    cJSON_AddNumberToObject(gyro, "gyro_y", -0.456);
    cJSON_AddNumberToObject(gyro, "gyro_z", 0.789);
    #endif

    #ifdef RAAFAT_ENABLE_ACCEL_PACKET
    // Create accelerometer object
    cJSON *accelerometer = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "accelerometer", accelerometer);

    // Add accelerometer values
    cJSON_AddNumberToObject(accelerometer, "accel_x", 1.23);
    cJSON_AddNumberToObject(accelerometer, "accel_y", -2.34);
    cJSON_AddNumberToObject(accelerometer, "accel_z", 3.45);
    #endif

    #ifdef RAAFAT_ENABLE_MAGN_PACKET
    // Create magnetometer object
    cJSON *magnetometer = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "magnetometer", magnetometer);

    // Add magnetometer values
    cJSON_AddNumberToObject(magnetometer, "mag_x", -123);
    cJSON_AddNumberToObject(magnetometer, "mag_y", 456);
    cJSON_AddNumberToObject(magnetometer, "mag_z", -789);
    #endif

    // Print the JSON packet
    char *json_packet = cJSON_PrintUnformatted(root);

    // Free memory
    cJSON_Delete(root);
	snprintf(raafat_json_data,sizeof(raafat_json_data),"%s",json_packet);
	printk("json packet : \n %s", raafat_json_data);
    cJSON_free(json_packet);
}
