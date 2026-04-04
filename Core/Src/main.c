#include "stm32f1xx.h"

#define ONE_MSEC_LOAD 0x1f40U

/**
 * @brief Delay Function
 * @param delay_ms the delay time in miliseconds
 * @return none
 */
void delay(uint32_t delay_ms)
{

  /* Start value then decrement */
  SysTick->LOAD  = ONE_MSEC_LOAD - 0x01U;

  /* Timer start from LOAD value into below value (VAL register) */
  SysTick->VAL   = 0x00U;

  /* Processor clock source */
  SysTick->CTRL |= (0x01U << 0x02U);
  
  /* Counter Enable */
  SysTick->CTRL |= 0x01U;

  for (volatile unsigned int i = 0x00U; i < delay_ms; i++)
  {
    while ((SysTick->CTRL & 0x10000U) == 0x00U)
    {
      __NOP();
    }
  }

  /* Disable SysTick timer*/
  SysTick->CTRL = 0x00U;
}

int main()
{
  SCB->CCR     |= SCB_CCR_STKALIGN_Msk; /* Use double-word aligned memory */

  RCC->CR      |= 0x01U;
  RCC->APB2ENR |= 0x10U;

  GPIOC->CRH |= 0x300000U;
  GPIOC->ODR |= 0x20000000U;
  
  while (1)
  {
    GPIOC->BSRR |= 0x2000;
    delay(1000U);
    
    GPIOC->BSRR |= 0x20000000;
    delay(1000U);
  } 
}