#include "handler.h"

void DelayMicroSecond(uint32_t delay_us)
{
  /* Start value then decrement */
  SysTick->LOAD = (ONE_USEC_LOAD - 0x01U);

  /* Timer start from LOAD value into below value (VAL register) */
  SysTick->VAL = RESET;

  /* Processor clock source */
  SysTick->CTRL |= (0x01U << 0x02U);
  
  /* Counter Enable */
  SysTick->CTRL |= 0x01U;

  for (volatile unsigned int i = RESET; i < delay_us; i++)
  {
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == RESET)
    {
      __NOP();
    }
  }

  /* Disable SysTick timer*/
  SysTick->CTRL = RESET;
}

void DelayMilliSecond(uint32_t delay_ms)
{

  /* Start value then decrement */
  SysTick->LOAD = (ONE_MSEC_LOAD - 0x01U);

  /* Timer start from LOAD value into below value (VAL register) */
  SysTick->VAL = RESET;

  /* Processor clock source */
  SysTick->CTRL |= (0x01U << 0x02U);
  
  /* Counter Enable */
  SysTick->CTRL |= 0x01U;

  for (volatile unsigned int i = RESET; i < delay_ms; i++)
  {
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == RESET)
    {
      __NOP();
    }
  }

  /* Disable SysTick timer*/
  SysTick->CTRL = RESET;
}

void RCC_Init(void)
{
  /* Use double-word aligned memory */
  SCB->CCR |= SCB_CCR_STKALIGN_Msk;

  /* HSI enable */
  RCC->CR |= RCC_CR_HSION;
  

  /* Enable clock for GPIOA and GPIOB */
  RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN);
}

void GPIO_Init(void)
{

  GPIOC->CRH |= 0x300000U;

  /* Enable PORTB 0-7 for D0-D7 push-pull and 50MHz max frequency */
  LCD_DATA_PORT->CRL = 0x33333333U;

  /* Enable PORTA 0-2 for RS, RW, E and 50MHz max frequency */
  LCD_CTRL_PORT->CRL |= 0x333U;
}