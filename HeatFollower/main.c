#include "stm32f10x.h"
#include "stm32f10x_conf.h" /*uncomment header file needed, on stm32f10x_conf.h to enable peripheral header file inclusion */
#include "SERVO.h"
#include "timer.h"

#define ADC1_DR_ADDRESS                  ((uint32_t)0x4001244C)
#define  DmaBufferSize 4*4

u16 AdcBuff[DmaBufferSize];

void configADC(void);
void configDMA(void);


u32	adcVal[4];

uint16_t servoh = 75; //servo fica na hor
uint16_t servov = 90; //servo fica na vert

int main(void)
{
	configADC();
	configDMA();
	GPIOPWMPC8_9();
	Timer_Iniciar();
	Timer_OC_Iniciar();
	Timer_Int_Iniciar();
	NVIC_conf();

	PWM_PC8_9_Init(75, 90);


	/*-------------------------------------
	RCC_ClocksTypeDef clockfreq;
	RCC_GetClocksFreq(&clockfreq);
	u32 ReadAdcClock = clockfreq.ADCCLK_Frequency;
	----------------------------------------*/
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	ADC_DMACmd(ADC1,ENABLE);
	//while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	//adcVal=ADC_GetConversionValue(ADC1);


	while(1)
    {
		u16 dataCounter;
		dataCounter=DMA_GetCurrDataCounter(DMA1_Channel1);
		uint8_t i=0;
		if(DMA_GetFlagStatus(DMA1_FLAG_TC1))
		{
			for(i=0;i<DmaBufferSize/4;i++){
				adcVal[i] = (AdcBuff[i]+AdcBuff[i+4]+AdcBuff[i+8]+AdcBuff[i+12])/4;
			}
		}
    }

}

void TIM4_IRQHandler(void) {
	Servo_Bewegung(adcVal[0], adcVal[1], adcVal[2], adcVal[3], &servoh, &servov);
	TIM_ClearITPendingBit(TIM4,TIM_IT_CC4);

}

void configADC(void)
{
    //--Enable ADC1 and GPIOA--
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure; //Variable used to setup the GPIO pins
    GPIO_StructInit(&GPIO_InitStructure); // Reset init structure, if not it can cause issues...
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    ADC_InitTypeDef configADC;

	configADC.ADC_ContinuousConvMode=ENABLE;
	//configADC.ADC_ContinuousConvMode=DISABLE;
	configADC.ADC_DataAlign=ADC_DataAlign_Right;
	configADC.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	//configADC.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	configADC.ADC_Mode=ADC_Mode_Independent;
	configADC.ADC_NbrOfChannel=4;
	configADC.ADC_ScanConvMode=ENABLE;
	ADC_Init(ADC1,&configADC);

	ADC_RegularChannelConfig(ADC1,ADC_Channel_10,1,ADC_SampleTime_41Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_11,2,ADC_SampleTime_41Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_12,3,ADC_SampleTime_41Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_13,4,ADC_SampleTime_41Cycles5);

	ADC_Cmd(ADC1,ENABLE);
	//habilita ADC para o DMA
	ADC_DMACmd(ADC1, ENABLE);
	ADC_ResetCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));

}

void configDMA(void)
{
	DMA_InitTypeDef configDMA;
	DMA_DeInit(DMA1_Channel1);

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	configDMA.DMA_BufferSize=DmaBufferSize;
	configDMA.DMA_DIR=DMA_DIR_PeripheralSRC;
	configDMA.DMA_M2M=DMA_M2M_Disable;
	configDMA.DMA_MemoryBaseAddr=(uint32_t)AdcBuff;
	configDMA.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	configDMA.DMA_MemoryInc=DMA_MemoryInc_Enable;
	configDMA.DMA_Mode=DMA_Mode_Circular;
	configDMA.DMA_PeripheralBaseAddr=ADC1_DR_ADDRESS;
	configDMA.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	configDMA.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	configDMA.DMA_Priority=DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1,&configDMA);
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
	DMA_Cmd(DMA1_Channel1,ENABLE);

}
