#include "hd44780.h"

#define LCD_RS_BIT (1<<14)
#define LCD_EN_BIT (1<<15)

#define LCD_RS_ON()  (GPIOB->ODR |=  LCD_RS_BIT)
#define LCD_EN_ON()  (GPIOB->ODR |=  LCD_EN_BIT)
#define LCD_RS_OFF() (GPIOB->ODR &= ~LCD_RS_BIT)
#define LCD_EN_OFF() (GPIOB->ODR &= ~LCD_EN_BIT)

// #define LCD_CLEAR                0x01 // Clear display
// #define LCD_HOME                 0x02 // Move cursor home
// #define LCD_OFF                  0x08 // Disable LCD
// #define LCD_ON_NO_CURSOR         0x0C // Turn on LCD, no cursor
// #define LCD_ON_BLINK_CURSOR      0x0D // Turn on LCD, blinking block cursor
// #define LCD_ON_LINE_CURSOR       0x0E // Turn on LCD, line cursor
// #define LCD_ON_LINE_BLINK_CURSOR 0x0F // Turn on LCD, blinking line cursor
// #define LCD_4B_58F_2L            0x2B // Set to 4-bit, 5x8 dot char, 2 lines
// #define LCD_8B_58F_2L            0x23 // Set to 8-bit, 5x8 dot char, 2 lines
// #define LCD_1ST_LINE             0x80 // Go to beginning of 1st line
// #define LCD_2ND_LINE             0xC0 // Go to beginning of 2nd line


void
LCD_writeLowerNibble( uint32_t data )
{
  GPIOA->ODR &= 0xF0FFU;    // Clear GPIO A[11:8]
  // Mask off the lower nibble of data, shift 8 bits to the left, and write those bits
  // to the newly cleared nibble from A[11:8]
  GPIOA->ODR |= (data & 0x0FU) << 0x08;
}

void
LCD_writeUpperNibble( uint32_t data )
{
  GPIOA->ODR &= 0xF0FFU;    // Clear GPIO A[11:8]
  // Mask off the upper nibble of data, shift 4 bits to the left, and write those bits
  // to the newly cleared nibble from A[11:8]
  GPIOA->ODR |= (data & 0xF0) << 0x04;
}

//  LCD_pulse_EN
//  Make EN high, wait for 1 ms, and then bring it down low. This longish timing requirement
//  seems to be necessary due to 4-bit processing.
void
LCD_pulse_EN(void)
{
  LCD_EN_ON();
  DelayMicroSecond( 1000U );
  // DelayMilliSecond(0x01U);
  LCD_EN_OFF();
}


//  LCD_cmd
//  Send a 4-bit command to the LCD
void
LCD_cmd( uint32_t data )
{
  // Make sure EN and RS are low
  LCD_EN_OFF();
  LCD_RS_OFF();
  // Place upper nibble of command on GPIOA[11:8]
  LCD_writeUpperNibble( data );
  // Pulse EN pin to set this nibble
  LCD_pulse_EN();
  // Place lower nibble of command on GPIOA[11:8]
  LCD_writeLowerNibble( data );
  // Pulse EN pin to set this nibble
  LCD_pulse_EN();
  DelayMicroSecond( 43 );
  if(( data == CLEAN_DISPLAY ) || ( data == INIT_CURSOR ))
  {
    DelayMicroSecond( 1487 );
  }
}


//  LCD_putc
//  Send a character to the LCD
void
LCD_putc( char data )
{
  // Set EN low, and RS high
  LCD_EN_OFF();
  LCD_RS_ON();
  // Place upper nibble of character on GPIOA[11:8]
  LCD_writeUpperNibble( data );
  // Pulse EN pin to set this nibble
  LCD_pulse_EN();
  // Place lower nibble of command on GPIOA[11:8]
  LCD_writeLowerNibble( data );
  // Pulse EN pin to set this nibble
  LCD_pulse_EN();
  DelayMicroSecond( 43 );
}


//  LCD_puts
//  Takes a pointer to a null-terminated string and displays that string
//  from the current LCD cursor position. Does not check for LCD line/string
//  overflow.
void
LCD_puts( char *data )
{
  uint32_t j = 0x00U;

  while( data[j] != 0x00 )
  {
    LCD_putc( data[j] );
    j++;
  }
}

void
LCD_init( void )
{
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN |
                  RCC_APB2ENR_IOPBEN;           // Enable GPIO Ports A and B

  GPIOA->CRH &= ~( 0x03 << GPIO_CRH_CNF8_Pos  |
                   0x03 << GPIO_CRH_CNF9_Pos  |
                   0x03 << GPIO_CRH_CNF10_Pos |
                   0x03 << GPIO_CRH_CNF11_Pos ); // Clear CNF Bits

  GPIOB->CRH &= ~( 0x03 << GPIO_CRH_CNF14_Pos |
                   0x03 << GPIO_CRH_CNF15_Pos ); // Clear CNF Bits

  GPIOA->CRH |= ( 0x01 << GPIO_CRH_MODE8_Pos  |
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
  DelayMicroSecond(300e3);
  // Set EN and RS low
  LCD_EN_OFF();
  LCD_RS_OFF();
  // Write 0x02 to data pins to start 4-bit mode
  LCD_writeLowerNibble( 0x02 );
  // Pulse EN pin to set this nibble
  LCD_pulse_EN();

  LCD_cmd( BUS4_TWO_10DOT );     // 4-bit, 5x8 font, 2 lines
  LCD_cmd( CLEAN_DISPLAY );         // Clear display
  LCD_cmd( ON_DISP_HC_NF );  // Display on, no cursor
}