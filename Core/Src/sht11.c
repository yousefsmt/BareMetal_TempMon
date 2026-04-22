#include "sht11.h"
#include "hd44780.h"

#include <stdlib.h>

void SHT11_Init()
{
    SHT11_DATA_RESET_PIN();
    SHT11_SCK_RESET_PIN();

    SHT11_DATA_OUT();
    SHT11_SCK_OUT();

    LCD_ExecuteCommand(CLEAN_DISPLAY);
    LCD_PrintString("init SHT11");
}

void SHT11_StartTransmission()
{
    SHT11_DATA_HIGH();
    SHT11_SCK_HIGH();
    DelayMicroSecond(0x01U);

    SHT11_DATA_LOW();
    DelayMicroSecond(0x01U);

    SHT11_SCK_LOW();
    DelayMicroSecond(0x01U);

    SHT11_SCK_HIGH();
    DelayMicroSecond(0x01U);

    SHT11_DATA_HIGH();
    DelayMicroSecond(0x01U);

    SHT11_SCK_LOW();
}

static uint32_t SHT11_ReadByte(uint32_t ack)
{
    uint32_t data = 0x00U;

    for (int i = 0x00; i < 0x08; i++)
    {
        data <<= 1;

        SHT11_SCK_HIGH();
        DelayMicroSecond(1);

        data |= SHT11_DATA_READ();

        SHT11_SCK_LOW();
        DelayMicroSecond(1);
    }

    SHT11_DataOut();

    if (ack == SHT11_ACK)
        SHT11_DATA_LOW();   // ACK
    else
        SHT11_DATA_HIGH();  // NACK

    DelayMicroSecond(1);
    SHT11_SCK_HIGH();
    DelayMicroSecond(1);
    SHT11_SCK_LOW();
    DelayMicroSecond(1);

    // SHT11_DATA_HIGH(); // release

    SHT11_DataIn();

    return data;
}

uint32_t SHT11_ReadData(void)
{
    uint32_t timeout = 1680000U; // Approx. 210ms
    uint16_t value   = 0x00U;

    // SHT11_DataIn();

    while ((SHT11_DATA_PIN->IDR & SHT11_DATA_BIT) && timeout--)
        ;
    
    if (timeout == 0)
        return 0xFFFF; // error

    uint32_t msb = SHT11_ReadByte(SHT11_ACK);
    uint32_t lsb = SHT11_ReadByte(SHT11_NACK);
    
    SHT11_DataOut();
    SHT11_DATA_HIGH();

    value = (msb << 8) | lsb;

    return value;
}

void SHT11_SendCommand(uint32_t cmd)
{
    SHT11_StartTransmission();
    uint32_t idx = 0x08U;

    while (idx--)
    {
        if (cmd & (0x01 << idx))
        {
            SHT11_DATA_HIGH();
        }
        else
        {
            SHT11_DATA_LOW();
        }
        DelayMicroSecond(0x01U);

        SHT11_SCK_HIGH();
        DelayMicroSecond(0x01U);
        SHT11_SCK_LOW();
        DelayMicroSecond(0x01U);
    }

    SHT11_DataIn();

    SHT11_SCK_HIGH();
    DelayMicroSecond(0x01U);

    if ((SHT11_DATA_PIN->IDR & SHT11_DATA_BIT) == SHT11_NACK)
    {
        LCD_ExecuteCommand(CLEAN_DISPLAY);
        LCD_PrintString("error cmd");
    }

    SHT11_SCK_LOW();
    DelayMicroSecond(0x01U);

}

void SHT11_DataIn()
{
    SHT11_DATA_RESET_PIN();
    SHT11_DATA_IN();
}

void SHT11_DataOut()
{
    SHT11_DATA_RESET_PIN();
    SHT11_DATA_OUT();
}