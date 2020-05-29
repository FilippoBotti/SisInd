/*
 * Alarm.c
 *
 *  Created on: 29 mag 2020
 *      Author: filip
 */

#include "stm32f4xx_hal.h"
#include "Keyb_4x4.h"
#include "main.h"
#include "string.h"
#include "Display_LCD.h"
#include "tim.h"
#include "Keyb_4x4.h"
#include "Alarm.h"

extern char lettera[6];
extern int cursore;
extern int allarme;
extern uint32_t strobeBuffer;
extern int strobe;
int intrusion = 0;
extern uint32_t TempoAR_Pir;
extern char password[6];
extern int tentativi;

void InitAlarm(void){
	for(int i=0; i<15; i++){
		if(i%3==0){
			PulisciSchermo();
		}

		StampaStringaSuLCD(0, 0, "Initializing");
		StampaStringaSuLCD(i%3+12, 0, ".");

		HAL_Delay(1000);
	}
	PulisciSchermo();
	StampaStringaSuLCD(0, 0, "Ready");
}


void CheckPassword(void){
	if(strcmp(lettera,"123456")==0){
		memset(lettera,0,strlen(lettera));
		memset(password,0,strlen(password));
		cursore=-1;
		tentativi=0;
		if(allarme==0){
			AllarmeAttivo();
		}
		else {
			AllarmeDisattivato();
		}
	}
	else{
		PulisciSchermo();
		StampaStringaSuLCD(0, 1, "Wrong code");
		tentativi++;
		if(tentativi==3 && !intrusion){
			allarme=1;
			CheckIntrusion();
			tentativi=0;
		}
		memset(lettera,0,strlen(lettera));
		memset(password,0,strlen(password));
		cursore=-1;
	}

}

void AllarmeAttivo(void){
	allarme=1;
	HAL_NVIC_EnableIRQ(EXTI3_IRQn);
	PulisciSchermo();
	StampaStringaSuLCD(0, 0, "Alarm on");
}

void AllarmeDisattivato(void){
	allarme=0;
	intrusion=0;
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
	HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, 0);
	PulisciSchermo();
	StampaStringaSuLCD(0, 0, "Alarm off");
	strobeBuffer=0;
	strobe = 1;
}

void Sound(int strobe){
	if(allarme&&intrusion){
		if(strobe)
		{
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
			HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, 1);
		}
		else
		{
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
			HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, 0);

		}
	}
}

void CheckIntrusion(void){
	HAL_NVIC_DisableIRQ(EXTI3_IRQn);
	strobeBuffer = TEMPO_STROBE;
	intrusion=1;
	Sound(strobe);
}

void LedAlarm(void){
	if(intrusion)
		HAL_GPIO_WritePin(WHITE_LED_GPIO_Port, WHITE_LED_Pin, 1);
	else
	    HAL_GPIO_WritePin(WHITE_LED_GPIO_Port, WHITE_LED_Pin, 0);
	if(!allarme && !intrusion)
	{
    	HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin, 1);
		HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, 0);
	}
	else if(allarme && !intrusion)
	{
		HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin, 0);
		HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, 1);
	}
	else if(allarme && intrusion)
	{
		HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin, 0);
		HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, 0);
	}
}




