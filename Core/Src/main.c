#include <stdio.h>

#include "handler.h"
#include "hd44780.h"
#include "sht11.h"


int main()
{
  uint32_t ret            = 0x00U;
  char     numStr[0x10UL] = {0x00U};

  RCC_Init();
  LCD_Init();
  SHT11_Init();

  LCD_ExecuteCommand(CLEAN_DISPLAY);

  LCD_ExecuteCommand(LCD_1ST_LINE + 0x01U);
  LCD_PrintString("Temp: ");

  LCD_ExecuteCommand(LCD_2ND_LINE + 0x01U);
  LCD_PrintString("Humidity: ");

  if (ret == 0xFFFF)
  {
    LCD_PrintString("SHT11 ERR");
  }
  else
  {
    sprintf(numStr, "%lu", ret);
    LCD_PrintString(numStr);
  }
  while (1)
  {
    SHT11_SendCommand(SHT11_MEASURE_HUMIDITY);
    ret = SHT11_ReadData();
    if (ret == 0xffffU)
    {
      LCD_ExecuteCommand(CLEAN_DISPLAY);
      LCD_PrintString("SHT11 ERR");
    }
    else
    {
      sprintf(numStr, "%lu", ret);
      LCD_ExecuteCommand(LCD_1ST_LINE + 8);
      LCD_PrintString(numStr);
    }
  }
  
  return 0;
}