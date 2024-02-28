/*
 * Copyright (c) 2017 Linaro Limited
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <string.h>

#define LOG_LEVEL 4
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main);

#include <zephyr/zephyr.h>

#include "raafat_rgb.h"

void main(void)
{
	raafat_rgb_init();

	LOG_INF("Displaying pattern on strip");
	while (1) {
		
		raafat_rgb_change(RED, 0);
		k_sleep(K_SECONDS(1));

		raafat_rgb_change(GREEN, 0);
		k_sleep(K_SECONDS(1));

		raafat_rgb_change(BLUE, 0);
		k_sleep(K_SECONDS(1));

		raafat_rgb_change(WHITE, 0);
		k_sleep(K_SECONDS(1));

		raafat_rgb_change(BLACK, 0);
		k_sleep(RAAFAT_RGB_DELAY_TIME);
	}
}

#if 0 
#include <zephyr/zephyr.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

LOG_MODULE_REGISTER(Application);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led3)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
	int ret;

	if (!device_is_ready(led.port))
	{
		return 0;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0)
	{
		return 0;
	}
	gpio_pin_set_dt(&led, 1);

	while (1)
	{
		// ret = gpio_pin_toggle_dt(&led);
		// if (ret < 0) {
		// 	return 0;
		// }
		LOG_INF("Hello");
		k_msleep(1000);
	}

	return 0;
}

#endif