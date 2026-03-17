#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#define PERIPHERALS_BASE (0x40000000UL) // 0x4000 0000
#define RCC_OFFSET       (0x00021000UL) // 0x4002 1000
#define GPIOC_OFFSET     (0x00011000UL) // 0x4001 1000

#define RCC_BASE   (PERIPHERALS_BASE | RCC_OFFSET)   // Clock peripherals base
#define GPIOC_BASE (PERIPHERALS_BASE | GPIOC_OFFSET) // General I/O pin out base

#define RCC_CR_OFFSET       (0x00000000UL) // Clock control
#define RCC_CFGR_OFFSET     (0x00000004UL) // Clock configuration
#define RCC_CIR_OFFSET      (0x00000008UL) // Clock interrupt
#define RCC_APB2RSTR_OFFSET (0x0000000CUL) // Reset APB2 for GPIO
#define RCC_APB1RSTR_OFFSET (0x00000010UL) // Reset APB1 for GPIO
#define RCC_AHBENR_OFFSET   (0x00000014UL) // AHB clock enable
#define RCC_APB2ENR_OFFSET  (0x00000018UL) // Enable APB2 clock for GPIO
#define RCC_APB1ENR_OFFSET  (0x0000001CUL) // Enable APB1 clock for GPIO
#define RCC_BDCR_OFFSET     (0x0000001CUL) // Backup domain control
#define RCC_CSR_OFFSET      (0x00000024UL) // Control/status


#define GPIOC_CRL_OFFSET  (0x00000000UL) // Port configuration low register
#define GPIOC_CRH_OFFSET  (0x00000004UL) // Port configuration high register
#define GPIOC_IDR_OFFSET  (0x00080000UL) // Port input data register
#define GPIOC_ODR_OFFSET  (0x0000000CUL) // Port data register
#define GPIOC_BSRR_OFFSET (0x00000010UL) // Bit set/reset
#define GPIOC_BRR_OFFSET  (0x00000014UL) // Bit reset
#define GPIOC_LCKR_OFFSET (0x0000000CUL) // Configuration lock

#define RCC_CR_R       (*(volatile unsigned int*)(RCC_BASE | RCC_CR_OFFSET))
#define RCC_APB2ENR_R  (*(volatile unsigned int*)(RCC_BASE | RCC_APB2ENR_OFFSET))
#define RCC_APB2RSTR_R (*(volatile unsigned int*)(RCC_BASE | RCC_APB2RSTR_OFFSET))
#define RCC_AHBENR_R   (*(volatile unsigned int*)(RCC_BASE | RCC_AHBENR_OFFSET))
#define RCC_CFGR_R     (*(volatile unsigned int*)(RCC_BASE | RCC_CFGR_OFFSET))
#define RCC_APB1ENR_R  (*(volatile unsigned int*)(RCC_BASE | RCC_APB1ENR_OFFSET))

// #define GPIOC_CRL_R (*(volatile unsigned int*)(GPIOC_BASE | GPIOC_CRL_OFFSET))
#define GPIOC_CRH_R (*(volatile unsigned int*)(GPIOC_BASE | GPIOC_CRH_OFFSET))
#define GPIOC_ODR_R (*(volatile unsigned int*)(GPIOC_BASE | GPIOC_ODR_OFFSET))
#define GPIOC_BSRR_R (*(volatile unsigned int*)(GPIOC_BASE | GPIOC_BSRR_OFFSET))
#define GPIOC_BRR_R (*(volatile unsigned int*)(GPIOC_BASE | GPIOC_BRR_OFFSET))

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
