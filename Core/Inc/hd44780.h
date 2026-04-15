#ifndef __CORE_HD44780_H
#define __CORE_HD44780_H

#include "handler.h"

/* Environment Setup */
#define CLEAR_DATA (0xff0000U)
#define CLEAR_CTRL (0x70000U)

#define RW_PIN (0x01U)
#define RS_PIN (0x02U)
#define E_PIN  (0x04U)

/* Instruction 1 */
#define CLEAN_DISPLAY (0x01U) /* clean all 32 characters */

/* Instruction 2 */
#define INIT_CURSOR (0x02U) /* initialize cursor at first addres on first row */

/* Instruction 3 (Input Mode)*/
#define CHAR_LEFT_SHIFT_IN    (0x04U) /* move left, shift character */
#define CURSOR_LEFT_SHIFT_IN  (0x05U) /* move left, shift cursor */
#define CHAR_RIGHT_SHIFT_IN   (0x06U) /* move right, shift character */
#define CURSOR_RIGHT_SHIFT_IN (0x07U) /* move right, shift cursor */

/* Instruction 4 */
#define OFF_DISP_HC_NF (0x08U) /* off display, hidden cursor and no flashing cursor */
#define OFF_DISP_HC_F  (0x09U) /* off display, hidden cursor and flashing cursor */
#define OFF_DISP_VC_NF (0x0aU) /* off display, visible cursor and no flashing cursor */
#define OFF_DISP_VC_F  (0x0bU) /* off display, visible cursor and flashing cursor */
#define ON_DISP_HC_NF  (0x0cU) /* on display, hidden cursor and no flashing cursor */
#define ON_DISP_HC_F   (0x0dU) /* on display, hidden cursor and flashing cursor */
#define ON_DISP_VC_NF  (0x0eU) /* on display, visible cursor and no flashing cursor */
#define ON_DISP_VC_F   (0x0fU) /* on display, visible cursor and flashing cursor */

/* Instruction 5 */
#define CURSOR_LEFT_SHIFT   (0x10U) /* cursor shift, left shift */
#define CURSOR_RIGHT_SHIFT  (0x14U) /* cursor shift, right shift */
#define DISPLAY_LEFT_SHIFT  (0x18U) /* display shift, left shift */
#define DISPLAY_RIGHT_SHIFT (0x1cU) /* display shift, right shift */

/* Instruction 6 */
#define BUS8_SINGLE_7DOT  (0x20U) /* eight bus, single line, seven dot-matrix */
#define BUS8_SINGLE_10DOT (0x24U) /* eight bus, single line, ten dot-matrix */
#define BUS8_TWO_7DOT     (0x28U) /* eight bus, two lines, seven dot-matrix */
#define BUS8_TWO_10DOT    (0x2cU) /* eight bus, two lines, ten dot-matrix */
#define BUS4_SINGLE_7DOT  (0x30U) /* four bus, single line, seven dot-matrix */
#define BUS4_SINGLE_10DOT (0x34U) /* four bus, single line, ten dot-matrix */
#define BUS4_TWO_7DOT     (0x38U) /* four bus, two lines, seven dot-matrix */
#define BUS4_TWO_10DOT    (0x3cU) /* four bus, two lines, ten dot-matrix */

#define LCD_4B_58F_2L            (0x2B) // Set to 4-bit, 5x8 dot char, 2 lines
#define LCD_8B_58F_2L            (0x23) // Set to 8-bit, 5x8 dot char, 2 lines
#define LCD_1ST_LINE             (0x80) // Go to beginning of 1st line
#define LCD_2ND_LINE             (0xC0) // Go to beginning of 2nd line

/* Instruction 7 */
#define GENERATE_CHAR (0x40U) /* for custom char */

// instruction 7 and 8 used for generate custom character and 9 is flag

/* Instruction 10 */
#define WRITE_MASK (0x200U) /* write data */

/* Instruction 11 */
#define READ_MASK (0x300U) /* read data */

void LCD_writeLowerNibble(uint8_t data);
void LCD_writeUpperNibble(uint8_t data);
void LCD_pulse_EN(void);
void LCD_cmd(uint8_t data);
void LCD_putc(char data);
void LCD_puts(char *data);
void LCD_init(void);

#endif /* __CORE_HD44780_H */