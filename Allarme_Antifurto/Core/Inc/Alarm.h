/*
 * Alarm.h
 *
 *  Created on: 29 mag 2020
 *      Author: filip
 */

#ifndef INC_ALARM_H_
#define INC_ALARM_H_
#define TEMPO_STROBE 500
#define TEMPO_AR_PIR 400

void CheckPassword(void);
void Sound(int strobe);
void CheckIntrusion(void);
void LedAlarm(void);
void InitAlarm(void);
void AllarmeAttivo(void);
void AllarmeDisattivato(void);

#endif /* INC_ALARM_H_ */
