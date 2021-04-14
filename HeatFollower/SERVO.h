#ifndef __SERVO
#define SERVO
#include "stm32f10x_conf.h"
#include "timer.h"


void Servo_Bewegung(uint16_t lt, uint16_t rt, uint16_t ld, uint16_t rd, uint16_t *servoh, uint16_t *servov);


#endif
