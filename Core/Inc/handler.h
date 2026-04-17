#ifndef __HANDLER_H
#define __HANDLER_H

#include "stm32f1xx.h"

#define ONE_MSEC_LOAD (0x1f40U) /*!< Value for create one millisecond delay for 8MHz clock base */
#define ONE_USEC_LOAD (0x08U)   /*!< Value for create one microsecond delay for 8MHz clock base */

/**
 * @brief Microsecond-level blocking delay using the SysTick timer
 * @param delay_us the delay time in microseconds
 * @return none
 * 
 * This function generates an accurate microsecond-level delay using the SysTrick timer.
 */
void DelayMicroSecond(uint32_t delay_us);

/**
 * @brief Millisecond-level blocking delay using the SysTick timer
 * @param delay_ms the delay time in miliseconds
 * @return none
 * 
 * This function generates an accurate millisecond-level delay using the SysTrick timer. 
 */
void DelayMilliSecond(uint32_t delay_ms);

/**
 * @brief Initialize and configure the Reset and Clock Control (RCC) peripheral
 * @param none
 * @return none
 * 
 * This function sets up the system clock
 */
void RCC_Init(void);

#endif /* __HANDLER_H */