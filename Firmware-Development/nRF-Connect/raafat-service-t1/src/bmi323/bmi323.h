#ifndef BMI_323_H_
#define BMI_323_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "raafat_data.h"

int bmi323_init(raafat_data_t* new_raafat_data);
void bmi323_read_data(uint8_t* data, uint8_t* address, uint8_t bytes_to_read);
void bmi323_soft_reset();
void bmi323_read_acc();
void bmi323_read_gyro();
void bmi323_read_temp();

#ifdef __cplusplus
}
#endif

#endif //BMI_323_H_