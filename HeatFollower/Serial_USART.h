#ifndef __Serial_USART
#define __Serial_USART

#include "stm32f10x_conf.h"

void GPIO_USART2 (void);
void USART_conf (void);
//void NIVIC_Config (uint8_t canal, FunctionalState estado);

uint8_t receive_byte_USARTx(uint8_t* rec_buffer, USART_TypeDef * USARTx);
uint8_t send_byte_USARTx(uint8_t rec_buffer, USART_TypeDef * USARTx);

#endif
