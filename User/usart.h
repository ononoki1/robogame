#ifndef __USART_H
#define __USART_H
#include "stm32f10x.h"

#define USART_REC_LEN 200 //最大接收长度

extern u8
    USART1_RX_BUF[USART_REC_LEN]; // USART1接收缓冲,最大USART_REC_LEN个字节
extern u16 USART1_RX_STA;         // USART1接收状态标记

void uart1Init(void);
void USART1_IRQHandler(void); // USART1中断服务函数

#endif
