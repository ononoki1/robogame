#include "all.h"

void ledInit() {
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void led1Off() { GPIO_ResetBits(GPIOC, GPIO_Pin_14); }

void led1On() { GPIO_SetBits(GPIOC, GPIO_Pin_14); }

void led2Off() { GPIO_ResetBits(GPIOC, GPIO_Pin_15); }

void led2On() { GPIO_SetBits(GPIOC, GPIO_Pin_15); }

void ledOff() { GPIO_ResetBits(GPIOC, GPIO_Pin_14 | GPIO_Pin_15); }

void ledOn() { GPIO_SetBits(GPIOC, GPIO_Pin_14 | GPIO_Pin_15); }
