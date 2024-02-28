#include "raafat_adc.h"
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>


#if !DT_NODE_EXISTS(DT_PATH(zephyr_user)) || \
	!DT_NODE_HAS_PROP(DT_PATH(zephyr_user), io_channels)
#error "No suitable devicetree overlay specified"
#endif

#define DT_SPEC_AND_COMMA(node_id, prop, idx) \
	ADC_DT_SPEC_GET_BY_IDX(node_id, idx),

/* Data of ADC io-channels specified in devicetree. */
static const struct adc_dt_spec adc_channels[] = {
	DT_FOREACH_PROP_ELEM(DT_PATH(zephyr_user), io_channels,
			     DT_SPEC_AND_COMMA)
};

static uint32_t count = 0;
static uint16_t buf;
static struct adc_sequence sequence = {
    .buffer = &buf,
    /* buffer size in bytes, not number of samples */
    .buffer_size = sizeof(buf),
};

int raafat_adc_init()
{
    int err;

	/* Configure channels individually prior to sampling. */
	for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) {
		if (!adc_is_ready_dt(&adc_channels[i])) {
			printk("ADC controller device %s not ready\n", adc_channels[i].dev->name);
			return 0;
		}

		err = adc_channel_setup_dt(&adc_channels[i]);
		if (err < 0) {
			printk("Could not setup channel #%d (%d)\n", i, err);
			return 0;
		}
	}

    return err;
}

int raafat_adc_read(raafat_data_t* new_raafat_data)
{
    int err = 0;
    // printk("ADC reading[%u]:\n", count++);
    int32_t val_mv[ARRAY_SIZE(adc_channels)];
    for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) {

        // printk("- %s, channel %d: ",
        //         adc_channels[i].dev->name,
        //         adc_channels[i].channel_id);

        (void)adc_sequence_init_dt(&adc_channels[i], &sequence);

        err = adc_read(adc_channels[i].dev, &sequence);
        if (err < 0) {
            printk("Could not read (%d)\n", err);
            continue;
        }

        /*
            * If using differential mode, the 16 bit value
            * in the ADC sample buffer should be a signed 2's
            * complement value.
            */
        if (adc_channels[i].channel_cfg.differential) {
            val_mv[i] = (int32_t)((int16_t)buf);
        } else {
            val_mv[i] = (int32_t)buf;
        }
        // printk("%"PRId32, val_mv[i]);
        err = adc_raw_to_millivolts_dt(&adc_channels[i],
                            &val_mv[i]);
        /* conversion to mV may not be supported, skip if not */
        // if (err < 0) {
        //     printk(" (value in mV not available)\n");
        // } else {
        //     printk(" = %"PRId32" mV\n", val_mv[i]);
        // }
    }
    new_raafat_data->an0 = val_mv[0];
    new_raafat_data->an1 = val_mv[1];
    new_raafat_data->an2 = val_mv[2];
    new_raafat_data->an3 = val_mv[3];
    new_raafat_data->an4 = val_mv[4];

    return err;
}