#include "SERVO.h"

#define dc	5

void Servo_Bewegung(uint16_t lt, uint16_t rt, uint16_t ld, uint16_t rd, uint16_t *servoh, uint16_t *servov){
	//variáveis para a lógica de movimento

	volatile int mediat;
	volatile int mediad;
	volatile int medial;
	volatile int mediar;

	volatile int difvert;
	volatile int difhort;

	volatile int tolh = 90	; // tolerância para diferência HORIZONTAL 100!
	volatile int tolv = 100; // tolerância para diferência VERTICAL 100!

	//////////////////////////////////////////////////////////////////////
	//LÓGICA DE MOVIMENTO

   	mediat = (lt + rt) / 2;
   	mediad = (ld + rd) / 2;
   	medial = (lt + ld) / 2;
   	mediar = (rt + rd) / 2;

   	difvert = mediat - mediad;
	difhort = medial - mediar;

   	//MOTOR VERTICAL
	/*
	 * duty maximo 120; duty minimo 85
	 */
   	if (((-1 * tolv) > difvert) || (difvert > tolv)) { //ve se a dif está na tolerancia, muda o angulo vertical
   		if (mediat > mediad) {
   			*servov = *servov + dc;
   			if (*servov > 120) {
   				*servov = 120;
   			}
   		}
		else if (mediat < mediad) {
			*servov = *servov - dc;
			if (*servov < 85) {
				*servov = 85;
			}
		}
   		PWM_dutyTauschen(*servoh, *servov);
	}

	//MOTOR HORIZONTAL
   	/*minimo=25; maximo=125   E dutycicle=1000!!	 */
   	if (((-1 * tolh) > difhort) || (difhort > tolh)) { //ve se a dif está na tolerancia, muda o angulo horizontal
		if (medial > mediar) {
			if(*servov < 102){
				*servoh= *servoh - dc;
			}
			else{
				*servoh= *servoh + dc;
			}
			if (*servoh > 125) {
				*servoh = 125;
			}
		}
		else if (medial < mediar) {
			if(*servov < 102){
				*servoh= *servoh + dc;
			}
			else{
				*servoh= *servoh - dc;
			}
			if (*servoh < 25) {
				*servoh = 25;
			}
		}
		PWM_dutyTauschen(*servoh, *servov);
   	}
}
