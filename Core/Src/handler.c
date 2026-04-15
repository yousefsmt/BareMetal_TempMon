#include "handler.h"

void DelayMicroSecond(uint32_t delay_us)
{
  /* Start value then decrement */
  SysTick->LOAD = ONE_USEC_LOAD - 0x01U;

  /* Timer start from LOAD value into below value (VAL register) */
  SysTick->VAL = 0x00U;

  /* Processor clock source */
  SysTick->CTRL |= (0x01U << 0x02U);
  
  /* Counter Enable */
  SysTick->CTRL |= 0x01U;

  for (volatile unsigned int i = 0x00U; i < delay_us; i++)
  {
    while ((SysTick->CTRL & 0x10000U) == 0x00U)
    {
      __NOP();
    }
  }

  /* Disable SysTick timer*/
  SysTick->CTRL = 0x00U;
}

void DelayMilliSecond(uint32_t delay_ms)
{

  /* Start value then decrement */
  SysTick->LOAD = ONE_MSEC_LOAD - 0x01U;

  /* Timer start from LOAD value into below value (VAL register) */
  SysTick->VAL = 0x00U;

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

void RCC_Init()
{
  /* Use double-word aligned memory */
  SCB->CCR |= SCB_CCR_STKALIGN_Msk;

  /* PLL disable */
  RCC->CR &= ~(0x01U << 0x18U);

  /* CSS disable */
  RCC->CR &= ~(0x01U << 0x13U);

  /* HSE disable */
  RCC->CR &= ~(0x01U << 0x10U);

  /* HSI enable */
  RCC->CR |= (0x01U << 0x00U);

  /* Enable clock for GPIOA and GPIOB */
  RCC->APB2ENR |= (0x01U << 0x04U);
}

void GPIO_Init()
{

  GPIOC->CRH |= 0x300000U;

  /* Enable PORTB 0-7 for D0-D7 push-pull and 50MHz max frequency */
  LCD_DATA_PORT->CRL = 0x33333333U;

  /* Enable PORTA 0-2 for RS, RW, E and 50MHz max frequency */
  LCD_CTRL_PORT->CRL |= 0x333U;
}