/*
 * Copyright (c) 2021 Bosch Sensortec GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>

#define LOG_LEVEL 4
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main);

int main(void)
{
	const struct device *const dev = DEVICE_DT_GET_ONE(bosch_bmm150);
	struct sensor_value magn[3];

	if (!device_is_ready(dev)) {
		LOG_INF("Device %s is not ready\n", dev->name);
		return 0;
	}

	LOG_INF("Device %p name is %s\n", dev, dev->name);

	while (1) {
		/* 10ms period, 100Hz Sampling frequency */
		k_sleep(K_MSEC(10));

		sensor_sample_fetch(dev);

		sensor_channel_get(dev, SENSOR_CHAN_MAGN_XYZ, magn);

		LOG_INF("MX: %d.%06d; MY: %d.%06d; MZ: %d.%06d; ",
		       magn[0].val1, magn[0].val2,
		       magn[1].val1, magn[1].val2,
		       magn[2].val1, magn[2].val2
			);
	}
	return 0;
}
