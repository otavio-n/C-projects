#include "timer.h"

//REMAP do PWM para os pinos PC8 e PC9
void GPIOPWMPC8_9 (void) {
	GPIO_InitTypeDef	GP;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);

	GP.GPIO_Mode=GPIO_Mode_AF_PP;
	GP.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9;
	GP.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOC,&GP);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);
}

void PWM_PC8_9_Init(uint16_t duty_horizontal, uint16_t duty_vertical )//50Hz para o servo
{
	TIM_TimeBaseInitTypeDef TimerBaseInit;
	TIM_OCInitTypeDef TimerOutChanInit;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TimerBaseInit.TIM_Prescaler= 1440-1; // Pres/14400
	TimerBaseInit.TIM_Period= 1000-1; //100 cts
	TimerBaseInit.TIM_CounterMode=TIM_CounterMode_Up;
	TimerBaseInit.TIM_ClockDivision=0;
	TIM_TimeBaseInit(TIM3,&TimerBaseInit);

	TimerOutChanInit.TIM_OCMode=TIM_OCMode_PWM1;
	TimerOutChanInit.TIM_OutputState=TIM_OutputState_Enable;
	TimerOutChanInit.TIM_Pulse=duty_horizontal;
	TIM_OC3Init(TIM3,&TimerOutChanInit);//PC8 duty_horizontal
	TimerOutChanInit.TIM_Pulse=duty_vertical;
	TIM_OC4Init(TIM3,&TimerOutChanInit);//PC9 duty_vertical
	TIM_Cmd(TIM3,ENABLE);
}

void Timer_Iniciar(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	// Configura o TIMER:2
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period = 10000-1; // Auto reload
	TIM_TimeBaseStructure.TIM_Prescaler = 1500-1; // CK_PSC = 72MHz, CK_CNT = 10 kHz
											  // 	reload a 1000 DANDO CERTO! 1500 estabiliza

	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
}

void Timer_OC_Iniciar(void){
	TIM_OCInitTypeDef TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
	TIM_OCInitStructure.TIM_Pulse = 0; // TIM4_CC4 = 5
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
}

void Timer_Int_Iniciar (void){
	//Configura TIM4 CC4 para interrupção
	TIM_ITConfig(TIM4, TIM_IT_CC4, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
}

void NVIC_conf (void) {
	NVIC_InitTypeDef nVICKY;
	NVIC_PriorityGroupConfig (NVIC_PriorityGroup_4); // 4 bits para sub-prioridade 0 bits para prioridade
	//Ativa a TIM4_IRQn
	nVICKY.NVIC_IRQChannel = TIM4_IRQn;
	nVICKY.NVIC_IRQChannelCmd = ENABLE;
	nVICKY.NVIC_IRQChannelPreemptionPriority = 15; // Não importa, só há sub-prioridade, então a menor
	nVICKY.NVIC_IRQChannelSubPriority = 0; // Maior sub-prioridade possível
	NVIC_Init(&nVICKY);

}

void PWM_dutyTauschen(uint16_t duty_horizontal, uint16_t duty_vertical){
	TIM_OCInitTypeDef TimerOutChanInit;
	TimerOutChanInit.TIM_OCMode=TIM_OCMode_PWM1;
	TimerOutChanInit.TIM_OutputState=TIM_OutputState_Enable;
	TimerOutChanInit.TIM_Pulse=duty_horizontal;
	TIM_OC3Init(TIM3,&TimerOutChanInit);//PC8 duty_horizontal
	TimerOutChanInit.TIM_Pulse=duty_vertical;
	TIM_OC4Init(TIM3,&TimerOutChanInit);//PC9 duty_vertical
	TIM_Cmd(TIM3,ENABLE);
}

