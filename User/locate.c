#include "all.h"

// cw: B up when A is high
// ccw: B up when A is low
// cw and ccw are defined in wheel.c, maybe not reality
// so just use A to calculate distance

void locateInit() {
  exti15_10IrqInit();
  exitInit();
  afioInit();
  gpioInit();
}

// 初始化编码器所需外部中断
void exti15_10IrqInit() {
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void exitInit() {
  EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_Line14;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

void afioInit() {
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
}

void gpioInit() {
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void EXTI15_10_IRQHandler() {
  if (EXTI_GetITStatus(EXTI_Line14) != RESET) {
    if (needCount)
      pprTimes++;
    if (pprTimes2 != -1)
      pprTimes2++;
    EXTI_ClearITPendingBit(EXTI_Line14);
  }
}
