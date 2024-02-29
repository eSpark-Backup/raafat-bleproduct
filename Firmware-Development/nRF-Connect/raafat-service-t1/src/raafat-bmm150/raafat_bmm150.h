#ifndef RAAFAT_BMM150_H_
#define RAAFAT_BMM150_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "raafat_data.h"


int raafat_bmm150_init();
void raafat_bmm150_read(raafat_data_t* new_raafat_data);


#ifdef __cplusplus
}
#endif



#endif //RAAFAT_BMM150_H_