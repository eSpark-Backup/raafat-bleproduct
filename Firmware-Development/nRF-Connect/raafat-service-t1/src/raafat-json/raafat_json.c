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
    cJSON_AddStringToObject(adc, "scale", "mV");

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
    cJSON_AddItemToObject(root, "gyroscope", gyro);
    cJSON_AddStringToObject(gyro, "scale", "raw");

    // Add gyro values
    cJSON *gyroscope_values = cJSON_CreateObject();
    cJSON_AddNumberToObject(gyroscope_values, "gyro_x", new_raafat_data->gyroX_val1);
    cJSON_AddNumberToObject(gyroscope_values, "gyro_y", new_raafat_data->gyroY_val1);
    cJSON_AddNumberToObject(gyroscope_values, "gyro_z", new_raafat_data->gyroZ_val1);
    cJSON_AddItemToObject(gyro, "values", gyroscope_values);
    #endif

    #ifdef CONFIG_BT_RAAFAT_ENABLE_ACCEL_PACKET
    // Create accelerometer object
    cJSON *accelerometer = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "accelerometer", accelerometer);
    cJSON_AddStringToObject(accelerometer, "scale", "raw");

    // Add accelerometer values
    cJSON *accelerometer_values = cJSON_CreateObject();

    // cJSON_AddNumberToObject(accelerometer_values, "accel_x_val1", new_raafat_data->accX_val1);
    // cJSON_AddNumberToObject(accelerometer_values, "accel_y_val1", new_raafat_data->accY_val1);
    // cJSON_AddNumberToObject(accelerometer_values, "accel_z_val1", new_raafat_data->accZ_val1);

    // cJSON_AddNumberToObject(accelerometer_values, "accel_x_val2", new_raafat_data->accX_val2);
    // cJSON_AddNumberToObject(accelerometer_values, "accel_y_val2", new_raafat_data->accY_val2);
    // cJSON_AddNumberToObject(accelerometer_values, "accel_z_val2", new_raafat_data->accZ_val2);

    cJSON_AddNumberToObject(accelerometer_values, "accel_x", new_raafat_data->accX_val1);
    cJSON_AddNumberToObject(accelerometer_values, "accel_y", new_raafat_data->accY_val1);
    cJSON_AddNumberToObject(accelerometer_values, "accel_z", new_raafat_data->accZ_val1);
    
    cJSON_AddItemToObject(accelerometer, "values", accelerometer_values);
    #endif

    #ifdef CONFIG_BT_RAAFAT_ENABLE_MAGN_PACKET
    // Create magnetometer object
    cJSON *magnetometer = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "magnetometer", magnetometer);
    cJSON_AddStringToObject(magnetometer, "scale", "raw");

    // Add magnetometer values
    cJSON *magnetometer_values = cJSON_CreateObject();

    // cJSON_AddNumberToObject(magnetometer_values, "mag_x_val1", new_raafat_data->magX_val1);
    // cJSON_AddNumberToObject(magnetometer_values, "mag_y_val1", new_raafat_data->magY_val1);
    // cJSON_AddNumberToObject(magnetometer_values, "mag_z_val1", new_raafat_data->magZ_val1);

    // cJSON_AddNumberToObject(magnetometer_values, "mag_x_val2", new_raafat_data->magX_val2);
    // cJSON_AddNumberToObject(magnetometer_values, "mag_y_val2", new_raafat_data->magY_val2);
    // cJSON_AddNumberToObject(magnetometer_values, "mag_z_val2", new_raafat_data->magZ_val2);

    // cJSON_AddNumberToObject(magnetometer, "mag_x", ((int64_t)new_raafat_data->magX_val1 << 32) | new_raafat_data->magX_val2);
    // cJSON_AddNumberToObject(magnetometer, "mag_y", ((int64_t)new_raafat_data->magY_val1 << 32) | new_raafat_data->magY_val2);
    // cJSON_AddNumberToObject(magnetometer, "mag_z", ((int64_t)new_raafat_data->magZ_val1 << 32) | new_raafat_data->magZ_val2);

    cJSON_AddNumberToObject(magnetometer_values, "mag_x", new_raafat_data->magX_val1 );
    cJSON_AddNumberToObject(magnetometer_values, "mag_y", new_raafat_data->magY_val1 );
    cJSON_AddNumberToObject(magnetometer_values, "mag_z", new_raafat_data->magZ_val1 );

    cJSON_AddItemToObject(magnetometer, "values", magnetometer_values);
    #endif

    /* RGB data */
    cJSON *rgb_led = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "rgb_led", rgb_led);
    cJSON_AddBoolToObject(rgb_led, "status", new_raafat_data->rgb_status);

    /* Temperature Data */
    cJSON *temp = cJSON_CreateObject();
    cJSON_AddItemToObject(root,"temperature", temp);
    // cJSON_AddNumberToObject(temp, "value", (uint16_t)(((uint16_t)new_raafat_data->temp_h << 8) | ((uint16_t)new_raafat_data->temp_l)));
    cJSON_AddStringToObject(temp,"scale","raw");
    cJSON *temp_values = cJSON_CreateObject();
    cJSON_AddItemToObject(temp,"values", temp_values);
    cJSON_AddNumberToObject(temp_values, "temp_h", new_raafat_data->temp_h);
    cJSON_AddNumberToObject(temp_values, "temp_l", new_raafat_data->temp_l);

    // Print the JSON packet
    char *json_packet = cJSON_PrintUnformatted(root);
    // Free memory
    cJSON_Delete(root);
	snprintf(new_raafat_data->raafat_json_packet, 500, "%s", json_packet);
	printk("JSON PACKET = %s\n", new_raafat_data->raafat_json_packet);
    cJSON_free(json_packet);
}
