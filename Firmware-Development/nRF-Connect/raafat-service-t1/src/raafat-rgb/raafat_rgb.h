#ifndef BT_RAAFAT_RGB_H_
#define BT_RAAFAT_RGB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "raafat_data.h"

#define RAAFAT_RGB_DELAY_TIME K_SECONDS(1)

enum raafat_rgb_e   { 
                        BLACK,                     
                        RED, 
                        GREEN, 
                        BLUE, 
                        WHITE 
                    };

void raafat_rgb_init(raafat_data_t* new_raafat_data);
void raafat_rgb_change(int color, int pixel_index);

#ifdef __cplusplus
}
#endif


#endif //BT_RAAFAT_RGB_H