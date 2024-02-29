#include "raafat_bmm150.h"
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>

static const struct device *const dev = DEVICE_DT_GET_ONE(bosch_bmm150);
static struct sensor_value magn[3];
static struct sensor_value full_scale, sampling_freq, oversampling;

#define CONFIG_BMM150_PRESET_HIGH_ACCURACY

int raafat_bmm150_init()
{

	if (!device_is_ready(dev)) {
		printk("Device %s is not ready\n", dev->name);
		return 0;
	}

	printk("Device %p name is %s\n", dev, dev->name);

    sampling_freq.val1 = 100;
    sampling_freq.val2 = 0;

    sensor_attr_set(dev, SENSOR_CHAN_MAGN_XYZ,
        SENSOR_ATTR_SAMPLING_FREQUENCY,
        &sampling_freq);
}

void raafat_bmm150_read(raafat_data_t* new_raafat_data)
{
    sensor_sample_fetch(dev);

    sensor_channel_get(dev, SENSOR_CHAN_MAGN_XYZ, magn);

    // sensor_channel_get(dev, SENSOR_CHAN_MAGN_X, &magn[0]);
    // sensor_channel_get(dev, SENSOR_CHAN_MAGN_Y, &magn[1]);
    // sensor_channel_get(dev, SENSOR_CHAN_MAGN_Z, &magn[2]); 

    // magn[0].val1 &= 0xFFFFE000;
    // magn[1].val1 &= 0xFFFFE000;
    // magn[2].val1 &= 0xFFFFE000;

    printk("MX: %d.%06d; MY: %d.%06d; MZ: %d.%06d; \n",
            magn[0].val1,               magn[0].val2,
            magn[1].val1,               magn[1].val2,
            magn[2].val1,               magn[2].val2
        );

    // printk("( x y z ) = ( %f  %f  %f )\n",
    //     sensor_value_to_double(&magn[0]),
    //     sensor_value_to_double(&magn[1]),
    //     sensor_value_to_double(&magn[2]));

    // printk("( x y z ) = ( %d  %d  %d )  \n",
    //     sensor_value_to_micro(&magn[0]),
    //     sensor_value_to_micro(&magn[1]),
    //     sensor_value_to_micro(&magn[2]));

    new_raafat_data->magX_val1 = magn[0].val1; 
    new_raafat_data->magX_val2 = magn[0].val2;
    
    new_raafat_data->magY_val1 = magn[1].val1; 
    new_raafat_data->magY_val2 = magn[1].val2;

    new_raafat_data->magZ_val1 = magn[2].val1; 
    new_raafat_data->magZ_val2 = magn[2].val2;
}