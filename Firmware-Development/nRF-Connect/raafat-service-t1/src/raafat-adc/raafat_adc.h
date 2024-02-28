#ifndef BT_RAAFAT_ADC_H_
#define BT_RAAFAT_ADC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include "raafat_data.h"

int raafat_adc_init();
int raafat_adc_read(raafat_data_t* new_raafat_data);

#ifdef __cplusplus
}
#endif

#endif /* BT_RAAFAT_ADC_H_ */


