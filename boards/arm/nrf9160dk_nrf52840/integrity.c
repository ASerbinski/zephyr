/*
 * Copyright (c) 2018-2020 Nordic Semiconductor ASA.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>

/* The following asserts ensure compile-time consistency between the macros
 * used in board.c and the ones defined in Kconfig.
 */

BUILD_ASSERT(IS_ENABLED(CONFIG_BOARD_NRF9160DK_INTERFACE0_MCU) ||
	     IS_ENABLED(CONFIG_BOARD_NRF9160DK_INTERFACE0_ARDUINO),
	     "Invalid MCU interface 0 routing");
BUILD_ASSERT(IS_ENABLED(CONFIG_BOARD_NRF9160DK_INTERFACE1_MCU) ||
	     IS_ENABLED(CONFIG_BOARD_NRF9160DK_INTERFACE1_TRACE),
	     "Invalid MCU interface 1 routing");
BUILD_ASSERT(IS_ENABLED(CONFIG_BOARD_NRF9160DK_INTERFACE2_MCU) ||
	     IS_ENABLED(CONFIG_BOARD_NRF9160DK_INTERFACE2_COEX),
	     "Invalid MCU interface 2 routing");
BUILD_ASSERT(IS_ENABLED(CONFIG_BOARD_NRF9160DK_UART0_VCOM) ||
	     IS_ENABLED(CONFIG_BOARD_NRF9160DK_UART0_ARDUINO),
	     "Invalid nRF9160 UART0 routing");
BUILD_ASSERT(IS_ENABLED(CONFIG_BOARD_NRF9160DK_UART1_VCOM) ||
	     IS_ENABLED(CONFIG_BOARD_NRF9160DK_UART1_ARDUINO),
	     "Invalid nRF9160 UART1 routing");
BUILD_ASSERT(IS_ENABLED(CONFIG_BOARD_NRF9160DK_LED0_PHY) ||
	     IS_ENABLED(CONFIG_BOARD_NRF9160DK_LED0_ARDUINO),
	     "Invalid LED 1 routing");
BUILD_ASSERT(IS_ENABLED(CONFIG_BOARD_NRF9160DK_LED1_PHY) ||
	     IS_ENABLED(CONFIG_BOARD_NRF9160DK_LED1_ARDUINO),
	     "Invalid LED 2 routing");
BUILD_ASSERT(IS_ENABLED(CONFIG_BOARD_NRF9160DK_LED2_PHY) ||
	     IS_ENABLED(CONFIG_BOARD_NRF9160DK_LED2_ARDUINO),
	     "Invalid LED 3 routing");
BUILD_ASSERT(IS_ENABLED(CONFIG_BOARD_NRF9160DK_LED3_PHY) ||
	     IS_ENABLED(CONFIG_BOARD_NRF9160DK_LED3_ARDUINO),
	     "Invalid LED 4 routing");
BUILD_ASSERT(IS_ENABLED(CONFIG_BOARD_NRF9160DK_BUTTON0_PHY) ||
	     IS_ENABLED(CONFIG_BOARD_NRF9160DK_BUTTON0_ARDUINO),
	     "Invalid button 1 routing");
BUILD_ASSERT(IS_ENABLED(CONFIG_BOARD_NRF9160DK_BUTTON1_PHY) ||
	     IS_ENABLED(CONFIG_BOARD_NRF9160DK_BUTTON1_ARDUINO),
	     "Invalid button 2 routing");
BUILD_ASSERT(IS_ENABLED(CONFIG_BOARD_NRF9160DK_SWITCH0_PHY) ||
	     IS_ENABLED(CONFIG_BOARD_NRF9160DK_SWITCH0_ARDUINO),
	     "Invalid switch 1 routing");
BUILD_ASSERT(IS_ENABLED(CONFIG_BOARD_NRF9160DK_SWITCH1_PHY) ||
	     IS_ENABLED(CONFIG_BOARD_NRF9160DK_SWITCH1_ARDUINO),
	     "Invalid switch 2 routing");

BUILD_ASSERT(!IS_ENABLED(CONFIG_BOARD_NRF9160DK_NRF52840_RESET) ||
	     IS_ENABLED(CONFIG_BOARD_NRF9160DK_NRF52840_RESET_P0_17) ||
	     IS_ENABLED(CONFIG_BOARD_NRF9160DK_NRF52840_RESET_P0_20) ||
	     IS_ENABLED(CONFIG_BOARD_NRF9160DK_NRF52840_RESET_P0_15) ||
	     IS_ENABLED(CONFIG_BOARD_NRF9160DK_NRF52840_RESET_P0_22) ||
	     IS_ENABLED(CONFIG_BOARD_NRF9160DK_NRF52840_RESET_P1_04) ||
	     IS_ENABLED(CONFIG_BOARD_NRF9160DK_NRF52840_RESET_P1_02),
	     "No reset line selected, please check Kconfig macros");
