#include "Serial_USART.h"


void GPIO_USART2 (void) {
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure USART1 Tx (PA.02) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART1 Rx (PA.03) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

void USART_conf (void) {
	USART_InitTypeDef USART_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &USART_InitStructure);

	/* Enable USART2 */
	USART_Cmd(USART2, ENABLE);

}
/*
void NIVIC_Config (uint8_t canal, FunctionalState estado) {
	NVIC_InitTypeDef nVICKY;
	NVIC_PriorityGroupConfig (NVIC_PriorityGroup_0); // 4 bits para sub-prioridade 0 bits para prioridade
	//Ativa a EXTI0_IRQn
	nVICKY.NVIC_IRQChannel = canal;
	nVICKY.NVIC_IRQChannelCmd = estado;
	nVICKY.NVIC_IRQChannelPreemptionPriority = 15; // Não importa, só há sub-prioridade, então a menor
	nVICKY.NVIC_IRQChannelSubPriority = 0; // Maior sub-prioridade possível
	NVIC_Init(&nVICKY);
}
*/
uint8_t receive_byte_USARTx(uint8_t* rec_buffer, USART_TypeDef * USARTx) {
	if ( 1 == USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) ) {
		*rec_buffer = (uint8_t) USART_ReceiveData(USARTx);
		return 1;
	}
	else return 0;
}

uint8_t send_byte_USARTx(uint8_t rec_buffer, USART_TypeDef * USARTx){
	if ( 1 == USART_GetFlagStatus(USARTx, USART_FLAG_TXE) ) {
			USART_SendData(USARTx, rec_buffer);
			return 1;
		}
	else return 0;
}
