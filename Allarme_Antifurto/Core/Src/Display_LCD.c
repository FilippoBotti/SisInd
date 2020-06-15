/*
 * Display_LCD.c
 *
 *  Created on: 11 apr 2019
 *      Author: user
 */

#include <stdlib.h>
#include "stm32f4xx_hal.h"
#include "Display_LCD.h"
#include "main.h"

/*
 * Funzione di inizializzazione display lcd
 */
void init_LCD(void)
	{
	init_modo_4bit();
	SetLCD ();
	go_xy(0,0);
	}

/*
 * Funzione di test display lcd, utilizzata solo in una
 * prima fase di debug e successivamente rimossa dal codice
 */
void testSuDueRighe(void)
	{
	char str[21];
	StampaStringaSuLCD(0,0,"Prima Riga ABCDE");
	int n=1234567890;
	itoa(n,str,10);
	StampaStringaSuLCD(0,1,str);
	n=654321;
	itoa(n,str,10);
	StampaStringaSuLCD(10,1,str);
	}


/* il display e' controllato da 6 PIN :
 * 2 di controllo RS e EN   con clock
 * 4 di dati D4,D5,D6,D7
 *
 */
void init_modo_4bit(void)
	{
	HAL_Delay(50);
    //0011xxxx
	HAL_GPIO_WritePin(PIN_D7_GPIO_Port,PIN_D7_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D6_GPIO_Port,PIN_D6_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D5_GPIO_Port,PIN_D5_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(PIN_D4_GPIO_Port,PIN_D4_Pin,GPIO_PIN_SET);
    //spedizione del dato 0x33 attraveso 2 nibble 0x03 e 0x03
	LcdStrobe();
	HAL_Delay(10);          //questi ritardi possono diminuire
	LcdStrobe();
	HAL_Delay(10);
	//spedizione del dato 0x32 attraveso 2 nibble 0x03 e 0x02
	LcdStrobe();
	HAL_Delay(10);
    //0010xxxx
	HAL_GPIO_WritePin(PIN_D4_GPIO_Port,PIN_D4_Pin,GPIO_PIN_RESET);
	LcdStrobe();
	HAL_Delay(10);
	HAL_GPIO_WritePin(PIN_D5_GPIO_Port,PIN_D5_Pin,GPIO_PIN_RESET);
	//il display ha acquisito la modalit� 4 bit;
	}

void SetLCD (void)
 	 {
	//Initializza LCD  vedi DisplayTech 204_a_serie.pdf pag 5
	HAL_Delay(10);
	lcd_cmd(0x28); //0010 1000 Function Set:  4 bit, 2 linee, 5x7

	HAL_Delay(10);
	lcd_cmd(0xC);  //0000 1100  Display On, Cursor Off, No Cursor Blink

	HAL_Delay(10);
	lcd_cmd(0x6);  //0000 0110 Entry Mode  cursore avanti

	HAL_Delay(10);
	lcd_cmd(0x80); //Initialize DDRAM address to zero

	HAL_Delay(10);
	lcd_cmd(0x1);  //0000 0001 Display Clear

	HAL_Delay(10);
	lcd_cmd(0x2);  //0000 0010 prima posizione

	HAL_Delay(20); //perchè sia chiaro che sto partendo/ripartendo
 }




void LcdStrobe(void)
	{
	uint8_t i;
	HAL_GPIO_WritePin(PIN_EN_GPIO_Port,PIN_EN_Pin,GPIO_PIN_SET);
	for (i=0;i < CICLI_ATTESA_PER_LCD;i++);
	HAL_GPIO_WritePin(PIN_EN_GPIO_Port,PIN_EN_Pin,GPIO_PIN_RESET);
	}

void lcd_cmd(uint8_t c)
	{
	HAL_Delay(2);
	//HAL_Delay(0);
	HAL_GPIO_WritePin(PIN_RS_GPIO_Port,PIN_RS_Pin,GPIO_PIN_RESET);
	CodeOut(c);
	}

void CodeOut(uint8_t c)
	{
	HAL_GPIO_WritePin(PIN_D7_GPIO_Port,PIN_D7_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D6_GPIO_Port,PIN_D6_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D5_GPIO_Port,PIN_D5_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D4_GPIO_Port,PIN_D4_Pin,GPIO_PIN_RESET);

	if(c&0x80)
		HAL_GPIO_WritePin(PIN_D7_GPIO_Port,PIN_D7_Pin,GPIO_PIN_SET);
	if(c&0x40)
		HAL_GPIO_WritePin(PIN_D6_GPIO_Port,PIN_D6_Pin,GPIO_PIN_SET);
	if(c&0x20)
		HAL_GPIO_WritePin(PIN_D5_GPIO_Port,PIN_D5_Pin,GPIO_PIN_SET);
	if(c&0x10)
		HAL_GPIO_WritePin(PIN_D4_GPIO_Port,PIN_D4_Pin,GPIO_PIN_SET);
	LcdStrobe();

	HAL_GPIO_WritePin(PIN_D7_GPIO_Port,PIN_D7_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D6_GPIO_Port,PIN_D6_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D5_GPIO_Port,PIN_D5_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D4_GPIO_Port,PIN_D4_Pin,GPIO_PIN_RESET);

	if(c&0x8)
		HAL_GPIO_WritePin(PIN_D7_GPIO_Port,PIN_D7_Pin,GPIO_PIN_SET);
	if(c&0x4)
		HAL_GPIO_WritePin(PIN_D6_GPIO_Port,PIN_D6_Pin,GPIO_PIN_SET);
	if(c&0x2)
		HAL_GPIO_WritePin(PIN_D5_GPIO_Port,PIN_D5_Pin,GPIO_PIN_SET);
	if(c&0x1)
		HAL_GPIO_WritePin(PIN_D4_GPIO_Port,PIN_D4_Pin,GPIO_PIN_SET);
	LcdStrobe();

	HAL_GPIO_WritePin(PIN_D7_GPIO_Port,PIN_D7_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D6_GPIO_Port,PIN_D6_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D5_GPIO_Port,PIN_D5_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PIN_D4_GPIO_Port,PIN_D4_Pin,GPIO_PIN_RESET);
	}


void PulisciSchermo(void)   //testata
  	{
   	lcd_cmd(0x1);
  	}

/*
 Stampa un intero nella posizione Colonna Riga
 */
void StampaInteroSuLCD(unsigned char Colonna,unsigned char Riga,uint16_t valore)
	{
	char str[10];
	itoa(valore,str,10);
	StampaStringaSuLCD(Colonna,Riga,str);
	}

/*sposta il cursore su x=colonna, y=riga */
void go_xy(char x,char y)
	{
	unsigned char base=0;
	switch(y)
    	{
    	case 0:
    		base=MIN_PRIMA_RIGA;
    	break;
    	case 1:
    		base=MIN_SECONDA_RIGA;
    	break;
    	}
    x+=base;
    lcd_cmd(x|0X80);
    }


/*
 * Stampa una stringa nella posizione colonna, riga (la stringa non deve oltrepassare
 * il bordo
 *
 */
void StampaStringaSuLCD(uint8_t colonna,uint8_t riga, char *p)   //riga e colonna poi stringa
  	{
   	go_xy(colonna,riga) ;
   	lcd_puts(p);
  	}


void StampaCarattereSuLCD(char c)
	{
	lcd_data(c);
	}

/* stampa il carattere *s*/
void lcd_puts(char * s)
	{
	while(*s)
		lcd_data(*s++);
	}

/* Invia un carattere all'LCD */
void lcd_data(unsigned char c)
	{
	HAL_Delay(0);
	HAL_GPIO_WritePin(PIN_RS_GPIO_Port,PIN_RS_Pin,GPIO_PIN_SET);
	CodeOut(c);
	HAL_GPIO_WritePin(PIN_RS_GPIO_Port,PIN_RS_Pin,GPIO_PIN_RESET);
	}


