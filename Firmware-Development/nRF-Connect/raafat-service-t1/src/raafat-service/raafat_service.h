/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef BT_RAAFAT_SERVICE_H_
#define BT_RAAFAT_SERVICE_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <zephyr/types.h>

//TODO: KConfig
#define CONFIG_BT_RAAFAT_LOG_LEVEL 4
#define CONFIG_BT_RAAFAT_POLL_ANALOG
#define CONFIG_BT_RAAFAT_SECURITY_ENABLED

/** @brief Raafat Service UUID. */
#define BT_UUID_RAAFAT_VAL \
	BT_UUID_128_ENCODE(0x00001523, 0x1212, 0xefde, 0x1523, 0x785feabcd123)

/** @brief Analog Characteristics UUID. */
#define BT_UUID_RAAFAT_AN1_VAL \
	BT_UUID_128_ENCODE(0x00001528, 0x1212, 0xefde, 0x1523, 0x785feabcd123)	
#define BT_UUID_RAAFAT_AN2_VAL \
	BT_UUID_128_ENCODE(0x00001529, 0x1212, 0xefde, 0x1523, 0x785feabcd123)
#define BT_UUID_RAAFAT_AN3_VAL \
	BT_UUID_128_ENCODE(0x00001526, 0x1212, 0xefde, 0x1523, 0x785feabcd123)
#define BT_UUID_RAAFAT_AN4_VAL \
	BT_UUID_128_ENCODE(0x00001527, 0x1212, 0xefde, 0x1523, 0x785feabcd123)


// #define BT_UUID_RAAFAT        BT_UUID_DECLARE_128(BT_UUID_RAAFAT_VAL)
// #define BT_UUID_RAAFAT_AN1    BT_UUID_DECLARE_128(BT_UUID_RAAFAT_AN1_VAL)
// #define BT_UUID_RAAFAT_AN2    BT_UUID_DECLARE_128(BT_UUID_RAAFAT_AN2_VAL)
// #define BT_UUID_RAAFAT_AN3    BT_UUID_DECLARE_128(BT_UUID_RAAFAT_AN3_VAL)
// #define BT_UUID_RAAFAT_AN4    BT_UUID_DECLARE_128(BT_UUID_RAAFAT_AN4_VAL)

#define BT_UUID_RAAFAT        BT_UUID_SPS
#define BT_UUID_RAAFAT_AN1    BT_UUID_GATT_AO
#define BT_UUID_RAAFAT_AN2    BT_UUID_GATT_AO
#define BT_UUID_RAAFAT_AN3    BT_UUID_GATT_AO
#define BT_UUID_RAAFAT_AN4    BT_UUID_GATT_AO



/** @brief Callback type for when the analog pin state is changed. */
typedef uint8_t (*analog_read_cb_t)(void);

/** @brief Callback struct used by the Raafat Service. */
struct bt_raafat_cb {
	/** Analog read callback. */
	analog_read_cb_t AN1_read_cb;
	analog_read_cb_t AN2_read_cb;
	analog_read_cb_t AN3_read_cb;
	analog_read_cb_t AN4_read_cb;
};

/* Enum for all callbacks */
enum analog_callback_e {
	ANALOG_1 = 2,
	ANALOG_2 = 4,
	ANALOG_3 = 8,
	ANALOG_4 = 10,
};

/** @brief Initialize the Raafat BlE Service.
 *
 * This function registers a GATT service with 4 characteristics: Analog1, Analog2, Analog3, Analog4.
 * Send notifications for the Analog Characteristic to let connected peers know
 * when the Anlog Pin value changes.
 * Write to the LED Characteristic to change the state of the LED on the
 * board.
 *
 * @param[in] callbacks Struct containing pointers to callback functions
 *			used by the service. This pointer can be NULL
 *			if no callback functions are defined.
 *
 *
 * @retval 0 If the operation was successful.
 *           Otherwise, a (negative) error code is returned.
 */
int bt_raafat_init(struct bt_raafat_cb *callbacks);

/** @brief Send the Current state.
 *
 * This function sends a uint8_t value, to all connected peers.
 *
 * @param[in] analog_state The state of the analog pin.
 *
 * @retval 0 If the operation was successful.
 *           Otherwise, a (negative) error code is returned.
 */
int bt_raafat_send_AN1_value(uint8_t analog_value, enum analog_callback_e cb_index);

#ifdef __cplusplus
}
#endif

#endif /* BT_RAAFAT_SERVICE_H_ */
