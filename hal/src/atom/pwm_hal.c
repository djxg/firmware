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
#include "pwm_hal.h"
#include "pinmap_impl.h"
#include "service_debug.h"

void HAL_PWM_Write(uint16_t pin, uint8_t value)
{
    HAL_PWM_Write_With_Frequency_Ext(pin, (uint16_t)value, configTIM_PWM_FREQ);
}

void HAL_PWM_Write_With_Frequency(uint16_t pin, uint8_t value, uint16_t pwm_frequency)
{
    HAL_PWM_Write_With_Frequency_Ext(pin, (uint16_t)value, pwm_frequency);
}

void HAL_PWM_Write_Ext(uint16_t pin, uint32_t value)
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
void HAL_PWM_Write_With_Frequency_Ext(uint16_t pin, uint32_t value, uint32_t pwm_frequency)
{
    //DEBUG("Enter HAL_PWM_Write_With_Frequency_Ext...\r\n");
    //Map the pin to the appropriate port and pin on the STM32
    STM32_Pin_Info* PIN_MAP = HAL_Pin_Map();

    // exclude TIM1 for own use
    if(PIN_MAP[pin].timer_peripheral != NULL) //&& PIN_MAP[pin].timer_peripheral != TIM1)
    {
        //DEBUG("PWM GPIO Configuration...\r\n");
        /* Common configuration for all channles */
        GPIO_InitTypeDef GPIO_InitStruct;
        GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
        GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

        // else if( (PIN_MAP[pin].timer_peripheral == TIM2) )
        if( (PIN_MAP[pin].timer_peripheral == TIM2) )
        {
            //DEBUG("PWM TIM2  Configuration...\r\n");
            __HAL_RCC_TIM2_CLK_ENABLE();
            /* GPIO_InitStruct.Alternate = GPIO_AF1_TIM2; */
            GPIO_InitStruct.Pin       = PIN_MAP[pin].gpio_pin;
            /* Port Clock enable */
            if( (PIN_MAP[pin].gpio_peripheral == GPIOA) )
            {
                __HAL_RCC_GPIOA_CLK_ENABLE();
                HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
                DEBUG("pwm time2 gpioa\r\n");
            }
            else if( (PIN_MAP[pin].gpio_peripheral == GPIOB) )
            {
                __HAL_RCC_GPIOB_CLK_ENABLE();
                HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
            }
            else if( (PIN_MAP[pin].gpio_peripheral == GPIOC) )
            {
                    __HAL_RCC_GPIOC_CLK_ENABLE();
                    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
            }
            else if( (PIN_MAP[pin].gpio_peripheral == GPIOD) )
            {
                    __HAL_RCC_GPIOD_CLK_ENABLE();
                    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
            }

        }
        else if( (PIN_MAP[pin].timer_peripheral == TIM3) )
        {
            //DEBUG("PWM TIM3  Configuration...\r\n");
            __HAL_RCC_TIM3_CLK_ENABLE();
            /* GPIO_InitStruct.Alternate = GPIO_AF2_TIM3; */
            GPIO_InitStruct.Pin       = PIN_MAP[pin].gpio_pin;

            /* Port Clock enable */
            if( (PIN_MAP[pin].gpio_peripheral == GPIOA) )
            {
                __HAL_RCC_GPIOA_CLK_ENABLE();
                HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
            }
            else if( (PIN_MAP[pin].gpio_peripheral == GPIOB) )
            {
                //DEBUG("PWM TIM3 GPIOB CLK ENABLE and GPIO Init\r\n");
                __HAL_RCC_GPIOB_CLK_ENABLE();
                HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
            }
            else if( (PIN_MAP[pin].gpio_peripheral == GPIOC) )
            {
                __HAL_RCC_GPIOC_CLK_ENABLE();
                HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
            }
            else if( (PIN_MAP[pin].gpio_peripheral == GPIOD) )
            {
                __HAL_RCC_GPIOD_CLK_ENABLE();
                HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
            }
        }
        else if( (PIN_MAP[pin].timer_peripheral == TIM4) )
        {
            //DEBUG("PWM TIM4  Configuration...\r\n");
            __HAL_RCC_TIM4_CLK_ENABLE();
            /* GPIO_InitStruct.Alternate = GPIO_AF3_TIM9; */
            GPIO_InitStruct.Pin       = PIN_MAP[pin].gpio_pin;

            /* Port Clock enable */
            if( (PIN_MAP[pin].gpio_peripheral == GPIOA) )
            {
                __HAL_RCC_GPIOA_CLK_ENABLE();
                HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
            }
            else if( (PIN_MAP[pin].gpio_peripheral == GPIOB) )
            {
                __HAL_RCC_GPIOB_CLK_ENABLE();
                HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
            }
            else if( (PIN_MAP[pin].gpio_peripheral == GPIOC) )
            {
                __HAL_RCC_GPIOC_CLK_ENABLE();
                HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
            }
            else if( (PIN_MAP[pin].gpio_peripheral == GPIOD) )
            {
                __HAL_RCC_GPIOD_CLK_ENABLE();
                HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
            }
        }
        //DEBUG("SystemCoreClock: %ld\r\n", SystemCoreClock);
        //DEBUG("pwm_frequency: %ld\r\n", pwm_frequency);
        //DEBUG("value: %ld\r\n", value);

#define TIM_COUNTER_CLOCK_FREQ 1000000 // in the param, the freq should be above 16 - 10000000
        // XXX:Note TIM_Prescaler and TIM_ARR and TIMCCR  should be
        // a number between 0x0000U and 0xFFFFU (0-65535)
        // XXX: Note here SystemCoreClock Should be TIM CLK, here equal
        // TIM_CLK should be set in the above code.
        /*##-1- Configure the TIM peripheral #######################################*/
        uint32_t TIM_Prescaler = (uint32_t)((SystemCoreClock / TIM_COUNTER_CLOCK_FREQ) - 1);

        uint32_t TIM_ARR = (uint32_t)((TIM_COUNTER_CLOCK_FREQ / pwm_frequency) - 1);
        uint32_t TIM_CCR = (uint32_t)(value * (TIM_ARR + 1) / 255);

        //DEBUG("TIM_Prescaler: %d\r\n", TIM_Prescaler);
        //DEBUG("TIM_ARR: %d\r\n", TIM_ARR);
        //DEBUG("TIM_CCR: %d\r\n", TIM_CCR);

        TIM_HandleTypeDef TimHandle;
        TIM_OC_InitTypeDef sConfig;

        TimHandle.Instance = PIN_MAP[pin].timer_peripheral;
        TimHandle.Init.Prescaler         = TIM_Prescaler;
        TimHandle.Init.Period            = TIM_ARR;
        TimHandle.Init.ClockDivision     = 0;
        TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
       // TimHandle.Init.RepetitionCounter = 0;
        if (HAL_TIM_PWM_Init(&TimHandle) != HAL_OK)
        {
            // Error
            DEBUG("PWM Init Error!\r\n");
        }

        /*##-2- Configure the PWM channels #b########################################*/
        /* Common configuration for all channels */
        sConfig.OCMode       = TIM_OCMODE_PWM1;
        sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;
        sConfig.OCFastMode   = TIM_OCFAST_DISABLE;
       // sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;

        /* Set the pulse value for channel 1 */
        sConfig.Pulse = TIM_CCR;
        if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, PIN_MAP[pin].timer_ch) != HAL_OK)
        {
            /* Configuration Error */
            DEBUG("PWM Configuration Error!\r\n");
        }

        /* Start channel */
        if (HAL_TIM_PWM_Start(&TimHandle, PIN_MAP[pin].timer_ch) != HAL_OK)
        {
            /* PWM Generation Error */
            DEBUG("PWM Generation Error!\r\n");
        }
    }
    else
    {
        // Error
        DEBUG("PWM First Error!\r\n");
    }
}

uint16_t HAL_PWM_Get_Frequency(uint16_t pin)
{
    return 0;
}

uint16_t HAL_PWM_Get_AnalogValue(uint16_t pin)
{
    return 0;
}
