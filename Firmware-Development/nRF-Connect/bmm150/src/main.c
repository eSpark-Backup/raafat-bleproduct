/*
 * Copyright (c) 2021 Bosch Sensortec GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <stdio.h>

/* Raafat Includes */
#include "raafat_bmm150.h"


int main(void)
{
	raafat_bmm150_init();
	while (1) {
		/* 10ms period, 100Hz Sampling frequency */
		k_sleep(K_MSEC(10));
		raafat_bmm150_read();
	}
	return 0;
}
