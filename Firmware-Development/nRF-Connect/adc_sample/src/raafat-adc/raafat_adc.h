#ifndef BT_RAAFAT_SERVICE_H_
#define BT_RAAFAT_SERVICE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

int raafat_adc_init();
int raafat_adc_read(int32_t* an0, int32_t* an1, int32_t* an2, int32_t* an3, int32_t* an4);

#ifdef __cplusplus
}
#endif

#endif /* BT_RAAFAT_SERVICE_H_ */


