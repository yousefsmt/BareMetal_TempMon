#include "hd44780.h"

void LCD_WriteLowerNibble( uint32_t data )
{
  LCD_DATA_PORT->ODR &= 0xF0FFU;

  LCD_DATA_PORT->ODR |= (data & 0x0FU) << 0x08;
}

void LCD_WriteUpperNibble( uint32_t data )
{
  LCD_DATA_PORT->ODR &= 0xF0FFU;

  LCD_DATA_PORT->ODR |= (data & 0xF0) << 0x04;
}

void LCD_Enable(void)
{
  LCD_EN_ON();
  DelayMicroSecond( 0x3e8U );
  // DelayMilliSecond(0x01U);
  LCD_EN_OFF();
}

void LCD_ExecuteCommand( uint32_t data )
{

  LCD_EN_OFF();
  LCD_RS_OFF();

  LCD_WriteUpperNibble( data );

  LCD_Enable();

  LCD_WriteLowerNibble( data );

  LCD_Enable();
  DelayMicroSecond( 0x2bU );
  if(( data == CLEAN_DISPLAY ) || ( data == INIT_CURSOR ))
  {
    DelayMicroSecond( 0x5cfU );
  }
}

void LCD_PrintChar( char data )
{

  LCD_EN_OFF();
  LCD_RS_ON();

  LCD_WriteUpperNibble( data );

  LCD_Enable();

  LCD_WriteLowerNibble( data );

  LCD_Enable();
  DelayMicroSecond( 0x2bU );
}

void LCD_PrintString( char *data )
{
  uint32_t j = 0x00U;

  while( data[j] != 0x00 )
  {
    LCD_PrintChar( data[j] );
    j++;
  }
}

void LCD_Init( void )
{
  LCD_DATA_PORT->CRH &= ~( 0x03 << GPIO_CRH_CNF8_Pos  |
                   0x03 << GPIO_CRH_CNF9_Pos  |
                   0x03 << GPIO_CRH_CNF10_Pos |
                   0x03 << GPIO_CRH_CNF11_Pos ); // Clear CNF Bits

  GPIOB->CRH &= ~( 0x03 << GPIO_CRH_CNF14_Pos |
                   0x03 << GPIO_CRH_CNF15_Pos ); // Clear CNF Bits

  LCD_DATA_PORT->CRH |= ( 0x01 << GPIO_CRH_MODE8_Pos  |
                /*  0x01 << GPIO_CRH_CNF8_Pos */  
                  0x01 << GPIO_CRH_MODE9_Pos  |
                /*  0x01 << GPIO_CRH_CNF9_Pos */  
                  0x01 << GPIO_CRH_MODE10_Pos |
                /*  0x01 << GPIO_CRH_CNF10_Pos */ 
                  0x01 << GPIO_CRH_MODE11_Pos  
                /*  0x01 << GPIO_CRH_CNF11_Pos */ ); // Set Mode bits to 01

  GPIOB->CRH |= ( 0x01 << GPIO_CRH_MODE14_Pos |
                /*  0x01 << GPIO_CRH_CNF14_Pos */ 
                  0x01 << GPIO_CRH_MODE15_Pos 
                /*  0x01 << GPIO_CRH_CNF15_Pos */ ); // Set Mode bits to 01

  // Start with delay to make sure the LCD module is fully powered up.
  // DelayMicroSecond(300e3);
  DelayMilliSecond(0x12c);
  // Set EN and RS low
  LCD_EN_OFF();
  LCD_RS_OFF();
  // Write 0x02 to data pins to start 4-bit mode
  LCD_WriteLowerNibble( 0x02 );
  // Pulse EN pin to set this nibble
  LCD_Enable();

  LCD_ExecuteCommand( BUS4_TWO_10DOT );     // 4-bit, 5x8 font, 2 lines
  LCD_ExecuteCommand( CLEAN_DISPLAY );         // Clear display
  LCD_ExecuteCommand( ON_DISP_HC_NF );  // Display on, no cursor
}