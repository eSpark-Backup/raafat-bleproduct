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
#include <zephyr/settings/settings.h>
#include "raafat_service.h"
#include "raafat_rgb.h"
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(bt_raafat, CONFIG_BT_RAAFAT_LOG_LEVEL);

static bool     notify_enabled;

// static uint8_t 	AN1_pin_value;
// static uint8_t 	AN2_pin_value;
// static uint8_t 	AN3_pin_value;
// static uint8_t 	AN4_pin_value;

#define DEVICE_NAME             CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN         (sizeof(DEVICE_NAME) - 1)

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

static const struct bt_data sd[] = {
	BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_RAAFAT_VAL),
};

/* Connect and disconnect callbacks */
static void connected(struct bt_conn *conn, uint8_t err)
{
	if (err) {
		printk("Connection failed (err %u)\n", err);
		return;
	}

	printk("Connected\n");
	raafat_rgb_change(BLUE, 0);
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	printk("Disconnected (reason %u)\n", reason);
	raafat_rgb_change(RED, 0);
}

#ifdef CONFIG_BT_RAAFAT_SECURITY_ENABLED
static void security_changed(struct bt_conn *conn, bt_security_t level,
			     enum bt_security_err err)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	if (!err) {
		printk("Security changed: %s level %u\n", addr, level);
	} else {
		printk("Security failed: %s level %u err %d\n", addr, level,
			err);
	}
}
#endif

BT_CONN_CB_DEFINE(conn_callbacks) = {
	.connected        = connected,
	.disconnected     = disconnected,
#ifdef CONFIG_BT_RAAFAT_SECURITY_ENABLED
	.security_changed = security_changed,
#endif
};

#if defined(CONFIG_BT_RAAFAT_SECURITY_ENABLED)
static void auth_passkey_display(struct bt_conn *conn, unsigned int passkey)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	printk("Passkey for %s: %06u\n", addr, passkey);
}

static void auth_cancel(struct bt_conn *conn)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	printk("Pairing cancelled: %s\n", addr);
}

static void pairing_complete(struct bt_conn *conn, bool bonded)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	printk("Pairing completed: %s, bonded: %d\n", addr, bonded);
}

static void pairing_failed(struct bt_conn *conn, enum bt_security_err reason)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	printk("Pairing failed conn: %s, reason %d\n", addr, reason);
}

static struct bt_conn_auth_cb conn_auth_callbacks = {
	.passkey_display = auth_passkey_display,
	.cancel = auth_cancel,
};

static struct bt_conn_auth_info_cb conn_auth_info_callbacks = {
	.pairing_complete = pairing_complete,
	.pairing_failed = pairing_failed
};
#else
static struct bt_conn_auth_cb conn_auth_callbacks;
static struct bt_conn_auth_info_cb conn_auth_info_callbacks;
#endif

static void raafatlc_ccc_cfg_changed(const struct bt_gatt_attr *attr,
				  uint16_t value)
{
	notify_enabled = (value == BT_GATT_CCC_NOTIFY);
}

static ssize_t write_raafat_json_led(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf,
			 uint16_t len, uint16_t offset, uint8_t flags)
{
	printk("Attribute write, handle: %u, conn: %p\n", attr->handle, (void *)conn);

	// if (len != 1U) {
	// 	LOG_DBG("Write led: Incorrect data length");
	// 	return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
	// }

	// if (offset != 0) {
	// 	LOG_DBG("Write led: Incorrect data offset");
	// 	return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	// }

	// if (lbs_cb.led_cb) {
		// Read the received value
		// uint8_t val = *((uint8_t *)buf);
       char* val = (char *)buf;
	   for (size_t i = 0; i < len; i++)
	   {
			/* code */
			if(val[i] == 0)
			{
				raafat_rgb_change(BLACK, 0);
			}
			if(val[i] == 1)
			{
				raafat_rgb_change(WHITE, 0);
			}
			if(val[i] == 2)
			{
				raafat_rgb_change(GREEN, 0);
			}
			if(val[i] == 3)
			{
				raafat_rgb_change(BLUE, 0);
			}
			// printk("%c\n",val[i]);
	   }

    	

	// 	if (val == 0x00 || val == 0x01) {
	// 		// Call the application callback function to update the LED state
	// 		lbs_cb.led_cb(val ? true : false);
	// 	} else {
	// 		LOG_DBG("Write led: Incorrect value");
	// 		return BT_GATT_ERR(BT_ATT_ERR_VALUE_NOT_ALLOWED);
	// 	}
	// }

	return len;
}



#ifdef CONFIG_BT_RAAFAT_POLL_ANALOG
static ssize_t read_raafat_json_packet(struct bt_conn *conn,
			  const struct bt_gatt_attr *attr,
			  void *buf,
			  uint16_t len,
			  uint16_t offset)
{
	const char *value = attr->user_data;

	LOG_DBG("Attribute read, handle: %u, conn: %p", attr->handle,
		(void *)conn);

	return bt_gatt_attr_read(conn, attr, buf, len, offset, value, strlen(value));

}
#endif


/* json packet for tesitng BLE service */
char* raafat_json_data[RAAFAT_SERVICE_JSON_PACKET_SIZE];

/* Raafat BLE Service Declaration */
BT_GATT_SERVICE_DEFINE(raafat_svc,
BT_GATT_PRIMARY_SERVICE(BT_UUID_RAAFAT),
	BT_GATT_CHARACTERISTIC(BT_UUID_RAAFAT_AN1,
			       BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_READ, read_raafat_json_packet, NULL,
			       &raafat_json_data),

#ifdef CONFIG_BT_RAAFAT_ENABLE_NOTIFY
	BT_GATT_CCC(raafatlc_ccc_cfg_changed,
		    BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
#endif			

BT_GATT_CHARACTERISTIC(BT_UUID_RAAFAT_LED,
				BT_GATT_CHRC_WRITE, BT_GATT_PERM_WRITE,
				NULL, write_raafat_json_led,
				NULL)
);

int raafat_service_send_json_packet()
{
	// printk("sending json packet!\n");
	int err = 0;
	if (!notify_enabled) {
		return -EACCES;
	}
	const char *value = "Interval Notify Todo!";

	err = bt_gatt_notify(NULL, &raafat_svc.attrs[2], 
			      value,
			      20);

	return err; 
}

int raafat_service_init()
{
	int err;
	printk("Starting Bluetooth Peripheral Raafat \n");

	if (IS_ENABLED(CONFIG_BT_RAAFAT_SECURITY_ENABLED)) {
		err = bt_conn_auth_cb_register(&conn_auth_callbacks);
		if (err) {
			printk("Failed to register authorization callbacks.\n");
			return 0;
		}

		err = bt_conn_auth_info_cb_register(&conn_auth_info_callbacks);
		if (err) {
			printk("Failed to register authorization info callbacks.\n");
			return 0;
		}
	}

	err = bt_enable(NULL);
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return 0;
	}

	printk("Bluetooth initialized\n");

	if (IS_ENABLED(CONFIG_SETTINGS)) {
		settings_load();
	}

	err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad),
			      sd, ARRAY_SIZE(sd));
	if (err) {
		printk("Advertising failed to start (err %d)\n", err);
		return 0;
	}

	printk("Advertising successfully started\n");

	return err;
}

char* raafat_service_get_json_packet_ptr()
{
	return raafat_json_data;
}