#ifndef __CORE_SHT11_H
#define __CORE_SHT11_H

#define MEASURE_TEMPERATURE (0x03U) /*!< Start temperature measurning */
#define MEASURE_HUMIDITY    (0x05U) /*!< Start humid measurning */
#define READ_STATUS         (0x07U) /*!< 4-Bus Dual Line 5*10 Dot-Matrix */
#define WRITE_STATUS        (0x06U) /*!< 4-Bus Dual Line 5*10 Dot-Matrix */
#define SOFT_RESET          (0x1eU) /*!< 4-Bus Dual Line 5*10 Dot-Matrix */

void SHT11_Init();
void SHT11_StartTransmission();
void SHT11_ReadData();
void SHT11_WriteData();

#endif /* __CORE_SHT11_H */