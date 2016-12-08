/**
 ******************************************************************************
 * @file    pwm_hal.c
 * @authors Satish Nair, Brett Walach
 * @version V1.0.0
 * @date    12-Sept-2014
 * @brief
 ******************************************************************************
 Copyright (c) 2013-2015 IntoRobot Industries, Inc.  All rights reserved.

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
#include "hw_config.h"
#include "pwm_hal.h"
#include "gpio_hal.h"
#include "pinmap_impl.h"
#include "service_debug.h"


#define PWMRANGE 255

uint32_t pwm_mask = 0;
uint16_t pwm_values[17] = {0,};
uint32_t pwm_freq = configTIM_PWM_FREQ;
uint32_t pwm_range = PWMRANGE;

uint32_t pwm_multiplier = 0;
uint16_t pwm_steps[17];
uint8_t pwm_steps_len = 0;
uint32_t pwm_steps_mask[17];

int ICACHE_FLASH_ATTR pwm_sort_array(uint16_t a[], uint16_t al){
    uint16_t i, j;
    for (i = 1; i < al; i++) {
        uint16_t tmp = a[i];
        for (j = i; j >= 1 && tmp < a[j-1]; j--)
            a[j] = a[j-1];
        a[j] = tmp;
    }
    int bl = 1;
    for(i = 1; i < al; i++){
        if(a[i] != a[i-1]) a[bl++] = a[i];
    }
    return bl;
}

uint32_t ICACHE_FLASH_ATTR pwm_get_mask(uint16_t value){
    uint32_t mask = 0;
    int i;
    for(i=0; i<17; i++){
        if((pwm_mask & (1 << i)) != 0 && pwm_values[i] == value) mask |= (1 << i);
    }
    return mask;
}

void ICACHE_FLASH_ATTR prep_pwm_steps(){
    if(pwm_mask == 0){
        pwm_steps_len = 0;
        return;
    }

    int pwm_temp_steps_len = 0;
    uint16_t pwm_temp_steps[17];
    uint32_t pwm_temp_masks[17];

    int i;
    for(i=0; i<17; i++){
        if((pwm_mask & (1 << i)) != 0 && pwm_values[i] != 0){
            pwm_temp_steps[pwm_temp_steps_len++] = pwm_values[i];
        }
    }
    pwm_temp_steps[pwm_temp_steps_len++] = pwm_range;
    pwm_temp_steps_len = pwm_sort_array(pwm_temp_steps, pwm_temp_steps_len) - 1;
    for(i=0; i<pwm_temp_steps_len; i++){
        pwm_temp_masks[i] = pwm_get_mask(pwm_temp_steps[i]);
    }
    for(i=pwm_temp_steps_len; i>0; i--){
        pwm_temp_steps[i] = pwm_temp_steps[i] - pwm_temp_steps[i-1];
    }
    ETS_FRC1_INTR_DISABLE();
    pwm_steps_len = pwm_temp_steps_len;
    ets_memcpy(pwm_steps, pwm_temp_steps, (pwm_temp_steps_len + 1) * 2);
    ets_memcpy(pwm_steps_mask, pwm_temp_masks, pwm_temp_steps_len * 4);
    pwm_multiplier = ESP8266_CLOCK/(pwm_range * pwm_freq);
    ETS_FRC1_INTR_ENABLE();
}

void ICACHE_RAM_ATTR pwm_timer_isr(){
    static uint8_t current_step = 0;
    static uint8_t stepcount = 0;
    static uint16_t steps[17];
    static uint32_t masks[17];

    if(current_step < stepcount){
        T1L = (pwm_steps[current_step+1] * pwm_multiplier);
        TEIE |= TEIE1;
        if(masks[current_step] & 0xFFFF) GPOC = masks[current_step] & 0xFFFF;
        if(masks[current_step] & 0x10000) GP16O = 0;
        current_step++;
    } else {
        current_step = 0;
        stepcount = 0;
        if(pwm_mask == 0) return;
        T1L = (pwm_steps[current_step] * pwm_multiplier);
        TEIE |= TEIE1;
        if(pwm_mask & 0xFFFF) GPOS = pwm_mask & 0xFFFF;
        if(pwm_mask & 0x10000) GP16O = 1;
        stepcount = pwm_steps_len;
        memcpy(steps, pwm_steps, (stepcount + 1) * 2);
        memcpy(masks, pwm_steps_mask, stepcount * 4);
    }
}

void ICACHE_FLASH_ATTR pwm_start_timer(){
    timer1_disable();
    timer1_attachInterrupt(pwm_timer_isr);
    timer1_enable(TIM_DIV1, TIM_EDGE, TIM_SINGLE);
    timer1_write(1);
}

/*
 * @brief Should take an integer 0-255 and create a PWM signal with a duty cycle from 0-100%.
 * configTIM_PWM_FREQ is set at 500 Hz
 * @param pin: The select pin
 * @param value: The duty: 0-255
 * @retval None
 */
