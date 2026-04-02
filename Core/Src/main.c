#include "stm32f1xx.h"

int main()
{
  RCC->CR      |= 0x01U;
  RCC->APB2ENR |= 0x10U;

  GPIOC->CRH |= 0x300000U;
  GPIOC->ODR |= 0x20000000U;
  
  while (1)
  {
    GPIOC->BSRR |= 0x2000;
    for (int i = 0; i < 100000; i++){}
    
    GPIOC->BSRR |= 0x20000000;
    for (int i = 0; i < 202144; i++){}
  }
  
}