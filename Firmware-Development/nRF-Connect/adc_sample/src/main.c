/*
 * Copyright (c) 2020 Libre Solar Technologies GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include "raafat_adc.h"

typedef struct raafat_data_s{
	int32_t an0; //0.2
	int32_t an1; //0.3
	int32_t an2; //0.4
	int32_t an3; //0.5
	int32_t an4; //0.28
}raafat_data_t;

static raafat_data_t raafat_data = {0};

int main(void)
{
	error_t err = 0;
	err = raafat_adc_init();
	if(err != 0)
	{	
		printk("Unable to initialize raafat adc\n");
		return 0;
	}

	while (1) {

		err = raafat_adc_read(&(raafat_data.an0), &(raafat_data.an1), &(raafat_data.an2), &(raafat_data.an3), &(raafat_data.an4));
		
		printk(" = %"PRId32" mV\n", raafat_data.an0);
		printk(" = %"PRId32" mV\n", raafat_data.an1);
		printk(" = %"PRId32" mV\n", raafat_data.an2);
		printk(" = %"PRId32" mV\n", raafat_data.an3);
		printk(" = %"PRId32" mV\n", raafat_data.an4);
		k_sleep(K_MSEC(1000));
	}
	return 0;
}
