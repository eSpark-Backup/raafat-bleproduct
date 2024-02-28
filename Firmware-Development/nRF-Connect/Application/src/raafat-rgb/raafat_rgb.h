#ifndef BT_RAAFAT_RGB_H_
#define BT_RAAFAT_RGB_H_

#ifdef __cplusplus
extern "C" {
#endif

#define RAAFAT_RGB_DELAY_TIME K_SECONDS(1)

enum raafat_rgb_e { RED, GREEN, BLUE, WHITE, BLACK };

void raafat_rgb_init();
void raafat_rgb_change(int color, int pixel_index);

#ifdef __cplusplus
}
#endif


#endif //BT_RAAFAT_RGB_H