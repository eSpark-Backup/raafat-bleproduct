/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include "./raafat_service.h"
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(bt_raafat, CONFIG_BT_RAAFAT_LOG_LEVEL);

static bool     notify_enabled;
static struct 	bt_raafat_cb	raafat_cb;
static uint8_t 	AN1_pin_value;
static uint8_t 	AN2_pin_value;
static uint8_t 	AN3_pin_value;
static uint8_t 	AN4_pin_value;

static void raafatlc_ccc_cfg_changed(const struct bt_gatt_attr *attr,
				  uint16_t value)
{
	notify_enabled = (value == BT_GATT_CCC_NOTIFY);
}

#ifdef CONFIG_BT_RAAFAT_POLL_ANALOG
static ssize_t read_AN1(struct bt_conn *conn,
			  const struct bt_gatt_attr *attr,
			  void *buf,
			  uint16_t len,
			  uint16_t offset)
{
	const char *value = attr->user_data;

	LOG_DBG("Attribute read, handle: %u, conn: %p", attr->handle,
		(void *)conn);

	if (raafat_cb.AN1_read_cb) {
		AN1_pin_value = raafat_cb.AN1_read_cb();
		AN2_pin_value = raafat_cb.AN2_read_cb();
		AN3_pin_value = raafat_cb.AN3_read_cb();
		AN4_pin_value = raafat_cb.AN4_read_cb();
		return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
					 sizeof(*value));
	}

	return 0;
}

//same of other pins an2,an3,an4 //todo:
#endif

/* Raafat Analog Service Declaration */
BT_GATT_SERVICE_DEFINE(raafat_svc,
BT_GATT_PRIMARY_SERVICE(BT_UUID_RAAFAT),
#ifdef CONFIG_BT_RAAFAT_POLL_ANALOG
	BT_GATT_CHARACTERISTIC(BT_UUID_RAAFAT_AN1,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, read_AN1, NULL,
			       &AN1_pin_value),

	BT_GATT_CCC(raafatlc_ccc_cfg_changed,
		    BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),

	BT_GATT_CHARACTERISTIC(BT_UUID_RAAFAT_AN2,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, read_AN1, NULL,
			       &AN2_pin_value),

	BT_GATT_CCC(raafatlc_ccc_cfg_changed,
		    BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),

	BT_GATT_CHARACTERISTIC(BT_UUID_RAAFAT_AN3,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, read_AN1, NULL,
			       &AN3_pin_value),

	BT_GATT_CCC(raafatlc_ccc_cfg_changed,
		    BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),

	BT_GATT_CHARACTERISTIC(BT_UUID_RAAFAT_AN4,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, read_AN1, NULL,
			       &AN4_pin_value),

	BT_GATT_CCC(raafatlc_ccc_cfg_changed,
		    BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
#else
	BT_GATT_CHARACTERISTIC(BT_UUID_RAAFAT_AN1,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, NULL, NULL, NULL),
#endif
	// BT_GATT_CCC(raafatlc_ccc_cfg_changed,
	// 	    BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
);


int bt_raafat_init(struct bt_raafat_cb *callbacks)
{
	if (callbacks) {
		raafat_cb.AN1_read_cb    	= 	callbacks->AN1_read_cb;
		raafat_cb.AN2_read_cb 		= 	callbacks->AN2_read_cb;
		raafat_cb.AN3_read_cb 		= 	callbacks->AN3_read_cb;
		raafat_cb.AN4_read_cb 		= 	callbacks->AN4_read_cb;
	}

	return 0;
}

int bt_raafat_send_AN1_value(uint8_t analog_value, enum analog_callback_e cb_index)
{
	int err = 0;
	if (!notify_enabled) {
		return -EACCES;
	}

	err = bt_gatt_notify(NULL, &raafat_svc.attrs[cb_index], 
			      &analog_value,
			      sizeof(analog_value));

	return err; 
}