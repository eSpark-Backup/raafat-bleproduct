#include "raafat_bmm150.h"
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>

static const struct device *const dev = DEVICE_DT_GET_ONE(bosch_bmm150);
static struct sensor_value magn[3];

int raafat_bmm150_init()
{

	if (!device_is_ready(dev)) {
		printk("Device %s is not ready\n", dev->name);
		return 0;
	}

	printk("Device %p name is %s\n", dev, dev->name);
}

void raafat_bmm150_read()
{
    sensor_sample_fetch(dev);

    sensor_channel_get(dev, SENSOR_CHAN_MAGN_XYZ, magn);

    printk("MX: %d.%06d; MY: %d.%06d; MZ: %d.%06d; \n",
            magn[0].val1, magn[0].val2,
            magn[1].val1, magn[1].val2,
            magn[2].val1, magn[2].val2
        );
}