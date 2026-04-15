#ifndef __HANDLER_H
#define __HANDLER_H

#include "stm32f1xx.h"

#define ONE_MSEC_LOAD (0x1f40U)
#define ONE_USEC_LOAD (0x08U)

#define LCD_CTRL_PORT (GPIOA)
#define LCD_DATA_PORT (GPIOB)

/**
 * @brief Delay Function
 * @param delay_us the delay time in miliseconds
 * @return none
 * This function generates an accurate microsecond-level delay using the SysTrick timer.
 */
void DelayMicroSecond(uint32_t delay_us);

/**
 * @brief Delay Function
 * @param delay_ms the delay time in miliseconds
 * @return none
 * This function generates an accurate millisecond-level delay using the SysTrick timer. 
 */
void DelayMilliSecond(uint32_t delay_ms);


void RCC_Init();
void GPIO_Init();

#endif /* __HANDLER_H */