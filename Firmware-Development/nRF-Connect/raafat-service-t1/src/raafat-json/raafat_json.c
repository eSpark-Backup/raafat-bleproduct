#include "raafat_json.h"
#include "cJSON.h"

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
    cJSON_AddStringToObject(adc, "Scale", "mV");

    // Add adc values
    cJSON *adc_values = cJSON_CreateObject();
    cJSON_AddNumberToObject(adc_values, "AN1", new_raafat_data->an0);
    cJSON_AddNumberToObject(adc_values, "AN2", new_raafat_data->an1);
    cJSON_AddNumberToObject(adc_values, "AN3", new_raafat_data->an2);
    cJSON_AddNumberToObject(adc_values, "AN4", new_raafat_data->an3);
    cJSON_AddNumberToObject(adc_values, "AN5", new_raafat_data->an4);
    cJSON_AddItemToObject(adc, "values", adc_values);



    #ifdef CONFIG_BT_RAAFAT_ENABLE_GYRO_PACKET
    // Create gyro object
    cJSON *gyro = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "gyro", gyro);

    // Add gyro values
    cJSON_AddNumberToObject(gyro, "gyro_x", 0.123);
    cJSON_AddNumberToObject(gyro, "gyro_y", -0.456);
    cJSON_AddNumberToObject(gyro, "gyro_z", 0.789);
    #endif

    #ifdef CONFIG_BT_RAAFAT_ENABLE_ACCEL_PACKET
    // Create accelerometer object
    cJSON *accelerometer = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "accelerometer", accelerometer);

    // Add accelerometer values
    cJSON_AddNumberToObject(accelerometer, "accel_x", 1.23);
    cJSON_AddNumberToObject(accelerometer, "accel_y", -2.34);
    cJSON_AddNumberToObject(accelerometer, "accel_z", 3.45);
    #endif

    #ifdef CONFIG_BT_RAAFAT_ENABLE_MAGN_PACKET
    // Create magnetometer object
    cJSON *magnetometer = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "magnetometer", magnetometer);
    cJSON_AddStringToObject(magnetometer, "Scale", "raw");

    // Add magnetometer values
    // cJSON_AddNumberToObject(magnetometer, "mag_x_val1", new_raafat_data->magX_val1);
    // cJSON_AddNumberToObject(magnetometer, "mag_y_val1", new_raafat_data->magY_val1);
    // cJSON_AddNumberToObject(magnetometer, "mag_z_val1", new_raafat_data->magZ_val1);

    // cJSON_AddNumberToObject(magnetometer, "mag_x_val2", new_raafat_data->magX_val2);
    // cJSON_AddNumberToObject(magnetometer, "mag_y_val2", new_raafat_data->magY_val2);
    // cJSON_AddNumberToObject(magnetometer, "mag_z_val2", new_raafat_data->magZ_val2);

    // cJSON_AddNumberToObject(magnetometer, "mag_x", ((int64_t)new_raafat_data->magX_val1 << 32) | new_raafat_data->magX_val2);
    // cJSON_AddNumberToObject(magnetometer, "mag_y", ((int64_t)new_raafat_data->magY_val1 << 32) | new_raafat_data->magY_val2);
    // cJSON_AddNumberToObject(magnetometer, "mag_z", ((int64_t)new_raafat_data->magZ_val1 << 32) | new_raafat_data->magZ_val2);

    cJSON *magnetometer_values = cJSON_CreateObject();
    cJSON_AddNumberToObject(magnetometer_values, "mag_x", new_raafat_data->magX_val1 );
    cJSON_AddNumberToObject(magnetometer_values, "mag_y", new_raafat_data->magY_val1 );
    cJSON_AddNumberToObject(magnetometer_values, "mag_z", new_raafat_data->magZ_val1 );
    cJSON_AddItemToObject(magnetometer, "values", magnetometer_values);
    #endif

    /* RGB data */
    cJSON *rgb_led = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "rgb_led", rgb_led);
    cJSON_AddBoolToObject(rgb_led, "status", new_raafat_data->rgb_status);

    // Print the JSON packet
    char *json_packet = cJSON_PrintUnformatted(root);
    // Free memory
    cJSON_Delete(root);
	snprintf(new_raafat_data->raafat_json_packet, 300, "%s", json_packet);
	printk("json packet : \n %s", new_raafat_data->raafat_json_packet);
    cJSON_free(json_packet);
}
