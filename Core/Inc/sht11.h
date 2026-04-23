#ifndef __CORE_SHT11_H
#define __CORE_SHT11_H

#include "handler.h"

#define SHT11_MEASURE_TEMPERATURE (0x03U) /*!< Start temperature measuring */
#define SHT11_MEASURE_HUMIDITY    (0x05U) /*!< Start humid measuring */
#define SHT11_READ_STATUS         (0x07U) /*!< 4-Bus Dual Line 5*10 Dot-Matrix */
#define SHT11_WRITE_STATUS        (0x06U) /*!< 4-Bus Dual Line 5*10 Dot-Matrix */
#define SHT11_SOFT_RESET          (0x1eU) /*!< 4-Bus Dual Line 5*10 Dot-Matrix */

#define SHT11_DATA_PIN (GPIOB)
#define SHT11_SCK_PIN  (GPIOB)

#define SHT11_DATA_BIT (0x01 << 0x00) /*!< Data pin connection to PIN0 */ 
#define SHT11_SCK_BIT  (0x01 << 0x01) /*!< SCK pin connection to PIN1 */ 

#define SHT11_DATA_HIGH() (SHT11_DATA_PIN->BSRR = SHT11_DATA_BIT)
#define SHT11_DATA_LOW()  (SHT11_DATA_PIN->BSRR = (SHT11_DATA_BIT << 0x10))

#define SHT11_SCK_HIGH()  (SHT11_SCK_PIN->BSRR = SHT11_SCK_BIT)
#define SHT11_SCK_LOW()   (SHT11_SCK_PIN->BSRR = (SHT11_SCK_BIT << 0x10))

#define SHT11_DATA_READ()      ((SHT11_DATA_PIN->IDR & SHT11_DATA_BIT) ? 0x01U : 0x00U)
#define SHT11_DATA_RESET_PIN() (SHT11_DATA_PIN->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0))
#define SHT11_SCK_RESET_PIN()  (SHT11_SCK_PIN->CRL  &= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1))

#define SHT11_DATA_IN()  (SHT11_DATA_PIN->CRL |= GPIO_CRL_CNF0_0)
#define SHT11_DATA_OUT() (SHT11_DATA_PIN->CRL |= (GPIO_CRL_MODE0_1 | GPIO_CRL_CNF0_0))

#define SHT11_SCK_OUT() (SHT11_SCK_PIN->CRL |= GPIO_CRL_MODE1_1)
typedef enum
{
    SHT11_ACK  = 0,
    SHT11_NACK = 1
} SHT11_Ack_t;

/**
 * @brief Initialize SHT11
 * @param none
 * @return none
 * 
 * Configures and sets up the SHT11 controller for operation.
 */
void SHT11_Init();

/**
 * @brief Send start transmission sequence to SHT11
 * @param none
 * @return none
 * 
 * Generates the specific start sequence required by the SHT11 protocol.
 */
void SHT11_StartTransmission();

/**
 * @brief Send command to SHT11 sensor
 * @param cmd 8-bit command defined by SHT11 protocol
 * @return none
 * 
 * Transmits an 8-bit command to the SHT11 over the serial interface.
 */
void SHT11_SendCommand(uint32_t cmd);

/**
 * @brief Configure DATA pin as input
 * @param none
 * @return none
 * 
 * Sets the DATA line (SDA) as input
 */
void SHT11_DataIn();

/**
 * @brief Configure DATA pin as output
 * @param none
 * @return none
 * 
 * Sets the DATA line (SDA) as output
 */
void SHT11_DataOut();

/**
 * @brief Read 16-bit data from SHT11 sensor
 * @param none
 * @return none
 * 
 * Reads a complete 16-bit measurement result from the SHT11 sensor.
 */
uint32_t SHT11_ReadData(void);

#endif /* __CORE_SHT11_H */