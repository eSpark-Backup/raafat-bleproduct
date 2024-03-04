#ifndef BT_RAAFAT_DATA_H_
#define BT_RAAFAT_DATA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stdbool.h>
/* raafat data structure */
typedef struct raafat_data_s{
	int32_t an0; //0.2
	int32_t an1; //0.3
	int32_t an2; //0.4
	int32_t an3; //0.5
	int32_t an4; //0.28

	char* raafat_json_packet;

	/* Magnetometer data */
	int32_t magX_val1;
	int32_t magX_val2;
	int32_t magY_val1;
	int32_t magY_val2;
	int32_t magZ_val1;
	int32_t magZ_val2;

	/* RGB Status */
	bool rgb_status;

	/* Accelerometer data */
	int32_t accX_val1;
	int32_t accX_val2;
	int32_t accY_val1;
	int32_t accY_val2;
	int32_t accZ_val1;
	int32_t accZ_val2;

	/* Gyroscope data */
	int32_t gyroX_val1;
	int32_t gyroX_val2;
	int32_t gyroY_val1;
	int32_t gyroY_val2;
	int32_t gyroZ_val1;
	int32_t gyroZ_val2;

	/* Temperature data */
	uint8_t temp_h;
	uint8_t temp_l;

}raafat_data_t;

#ifdef __cplusplus
}
#endif

#endif /* BT_RAAFAT_DATA_H_ */