void ICACHE_FLASH_ATTR HAL_PWM_Write(uint16_t pin, uint8_t value)
{
    HAL_PWM_Write_With_Frequency_Ext(pin, (uint16_t)value, configTIM_PWM_FREQ);
}

/*
 * @brief Should take an integer 0-255 and create a PWM signal with a duty cycle from 0-100%.
 * @param pin: The select pin
 * @param value: The duty: 0-255
 * @param pwm_frequency: The frequency.
 * @retval None
 */
void ICACHE_FLASH_ATTR HAL_PWM_Write_With_Frequency(uint16_t pin, uint8_t value, uint16_t pwm_frequency)
{
    HAL_PWM_Write_With_Frequency_Ext(pin, (uint16_t)value, pwm_frequency);
}

/*
 * @brief Should take an integer within the limits of set resolution (8-bit or 16-bit)
 * and create a PWM signal with a duty cycle from 0-100%.
 * configTIM_PWM_FREQ is set at 500 Hz
 * @param pin: The select pin
 * @param value: The duty: 0-255
 * @retval None
 */
void ICACHE_FLASH_ATTR HAL_PWM_Write_Ext(uint16_t pin, uint32_t value)
{
    HAL_PWM_Write_With_Frequency_Ext(pin, value, configTIM_PWM_FREQ);
}

/*
 * @brief Should take an integer within the limits of set resolution (8-bit or 16-bit)
 * and create a PWM signal with a duty cycle from 0-100%
 * and a specified frequency.
 * @param pin: The select pin
 * @param value: The duty: 0-255
 * @param pwm_frequency: The frequency.
 * @retval None
 */
void ICACHE_FLASH_ATTR HAL_PWM_Write_With_Frequency_Ext(uint16_t pin, uint32_t value, uint32_t pwm_frequency)
{
    bool start_timer = false;
    EESP82666_Pin_Info* PIN_MAP = HAL_Pin_Map();

    pin_t gpio_pin = PIN_MAP[pin].gpio_pin;
    if(value == 0){
        pwm_mask &= ~(1 << gpio_pin);
        prep_pwm_steps();
        HAL_GPIO_Write(pin, 0);
        if(pwm_mask == 0) timer1_disable();
        return;
    }
    if((pwm_mask & (1 << gpio_pin)) == 0){
        if(pwm_mask == 0) start_timer = true;
        pwm_mask |= (1 << gpio_pin);
        HAL_Pin_Mode(pin, OUTPUT);
        HAL_GPIO_Write(pin, 0);
    }
    DEBUG_D("pwm_mask = %x", pwm_mask);
    pwm_values[gpio_pin] = value % (pwm_range + 1);
    pwm_freq = pwm_frequency;
    prep_pwm_steps();
    if(start_timer){
        pwm_start_timer();
    }
}

uint16_t ICACHE_FLASH_ATTR HAL_PWM_Get_Frequency(uint16_t pin)
{
    return HAL_PWM_Get_Frequency_Ext(pin);
}

uint16_t ICACHE_FLASH_ATTR HAL_PWM_Get_AnalogValue(uint16_t pin)
{
    return HAL_PWM_Get_AnalogValue_Ext(pin);
}


uint32_t ICACHE_FLASH_ATTR HAL_PWM_Get_Frequency_Ext(uint16_t pin)
{
    return pwm_freq;
}

uint32_t ICACHE_FLASH_ATTR HAL_PWM_Get_AnalogValue_Ext(uint16_t pin)
{
    return 0;
}

uint32_t ICACHE_FLASH_ATTR HAL_PWM_Get_Max_Frequency(uint16_t pin)
{
    return 0;
}

void HAL_PWM_UpdateDutyCycle(uint16_t pin, uint16_t value)
{
}

void HAL_PWM_UpdateDutyCycle_Ext(uint16_t pin, uint32_t value)
{
}

uint8_t HAL_PWM_Get_Resolution(uint16_t pin)
{
    return 0;
}

void HAL_PWM_Set_Resolution(uint16_t pin, uint8_t resolution)
{
}
