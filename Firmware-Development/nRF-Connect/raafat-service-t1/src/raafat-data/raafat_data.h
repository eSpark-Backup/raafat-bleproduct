#ifndef BT_RAAFAT_DATA_H_
#define BT_RAAFAT_DATA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

/* raafat data structure */
typedef struct raafat_data_s{
	int32_t an0; //0.2
	int32_t an1; //0.3
	int32_t an2; //0.4
	int32_t an3; //0.5
	int32_t an4; //0.28

	char* raafat_json_packet;
}raafat_data_t;

#ifdef __cplusplus
}
#endif

#endif /* BT_RAAFAT_DATA_H_ */