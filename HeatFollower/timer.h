#ifndef __timer
#define timer
#include "stm32f10x_conf.h"

void GPIOPWMPC8_9 (void);
void PWM_PC8_9_Init(uint16_t duty_horizontal, uint16_t duty_vertical);
void PWM_dutyTauschen(uint16_t duty_horizontal, uint16_t duty_vertical);
//void Tim2_4_Base_Init (uint16_t PRE, uint16_t ARR, TIM_TypeDef* TIMx, uint32_t RCC_APB1Periph_TIMx);
//void Tim2_4_CCR_int (TIM_TypeDef* TIMx, uint16_t TIM_IT_CCx, void (*CCR) (TIM_TypeDef*, TIM_OCInitTypeDef*));
void NVIC_conf (void);
void Timer_Iniciar(void);
void Timer_OC_Iniciar(void);
void Timer_Int_Iniciar (void);

#endif
