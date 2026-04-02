#include "stm32f1xx.h"

/**
 * @brief Delay Function
 * @param delay_ms::uint32_t the delay time in miliseconds
 * @retval None
 */
void
delay(uint32_t delay_ms)
{
  uint32_t one_delay = (SystemCoreClock / 1000U) - 0x01U;

  SysTick->CTRL = 0x00U;
  SysTick->LOAD = one_delay*delay_ms;
  SysTick->VAL  = 0x00U;
  SysTick->CTRL = 0x05U;

  while ((SysTick->CTRL & 0x10000U) == 0x00U)
  {
    __NOP();
  }
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
    delay(500U);
    
    GPIOC->BSRR |= 0x20000000;
    delay(500U);
  }
  
}