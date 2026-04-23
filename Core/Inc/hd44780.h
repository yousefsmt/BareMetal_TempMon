#ifndef __CORE_HD44780_H
#define __CORE_HD44780_H

#include "handler.h"

#define LCD_CTRL_PORT (GPIOB) /*!< Control connection pins */
#define LCD_DATA_PORT (GPIOA) /*!< Data connection pins */

#define RW_PIN (0x01U) /*!< Set R/W Pin A0 */
#define RS_PIN (0x02U) /*!< Set RS Pin A1 */
#define E_PIN  (0x04U) /*!< Set E Pin A2 */

#define LCD_1ST_LINE (0x80U) /*!< Set beginning of 1st line */ 
#define LCD_2ND_LINE (0xC0U) /*!< Set beginning of 2st line */

#define LCD_RS_BIT (0x01 << 0x0e) /*!< RS pin connection to PIN14 */ 
#define LCD_EN_BIT (0x01 << 0x0f) /*!< E pin connection to PIN15 */ 

#define LCD_RS_ON()  (LCD_CTRL_PORT->ODR |=  LCD_RS_BIT) /*!< Enable RS pin */
#define LCD_EN_ON()  (LCD_CTRL_PORT->ODR |=  LCD_EN_BIT) /*!< Enable E pin */
#define LCD_RS_OFF() (LCD_CTRL_PORT->ODR &= ~LCD_RS_BIT) /*!< Disable RS pin */
#define LCD_EN_OFF() (LCD_CTRL_PORT->ODR &= ~LCD_EN_BIT) /*!< Disable E pin */
#define CLEAR_DATA() (LCD_DATA_PORT->ODR &= 0xF0FFU)     /*!< Clear Data Pin D4-D7 */

/* Instruction 1 */
#define CLEAN_DISPLAY (0x01U) /*!< Cleaning display */

/* Instruction 2 */
#define INIT_CURSOR (0x02U) /*!< Return cursor to home location */

/* Instruction 3 (Input Mode)*/
#define CHAR_LEFT_SHIFT_IN    (0x04U) /*!< Shift character to left */
#define CURSOR_LEFT_SHIFT_IN  (0x05U) /*!< Shift cursor to left */
#define CHAR_RIGHT_SHIFT_IN   (0x06U) /*!< Shift character to right */
#define CURSOR_RIGHT_SHIFT_IN (0x07U) /*!< Shift cursor to left */

/* Instruction 4 */
#define OFF_DISP_HC_NF (0x08U) /*!< Display off, cursor hidden and no flashing */
#define OFF_DISP_HC_F  (0x09U) /*!< Display off, cursor hidden and flashing */
#define OFF_DISP_VC_NF (0x0aU) /*!< Display off, cursor visible and no flashing */
#define OFF_DISP_VC_F  (0x0bU) /*!< Display off, cursor visible and flashing */
#define ON_DISP_HC_NF  (0x0cU) /*!< Display on, cursor hidden and no flashing */
#define ON_DISP_HC_F   (0x0dU) /*!< Display on, cursor hidden and flashing */
#define ON_DISP_VC_NF  (0x0eU) /*!< Display on, cursor visible and no flashing */
#define ON_DISP_VC_F   (0x0fU) /*!< Display on, cursor visible and flashing */

/* Instruction 5 */
#define CURSOR_LEFT_SHIFT   (0x10U) /*!< Shift cursor to left */
#define CURSOR_RIGHT_SHIFT  (0x14U) /*!< Shift cursor to right */
#define DISPLAY_LEFT_SHIFT  (0x18U) /*!< Shift display to left */
#define DISPLAY_RIGHT_SHIFT (0x1cU) /*!< Shift display to right */

/* Instruction 6 */
#define BUS8_SINGLE_7DOT  (0x20U) /*!< 8-Bus Single Line 5*7 Dot-Matrix */
#define BUS8_SINGLE_10DOT (0x24U) /*!< 8-Bus Single Line 5*10 Dot-Matrix */
#define BUS8_TWO_7DOT     (0x28U) /*!< 8-Bus Dual Line 5*7 Dot-Matrix */
#define BUS8_TWO_10DOT    (0x23U) /*!< 8-Bus Dual Line 5*10 Dot-Matrix */
#define BUS4_SINGLE_7DOT  (0x30U) /*!< 4-Bus Single Line 5*7 Dot-Matrix */
#define BUS4_SINGLE_10DOT (0x34U) /*!< 4-Bus Single Line 5*10 Dot-Matrix */
#define BUS4_TWO_7DOT     (0x38U) /*!< 4-Bus Dual Line 5*7 Dot-Matrix */
#define BUS4_TWO_10DOT    (0x2bU) /*!< 4-Bus Dual Line 5*10 Dot-Matrix */

/* Instruction 7 */
#define GENERATE_CHAR (0x40U) /*!< Custom character */

// instruction 7 and 8 used for generate custom character and 9 is flag

/* Instruction 10 */
#define WRITE_MASK (0x200U) /*!< Write data mask */

/* Instruction 11 */
#define READ_MASK (0x300U) /*!< Read data mask */

/**
 * @brief Write Lower Nibble Bits
 * @param data set data for lower nibble port
 * @return none
 * 
 * This function operates the LCD in 4‑bit interface mode by splitting
 * an 8‑bit data value into two 4‑bit nibbles and transmitting them
 * sequentially using two enable pulses.
 */
void LCD_WriteLowerNibble(uint32_t data);

/**
 * @brief Write Upper Nibble Bits
 * @param data set data for upper nibble port
 * @return none
 * 
 * This function operates the LCD in 4‑bit interface mode by splitting
 * an 8‑bit data value into two 4‑bit nibbles and transmitting them
 * sequentially using two enable pulses.
 */
void LCD_WriteUpperNibble(uint32_t data);

/**
 * @brief Clock Pulse for E pin
 * @param none
 * @return none
 * 
 * After data is placed on pins D0–D7, this function creates the
 * required enable pulse so the LCD can latch and read the data.
 */
void LCD_Enable(void);

/**
 * @brief Execute Command
 * @param cmd Specific command
 * @return none
 * 
 * This function transmits a specific command code to the LCD module,
 * triggering the corresponding control operation (such as clearing
 * the display, setting cursor position, or configuring display modes).
 */
void LCD_ExecuteCommand(uint32_t cmd);

/**
 * @brief Put one character
 * @param data Specific character
 * @return none
 * 
 * Transmits a given character to the LCD for display at the current
 * cursor position.
 */
void LCD_PrintChar(char data);

/**
 * @brief Put character array
 * @param data Specific character array
 * @return none
 * 
 * Transmits a null-terminated string to the LCD. Each character in the
 * string is sent sequentially to the LCD, effectively printing the
 * entire string starting at the current cursor position.
 */
void LCD_PrintString(char *data);

/**
 * @brief Initialize LCD
 * @param none
 * @return none
 * 
 * Configures and sets up the LCD controller for operation. This typically
 * involves setting display parameters, clearing the screen, and positioning
 * the cursor to the home position. This function must be called before
 * any other LCD functions can be used.
 */
void LCD_Init(void);

#endif /* __CORE_HD44780_H */