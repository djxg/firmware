/**
 ******************************************************************************
  Copyright (c) 2013-2014 IntoRobot Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "pinmap_hal.h"
#include "pinmap_impl.h"
#include <stddef.h>

#define GPIO_0                      0
#define GPIO_1                      1
#define GPIO_2                      2
#define GPIO_3                      3
#define GPIO_4                      4
#define GPIO_5                      5
#define GPIO_6                      6
#define GPIO_7                      7
#define GPIO_8                      8
#define GPIO_9                      9
#define GPIO_10                     10
#define GPIO_11                     11
#define GPIO_12                     12
#define GPIO_13                     13
#define GPIO_14                     14
#define GPIO_15                     15
#define GPIO_16                     16
#define GPIO_17                     17


#define GPIO_PinSource0            ((uint8_t)0x00)
#define GPIO_PinSource1            ((uint8_t)0x01)
#define GPIO_PinSource2            ((uint8_t)0x02)
#define GPIO_PinSource3            ((uint8_t)0x03)
#define GPIO_PinSource4            ((uint8_t)0x04)
#define GPIO_PinSource5            ((uint8_t)0x05)
#define GPIO_PinSource6            ((uint8_t)0x06)
#define GPIO_PinSource7            ((uint8_t)0x07)
#define GPIO_PinSource8            ((uint8_t)0x08)
#define GPIO_PinSource9            ((uint8_t)0x09)
#define GPIO_PinSource10           ((uint8_t)0x0A)
#define GPIO_PinSource11           ((uint8_t)0x0B)
#define GPIO_PinSource12           ((uint8_t)0x0C)
#define GPIO_PinSource13           ((uint8_t)0x0D)
#define GPIO_PinSource14           ((uint8_t)0x0E)
#define GPIO_PinSource15           ((uint8_t)0x0F)
#define GPIO_PinSource16           ((uint8_t)0x10)


#define ADC_Channel_0  ((uint8_t)0x00)
#define TIM1           ((uint8_t)0x00)

/* Private typedef -----------------------------------------------------------*/

EESP82666_Pin_Info __PIN_MAP[TOTAL_PINS] =
{
/*
 * gpio_pin (0-16)
 * gpio_pin_source (GPIO_PinSource0 - GPIO_PinSource15)
 * timer_peripheral (TIM1 - TIM5, or NONE)
 * timer_ch (1-3, or NONE)
 * pin_mode (NONE by default, can be set to OUTPUT, INPUT, or other types)
 */

/* D0            - 00 */ { GPIO_2, GPIO_PinSource2, NONE, TIM1, PIN_MODE_NONE },
/* D1            - 01 */ { GPIO_4, GPIO_PinSource4, NONE, TIM1, PIN_MODE_NONE },
/* D2            - 02 */ { GPIO_14, GPIO_PinSource14, NONE, TIM1, PIN_MODE_NONE },
/* D3            - 03 */ { GPIO_12, GPIO_PinSource12, NONE, TIM1, PIN_MODE_NONE },
/* D4            - 04 */ { GPIO_13, GPIO_PinSource13, NONE, TIM1, PIN_MODE_NONE },
/* D5            - 05 */ { GPIO_15, GPIO_PinSource15, NONE, TIM1, PIN_MODE_NONE },
/* D6            - 06 */ { GPIO_16, GPIO_PinSource16, NONE, TIM1, PIN_MODE_NONE },
/* D7            - 07 */ { GPIO_16, GPIO_PinSource16, NONE, TIM1, PIN_MODE_NONE },
/* TX            - 08 */ { GPIO_1, GPIO_PinSource1, NONE, TIM1, PIN_MODE_NONE },
/* RX            - 09 */ { GPIO_3, GPIO_PinSource3, NONE, TIM1, PIN_MODE_NONE },
/* LED           - 10 */ { GPIO_5, GPIO_PinSource5, NONE, TIM1, NONE },
/* KEY           - 11 */ { GPIO_0, GPIO_PinSource0, NONE, TIM1, NONE },
/* NOT USED      - 12 */ { NONE, NONE, NONE, NONE, NONE },
/* NOT USED      - 13 */ { NONE, NONE, NONE, NONE, NONE },
/* NOT USED      - 14 */ { NONE, NONE, NONE, NONE, NONE },
/* NOT USED      - 15 */ { NONE, NONE, NONE, NONE, NONE },
/* NOT USED      - 16 */ { NONE, NONE, NONE, NONE, NONE },
/* NOT USED      - 17 */ { NONE, NONE, NONE, NONE, NONE },
/* NOT USED      - 18 */ { NONE, NONE, NONE, NONE, NONE },
/* NOT USED      - 19 */ { NONE, NONE, NONE, NONE, NONE },
/* NOT USED      - 20 */ { NONE, NONE, NONE, NONE, NONE },
/* NOT USED      - 21 */ { NONE, NONE, NONE, NONE, NONE },
/* NOT USED      - 22 */ { NONE, NONE, NONE, NONE, NONE },
/* NOT USED      - 23 */ { NONE, NONE, NONE, NONE, NONE },
/* NOT USED      - 24 */ { NONE, NONE, NONE, NONE, NONE },
/* NOT USED      - 25 */ { NONE, NONE, NONE, NONE, NONE },
/* NOT USED      - 26 */ { NONE, NONE, NONE, NONE, NONE },
/* NOT USED      - 27 */ { NONE, NONE, NONE, NONE, NONE },
/* NOT USED      - 28 */ { NONE, NONE, NONE, NONE, NONE },
/* NOT USED      - 29 */ { NONE, NONE, NONE, NONE, NONE },
/* A0            - 30 */ { GPIO_17, NONE, ADC_Channel_0, NONE, NONE }
};

EESP82666_Pin_Info* HAL_Pin_Map() {
    return __PIN_MAP;
}
