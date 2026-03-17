#include "main.h"

int main()
{
  RCC_CR_R &= 0xFEFFFFFF; /*PLL off*/
  RCC_CR_R |= 0x00000001; /*Turn on HSI*/

  RCC_CFGR_R &= 0xfffffffc; /*After reset switch to HSI*/

  // RCC_APB2RSTR_R |= 0x00000010; /*Reset Clock*/
  RCC_APB2ENR_R  |= 0x00000010; /*Enable clock GPIOC*/
  // RCC_APB1ENR_R  |= 0x10000000; /*Enable PWR clock*/

  GPIOC_CRH_R |= 0x00300000; /*Set mode 11 max 50MHz and set cnf 00 push pull*/
  // GPIOC_BRR_R |= 0x00000000;
  
  // GPIOC_ODR_R |= 0xffffffff;
  
  // GPIOC_BSRR_R |= 0x00002000; /**/
  GPIOC_ODR_R |= 0x20000000;
  
  while (1)
  {
    // GPIOC_ODR_R |= 0x00000000; /* Output data is 1*/
    GPIOC_BSRR_R |= 0x00002000;
    for (int i = 0; i < 1048576; i++){}
    
    
    // GPIOC_ODR_R |= 0x20000000; /* Output data is 0*/
    GPIOC_BSRR_R |= 0x20000000;
    for (int i = 0; i < 262144; i++){}

    /* code */
  }
  
  
}