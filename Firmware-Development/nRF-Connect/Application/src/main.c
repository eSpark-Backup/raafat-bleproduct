/*
 * Copyright (c) 2020 Libre Solar Technologies GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gap.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/conn.h>

#include <dk_buttons_and_leds.h>
/* STEP 7 - Include the header file of MY LBS customer service */
#include "BLE.h"
char json[150]; 

static struct bt_le_adv_param *adv_param = BT_LE_ADV_PARAM(
	(BT_LE_ADV_OPT_CONNECTABLE |
	 BT_LE_ADV_OPT_USE_IDENTITY), /* Connectable advertising and use identity address */
	800, /* Min Advertising Interval 500ms (800*0.625ms) */
	801, /* Max Advertising Interval 500.625ms (801*0.625ms) */
	NULL); /* Set to NULL for undirected advertising */

LOG_MODULE_REGISTER(Lesson4_Exercise1, LOG_LEVEL_INF);

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

#define RUN_STATUS_LED DK_LED1
#define CON_STATUS_LED DK_LED2

/* STEP 8.1 - Specify the LED to control */
#define USER_LED DK_LED3

/* STEP 9.1 - Specify the button to monitor */
#define USER_BUTTON DK_BTN1_MSK

#define RUN_LED_BLINK_INTERVAL 1000

static bool app_button_state;

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),

};

static const struct bt_data sd[] = {
	BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_LBS_VAL),
};

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

/* STEP 8.2 - Define the application callback function for controlling the LED */
static void app_led_cb(bool led_state)
{
	dk_set_led(USER_LED, led_state);
}

/* STEP 9.2 - Define the application callback function for reading the state of the button */
static bool app_button_cb(void)
{
	return app_button_state;
}

/* STEP 10 - Declare a varaible app_callbacks of type my_lbs_cb and initiate its members to the applications call back functions we developed in steps 8.2 and 9.2. */
static struct my_lbs_cb app_callbacks = {
	.led_cb = app_led_cb,
	.button_cb = app_button_cb,
};

static void button_changed(uint32_t button_state, uint32_t has_changed)
{
	if (has_changed & USER_BUTTON) {
		uint32_t user_button_state = button_state & USER_BUTTON;
		app_button_state = user_button_state ? true : false;
	}
}
static void on_connected(struct bt_conn *conn, uint8_t err)
{
	if (err) {
		printk("Connection failed (err %u)\n", err);
		return;
	}

	printk("Connected\n");

	dk_set_led_on(CON_STATUS_LED);
}

static void on_disconnected(struct bt_conn *conn, uint8_t reason)
{
	printk("Disconnected (reason %u)\n", reason);

	dk_set_led_off(CON_STATUS_LED);
}

struct bt_conn_cb connection_callbacks = {
	.connected = on_connected,
	.disconnected = on_disconnected,
};

static int init_button(void)
{
	int err;

	err = dk_buttons_init(button_changed);
	if (err) {
		printk("Cannot init buttons (err: %d)\n", err);
	}

	return err;
}
int main(void)
{
	int err;
	uint32_t count = 0;
	uint16_t buf;
	struct adc_sequence sequence = {
		.buffer = &buf,
		/* buffer size in bytes, not number of samples */
		.buffer_size = sizeof(buf),
	};

	/* Configure channels individually prior to sampling. */
	for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) 
	{
		if (!device_is_ready(adc_channels[i].dev)) {
			printk("ADC controller device %s not ready\n", adc_channels[i].dev->name);
			return 0;
		}

		err = adc_channel_setup_dt(&adc_channels[i]);
		if (err < 0) {
			printk("Could not setup channel #%d (%d)\n", i, err);
			return 0;
		}
	}
		int blink_status = 0;


	LOG_INF("Starting Lesson 4 - Exercise 1 \n");
    printk("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh\n");
	err = dk_leds_init();
	if (err) {
		LOG_ERR("LEDs init failed (err %d)\n", err);
		return;
	}

	err = init_button();
	if (err) {
		printk("Button init failed (err %d)\n", err);
		return;
	}

	err = bt_enable(NULL);
	if (err) {
		LOG_ERR("Bluetooth init failed (err %d)\n", err);
		return;
	}
	bt_conn_cb_register(&connection_callbacks);

	/* STEP 11 - Pass your application callback functions stored in app_callbacks to the MY LBS service */
	err = my_lbs_init(&app_callbacks);
	if (err) {
		printk("Failed to init LBS (err:%d)\n", err);
		return;
	}
	LOG_INF("Bluetooth initialized\n");
	err = bt_le_adv_start(adv_param, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
	if (err) {
		LOG_ERR("Advertising failed to start (err %d)\n", err);
		return;
	}

	LOG_INF("Advertising successfully started\n");

	while (1) {
		printk("ADC reading[%u]:\n", count++);
		for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) 
		{
			int32_t val_mv[8];
            printk("%d : ",ARRAY_SIZE(adc_channels));
			printk("%d : ",i);
			printk("- %s, channel %d: ",
			       adc_channels[i].dev->name,
			       adc_channels[i].channel_id);
  
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
			if (adc_channels[i].channel_cfg.differential) 
			{
				val_mv[i]= (int32_t)((int16_t)buf);
			}
			else 
			{   if (buf>60000)
			       buf = 0;
				val_mv[i] = (int32_t)buf;
			}
			printk("%d"PRId32, val_mv[i]);
			 err = adc_raw_to_millivolts_dt(&adc_channels[i],
					       &val_mv[i]);
			/* conversion to mV may not be supported, skip if not */
			if (err < 0) 
			 {
				printk(" (value in mV not available)\n");
			} 
			 else 
			 {
				printk(" = %"PRId32" mV\n", val_mv[i]);
			}
			
			snprintk(json, sizeof(json), "{\"AIN0\": %d, \"AIN1\": %d, \"AIN2\": %d, \"AIN3\": %d, \"AIN4\": %d, \"AIN5\": %d, \"AIN6\": %d, \"AIN7\": %d}",
																																			val_mv[0] , val_mv[1],
																																			val_mv[2], val_mv[3],
																																			val_mv[4], val_mv[5],
																																			val_mv[6], val_mv[7]
																																			);
			printk("JSON: %s\n", json);
		}

		k_sleep(K_MSEC(1000));
	}
	return 0;
}
