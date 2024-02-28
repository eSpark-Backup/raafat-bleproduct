#include <zephyr/zephyr.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/device.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/sys/util.h>

#include "raafat_rgb.h"


#define STRIP_NODE		DT_ALIAS(led_strip)
#define STRIP_NUM_PIXELS	DT_PROP(DT_ALIAS(led_strip), chain_length)


#define RGB(_r, _g, _b) { .r = (_r), .g = (_g), .b = (_b) }

static const struct led_rgb colors[] = {
	RGB(0x0f, 0x00, 0x00), /* red */
	RGB(0x00, 0x0f, 0x00), /* green */
	RGB(0x00, 0x00, 0x0f), /* blue */
	RGB(0x0f, 0x0f, 0x0f), /* white */
	RGB(0x00, 0x00, 0x00), /* Black/off */
};

struct led_rgb pixels[STRIP_NUM_PIXELS];

static const struct device *strip = DEVICE_DT_GET(STRIP_NODE);


void raafat_rgb_init()
{

	if (device_is_ready(strip)) {
		printk("Found LED strip device %s", strip->name);
	} else {
		printk("LED strip device %s is not ready", strip->name);
	}
}

void raafat_rgb_change(int color, int pixel_index)
{
    memset(&pixels, 0x00, sizeof(pixels));
    memcpy(&pixels[pixel_index], &colors[color], sizeof(struct led_rgb));
    led_strip_update_rgb(strip, pixels, STRIP_NUM_PIXELS);
}