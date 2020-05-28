/*
 * Display_LCD.h
 *
 *  Created on: 11 apr 2019
 *      Author: user
 */

#ifndef DISPLAY_LCD_H_
#define DISPLAY_LCD_H_


/*sono coinvolti il PORT_A, PORT_B e PORT_C*/

/*
#define PIN_D7_Pin GPIO_PIN_5
#define PIN_D7_GPIO_Port GPIOC

#define PIN_D6_Pin GPIO_PIN_12
#define PIN_D6_GPIO_Port GPIOA

#define PIN_D5_Pin GPIO_PIN_11
#define PIN_D5_GPIO_Port GPIOA

#define PIN_D4_Pin GPIO_PIN_12
#define PIN_D4_GPIO_Port GPIOB

#define PIN_EN_Pin GPIO_PIN_6
#define PIN_EN_GPIO_Port GPIOC

#define PIN_RS_Pin GPIO_PIN_8
#define PIN_RS_GPIO_Port GPIOC
*/
#define CICLI_ATTESA_PER_LCD 10



#define N_COLONNE 						16
#define N_RIGHE   						2
#define CARATTERI_PER_RIGA              16

#define         MIN_PRIMA_RIGA      	 0
#define         MAX_PRIMA_RIGA     		(0X0F)   //controllare

#define         MIN_SECONDA_RIGA      	(0X40)
#define         MAX_SECONDA_RIGA      	(0X4F)

#define 		CELLA_NASCOSTA	     	(0x10) //Da verificare in base al display usato

void init_LCD(void);
void init_pin_LCD(void);

void init_modo_4bit(void);
void SetLCD (void);
void LcdStrobe(void);
void lcd_cmd(uint8_t);
void CodeOut(uint8_t c);
void PulisciSchermo(void);
void StampaInteroSuLCD(uint8_t,uint8_t, uint16_t);
//unsigned char Uint16ToStr(char *,uint16_t);
void StampaStringaSuLCD(uint8_t,uint8_t,  char *);
void lcd_puts(char* );
void lcd_data(unsigned char );
void NascondiCursore(void);
void go_xy(char x,char y);
void testSuDueRighe(void);
void StampaCarattereSuLCD(char);



#endif /* DISPLAY_LCD_H_ */
