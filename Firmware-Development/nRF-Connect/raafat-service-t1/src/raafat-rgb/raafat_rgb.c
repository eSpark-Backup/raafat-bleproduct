#include <zephyr/zephyr.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/device.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/sys/util.h>

#include "raafat_rgb.h"


#define STRIP_NODE		DT_ALIAS(led_strip)
#define STRIP_NUM_PIXELS	DT_PROP(DT_ALIAS(led_strip), chain_length)

static raafat_data_t* s_new_raafat_data;
#define RGB(_r, _g, _b) { .r = (_r), .g = (_g), .b = (_b) }

static const struct led_rgb colors[] = {
	RGB(0x00, 0x00, 0x00), /* Black/off */
	RGB(0x0f, 0x00, 0x00), /* red */
	RGB(0x00, 0x0f, 0x00), /* green */
	RGB(0x00, 0x00, 0x0f), /* blue */
	RGB(0x0f, 0x0f, 0x0f), /* white */
};

struct led_rgb pixels[STRIP_NUM_PIXELS];

static const struct device *strip = DEVICE_DT_GET(STRIP_NODE);

#define STACK_SIZE 1024
#define PRIORITY 5

// Define stack and control structure for your thread
K_THREAD_STACK_DEFINE(my_stack, STACK_SIZE);
struct k_thread raafat_rgb_thread_data;

// Define your thread function
void raafat_rgb_thread(void *arg) {
	printk("RGB Thread Started!\n");
    while (1) {
    	printk("RGB Thread Running!\n");
		raafat_rgb_change(RED, 0);
		k_sleep(RAAFAT_RGB_DELAY_TIME);

		raafat_rgb_change(GREEN, 0);
		k_sleep(RAAFAT_RGB_DELAY_TIME);

		raafat_rgb_change(BLUE, 0);
		k_sleep(RAAFAT_RGB_DELAY_TIME);

		raafat_rgb_change(WHITE, 0);
		k_sleep(RAAFAT_RGB_DELAY_TIME);

		raafat_rgb_change(BLACK, 0);
		k_sleep(RAAFAT_RGB_DELAY_TIME);
    }
}

void raafat_rgb_init(raafat_data_t* new_raafat_data)
{

	if (device_is_ready(strip)) {
		printk("Found LED strip device %s", strip->name);
	} else {
		printk("LED strip device %s is not ready", strip->name);
	}

	s_new_raafat_data = new_raafat_data;

    /* LED Thread intialize */
    // Initialize the thread
    k_thread_create(&raafat_rgb_thread_data, my_stack, STACK_SIZE,
                    raafat_rgb_thread, NULL, NULL, NULL,
                    PRIORITY, 0, K_NO_WAIT);

    // Start the thread
    k_thread_start(&raafat_rgb_thread_data);

}

void raafat_rgb_change(int color, int pixel_index)
{
    memset(&pixels, 0x00, sizeof(pixels));
    memcpy(&pixels[pixel_index], &colors[color], sizeof(struct led_rgb));
    led_strip_update_rgb(strip, pixels, STRIP_NUM_PIXELS);
	s_new_raafat_data->rgb_status = (uint8_t)color;
}