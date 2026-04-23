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

void SHT11_StartTransmission(void)
{
    SHT11_DataOut();    

    SHT11_DATA_HIGH();
    SHT11_SCK_LOW();
    DelayMicroSecond(0x02U);

    SHT11_SCK_HIGH();
    DelayMicroSecond(0x02U);

    SHT11_DATA_LOW();
    DelayMicroSecond(0x02U);

    SHT11_SCK_LOW();
    DelayMicroSecond(0x02U);

    SHT11_SCK_HIGH();
    DelayMicroSecond(0x02U);

    SHT11_DATA_HIGH();
    DelayMicroSecond(0x02U);

    SHT11_SCK_LOW();
    DelayMicroSecond(0x02U);
}

static uint8_t SHT11_ReadByte(uint8_t ack)
{
    uint8_t data = 0;

    SHT11_DataIn();   // ensure input

    for (int i = 0; i < 8; i++)
    {
        data <<= 1;

        SHT11_SCK_HIGH();
        DelayMicroSecond(2);

        data |= SHT11_DATA_READ();

        SHT11_SCK_LOW();
        DelayMicroSecond(2);
    }

    // ACK phase
    SHT11_DataOut();

    if (ack == SHT11_ACK)
        SHT11_DATA_LOW();
    else
        SHT11_DATA_HIGH();

    DelayMicroSecond(2);

    SHT11_SCK_HIGH();
    DelayMicroSecond(2);
    SHT11_SCK_LOW();
    DelayMicroSecond(2);

    SHT11_DATA_HIGH();   // release line
    SHT11_DataIn();

    return data;
}

uint32_t SHT11_ReadData(void)
{
    uint32_t timeout = 250000; // ~250ms

    SHT11_DataIn();

    while (SHT11_DATA_READ() && timeout--)
        DelayMicroSecond(1);

    if (timeout == 0)
        return 0xFFFF;

    uint32_t msb = SHT11_ReadByte(SHT11_ACK);
    uint32_t lsb = SHT11_ReadByte(SHT11_NACK);

    return (msb << 8) | lsb;
}

void SHT11_SendCommand(uint32_t cmd)
{
    SHT11_StartTransmission();
    SHT11_DataOut();

    for (int idx = 7; idx >= 0; idx--)
    {
        if (cmd & (1U << idx))
            SHT11_DATA_HIGH();
        else
            SHT11_DATA_LOW();

        DelayMicroSecond(2);

        SHT11_SCK_HIGH();
        DelayMicroSecond(2);
        SHT11_SCK_LOW();
        DelayMicroSecond(2);
    }

    // Release DATA for ACK
    SHT11_DATA_HIGH();
    SHT11_DataIn();

    DelayMicroSecond(2);

    // ACK clock
    SHT11_SCK_HIGH();
    DelayMicroSecond(2);

    if ((SHT11_DATA_PIN->IDR & SHT11_DATA_BIT) == SHT11_NACK)
    {
        LCD_ExecuteCommand(CLEAN_DISPLAY);
        LCD_PrintString("error cmd");
    }

    SHT11_SCK_LOW();
    DelayMicroSecond(2);
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