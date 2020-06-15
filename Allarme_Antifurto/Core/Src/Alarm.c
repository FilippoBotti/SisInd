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

/*
 * Le variabili che importiamo sono la stringa effettiva inserita dall'utente,
 * la stringa di "hiding passowrd", il cursore per le stringhe, il numero di tentativi,
 * i booleani per verificare l'allarme e l'intrusione e i dati per il lampeggio.
 *
 */

extern char lettera[6];
extern uint8_t cursore;
extern uint8_t allarme;
extern uint32_t strobeBuffer;
extern uint8_t strobe;
uint8_t intrusion = 0;
extern uint32_t TempoAR_Pir;
extern char password[6];
extern uint8_t tentativi;

/* Funzione di inizializzazione Sensore Pir
 * Il sensore necessita di 15 secondi per essere inizializzato e poter operare
 * correttamente, durante questo tempo viene proiettata sul display
 * un'animazione. Successivamente viene mostrata la scritta "Ready"
 *
 */

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

/* Funzione di controllo della password inserita
 * Viene verificata la stringa inserita:
 * Se risulta diversa compare a display una segnalazione di password errata,
 * viene aumentato di uno il numero di tentativi e viene azzerata la password per
 * una successiva immisione, nel caso di 3 errori consecutivi viene avviato l'allarme
 * tramite l'apposita funzione
 * Se risulta corretta viene azzerata la stringa immessa e il numero dei tentativi
 * Nel caso in cui l'allarme non fosse inserito viene richiamata la funzione per inserirlo
 * Nel caso in cui l'allarme fosse inserito viene richiamata la funzione per disinserirlo
 *
 *
 */

void CheckPassword(void){
	if(strcmp(lettera,"123456")==0){
		memset(lettera,0,strlen(lettera));
		memset(password,0,strlen(password));
		cursore=-1;
		tentativi=0;
		if(allarme==0 && intrusion==0){
			AllarmeAttivo();
		}
		else {
			AllarmeDisattivato();
		}
		LedAlarm();
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

/* Funzione che inserisce l'allarme ponendo true la variabile "allarme"
 * abilita le interruzioni del sensore PIR e comunica grazie al display
 * l'attivazione dell'allarme
 *
 */

void AllarmeAttivo(void){
	allarme=1;
	PulisciSchermo();
	StampaStringaSuLCD(0, 0, "Alarm on");
}

/* Funzione che disattiva l'allarme stoppando il buzzer (PWM) e
 * spegnendo il led Rosso, vengono inoltre ripristinati i parametri
 * per il lampeggio e viene comunicato grazie al display la disattivazione
 * dell'allarme
 *
 */

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

/* Funzione di lampeggio e effettiva attuazione dell'allarme,
 * verificando che vi sia stata
 * una segnalazione da parte del sensore (o troppi tentativi di
 * immissione della password) viene attivato il buzzer e il led rosso
 * Grazie ad un boolean viene attuata l'intermittenza dell'allarme
 * e del lampeggio
 *
 */

void Sound(int strobe){
	if(intrusion){
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

/* Funzione che fa effettivamente partire l'allarme (è chiamata
 * dalle interruzioni del sensore pir)
 * Disabilita la variabile allarme per
 * far si che vengano disabilitate le interruzioni (in quanto ne basta una per
 * attivare l'allarme) e richiama la funzione di Sound() per
 * l'allarme
 *
 */

void CheckIntrusion(void){
	strobeBuffer = TEMPO_STROBE;
	intrusion=1;
	allarme = 0;
	Sound(strobe);
}

/* Funzione che gestisce i led bianchi, verde e giallo.
 * I led bianchi vengono accesi nel caso in cui è scattato
 * l'allarme e vengono successivamente spenti quando disattivato
 * Il led giallo indica allarme non inserito
 * Il led verde indica allarme inserito ma non ancora scattato
 *
 */

void LedAlarm(void){
	if(intrusion){
		HAL_GPIO_WritePin(WHITE_LED_GPIO_Port, WHITE_LED_Pin, 1);
		HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin, 0);
		HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, 0);
	}
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

}




