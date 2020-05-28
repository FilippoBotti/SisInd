/*
 * Keyb_4x4.h
 *
 *  Created on: Feb 26, 2020
 *      Author: user
 */

#ifndef INC_KEYB_4X4_H_
#define INC_KEYB_4X4_H_

#define DURATA_VALORE_BASSO 10
#define TEMPO_AR_KEYB4x4 100
#define TEMPO_STROBE 500
#define TEMPO_AR_PIR 400
extern unsigned char TastoPremuto;
extern uint8_t CicloKeyb4x4Attivo;

void GestioneRigheMatriceKeyb4x4(void);
void StartKeyb4x4(void);
void GestioneARButton(void);
void AttivaPinKeyb4x4(uint8_t index);
void GestioneEXTI_Keyb4x4(uint16_t GPIO_Pin);
void RiconosciTastoAttivato(void);
void CheckPassword(void);
void Sound(int strobe);
void CheckIntrusion(void);
void LedAlarm(void);

#endif /* INC_KEYB_4X4_H_ */
