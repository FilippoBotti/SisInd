/*
 * Keyb_4x4.c
 *
 *  Created on: Feb 26, 2020
 *      Author: user
 *
*/

#include "stm32f4xx_hal.h"
#include "Keyb_4x4.h"
#include "main.h"
#include "string.h"
#include "Display_LCD.h"
#include "tim.h"
#include "Alarm.h"
#include "string.h"

uint16_t DurataValoreBasso;
uint8_t IndiceCicloKeyb4x4=0;
uint8_t CicloKeyb4x4Attivo=0;
extern char lettera[6];
extern char password[6];
extern int cursore;
uint16_t TempoAR_Keyb4x4;
uint16_t PinAttivato;

const unsigned char TastiKeyb4x4[4][4] =
	{
		{'1','2','3','A'},
		{'4','5','6','B'},
		{'7','8','9','C'},
		{'*','0','#','D'}
	};



unsigned char  TastoPremuto=0;

void AttivaPinKeyb4x4(uint8_t index)
	{
	/* provoco la rotazione del bit '0'*/

	HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin,GPIO_PIN_SET);
	switch(index)
		{
		case 0:
			HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin,GPIO_PIN_RESET);
		break;
		case 1:
			HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin,GPIO_PIN_RESET);
		break;
		case 2:
			HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin,GPIO_PIN_RESET);
		break;
		case 3:
			HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin,GPIO_PIN_RESET);
		break;
		}

	}

void StartKeyb4x4(void)
	{
    CicloKeyb4x4Attivo=1;
    DurataValoreBasso=DURATA_VALORE_BASSO;
    AttivaPinKeyb4x4(IndiceCicloKeyb4x4);
	}


/*
 * funzione utilizzata per i tempi di antirimbalzo e per la rotazione dello '0' sulle varie righe
 */
void GestioneRigheMatriceKeyb4x4(void)
	{

	if(TempoAR_Keyb4x4)   //se è attivo un tempo antirimbalzo
		{
		TempoAR_Keyb4x4--;
		if(!TempoAR_Keyb4x4)
			{
			RiconosciTastoAttivato();
			HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
			return;
			}
		}

	if(!CicloKeyb4x4Attivo) return;   //se NON devo far ruotare lo '0',esco
	DurataValoreBasso--;
	if(!DurataValoreBasso)
		{
		IndiceCicloKeyb4x4++;
		if (IndiceCicloKeyb4x4>3)
				IndiceCicloKeyb4x4=0;
		AttivaPinKeyb4x4(IndiceCicloKeyb4x4);
		DurataValoreBasso=DURATA_VALORE_BASSO;
		}
	}


void RiconosciTastoAttivato(void)
{
	uint8_t TastoAttivo=0;
	static uint8_t TastoAttivoPrec=0;
	static int8_t nTasti=0;
	switch(PinAttivato) //riconosco eventuale tasto premuto
		{
		case C1_Pin:
			if(!HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin))
				TastoAttivo=TastiKeyb4x4[IndiceCicloKeyb4x4][0];

		break;
		case C2_Pin:
			if(!HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin))
				TastoAttivo=TastiKeyb4x4[IndiceCicloKeyb4x4][1];
		break;
		case C3_Pin:
			if(!HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin))
				TastoAttivo=TastiKeyb4x4[IndiceCicloKeyb4x4][2];
		break;
		case C4_Pin:
			if(!HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin))
				TastoAttivo=TastiKeyb4x4[IndiceCicloKeyb4x4][3];
		break;
		}

	 if(!TastoAttivo)  //era un rilascio
	 	{
		if(nTasti)     //
			nTasti--;
	 	if(!nTasti)
	 	//Devo verificare che su altre righe vi siano tasti premuti, contarli ...
	 		{
	 		//Verifica che su altre righe vi siano tasti premuti, e li conta (NON SCRITTA)
	 		//nTasti=ContaTastiPremuti();
	 		DurataValoreBasso=DURATA_VALORE_BASSO;
	 		CicloKeyb4x4Attivo=1;   // al rilascio, riattivo il ciclo
	 		TastoAttivoPrec=0;
	 		}
	 	}
	 else
	 	{
	 	if(!nTasti){
	 		TastoPremuto=TastoAttivo;
	 		cursore++;
	 		if(cursore!=6){
	 			lettera[cursore]=TastoAttivo;
	 			password[cursore] = TastiKeyb4x4[3][0];
	 		}
	 		else{
	 			cursore=-1;
	 			memset(lettera,0,strlen(lettera));
	 			memset(password,0,strlen(password));
	 		}


	 	}//pubblico il tasto primario su una  riga
	 	if(TastoAttivo!=TastoAttivoPrec)   //conteggio di tasti premuti sulla
	 		nTasti++;                      //sulla stessa riga anche diversi dal primario
	 	TastoAttivoPrec=TastoAttivo;       //su questo devo ripensarci bene....
	 	}
	}


void GestioneEXTI_Keyb4x4(uint16_t GPIO_Pin)
	{
	CicloKeyb4x4Attivo=0;                 //dichiaro il ciclo di rotazione dello '0'non attivo
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);  //disabilito interruzioni 10-15
	TempoAR_Keyb4x4=TEMPO_AR_KEYB4x4;     //per un tempo di antirimbalzo
	PinAttivato= GPIO_Pin;                //catturo il pin attivato
	}

