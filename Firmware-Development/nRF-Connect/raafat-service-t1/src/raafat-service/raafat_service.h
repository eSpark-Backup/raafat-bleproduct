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

/** @brief Raafat Service UUID. */
#define BT_UUID_RAAFAT_VAL \
	BT_UUID_128_ENCODE(0x00001523, 0x1212, 0xefde, 0x1523, 0x785feabcd123)

/** @brief Analog Characteristics UUID. */
// #define BT_UUID_RAAFAT_AN1_VAL \
// 	BT_UUID_128_ENCODE(0x00001528, 0x1212, 0xefde, 0x1523, 0x785feabcd123)	
#define BT_UUID_RAAFAT_AN1_VAL \
	BT_UUID_128_ENCODE(0x00002, 	0x1212, 0xefde, 0x1523, 0x785feabcd123)	
// #define BT_UUID_RAAFAT_AN2_VAL \
// 	BT_UUID_128_ENCODE(0x00001529, 	0x1212, 0xefde, 0x1523, 0x785feabcd123)
// #define BT_UUID_RAAFAT_AN3_VAL \
// 	BT_UUID_128_ENCODE(0x00001526, 	0x1212, 0xefde, 0x1523, 0x785feabcd123)
// #define BT_UUID_RAAFAT_AN4_VAL \
// 	BT_UUID_128_ENCODE(0x00001527, 	0x1212, 0xefde, 0x1523, 0x785feabcd123)


// #define BT_UUID_RAAFAT        BT_UUID_DECLARE_128(BT_UUID_RAAFAT_VAL)
#define BT_UUID_RAAFAT_AN1    BT_UUID_DECLARE_128(BT_UUID_RAAFAT_AN1_VAL)
// #define BT_UUID_RAAFAT_AN2    BT_UUID_DECLARE_128(BT_UUID_RAAFAT_AN2_VAL)
// #define BT_UUID_RAAFAT_AN3    BT_UUID_DECLARE_128(BT_UUID_RAAFAT_AN3_VAL)
// #define BT_UUID_RAAFAT_AN4    BT_UUID_DECLARE_128(BT_UUID_RAAFAT_AN4_VAL)

#define BT_UUID_RAAFAT        BT_UUID_SPS
// #define BT_UUID_RAAFAT_AN1    BT_UUID_GATT_AO
// #define BT_UUID_RAAFAT_AN2    BT_UUID_GATT_AO
// #define BT_UUID_RAAFAT_AN3    BT_UUID_GATT_AO
// #define BT_UUID_RAAFAT_AN4    BT_UUID_GATT_AO


/** @brief Send the Current state.
 *
 * This function sends a uint8_t value, to all connected peers.
 *
 * @param[in] analog_state The state of the analog pin.
 *
 * @retval 0 If the operation was successful.
 *           Otherwise, a (negative) error code is returned.
 */
int raafat_service_send_json_packet();
int raafat_service_init();

#ifdef __cplusplus
}
#endif

#endif /* BT_RAAFAT_SERVICE_H_ */
