#include "all.h"

// cw 顺时针, ccw 逆时针, 数字是轮子编号, 见底板上的马克笔记号
void cw1() {
  GPIO_SetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_9);
  GPIO_ResetBits(GPIOB, GPIO_Pin_10);
}

void cw2() {
  GPIO_SetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_12);
  GPIO_ResetBits(GPIOB, GPIO_Pin_13);
}

void cw3() {
  GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9);
  GPIO_ResetBits(GPIOA, GPIO_Pin_10);
}

void cw4() {
  GPIO_SetBits(GPIOA, GPIO_Pin_11 | GPIO_Pin_12);
  GPIO_ResetBits(GPIOA, GPIO_Pin_15);
}

// 与 stop 区别, 代表 pwm 波控制的空段
void cw1Stop() {
  GPIO_ResetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_10);
  GPIO_SetBits(GPIOB, GPIO_Pin_9);
}

void cw2Stop() {
  GPIO_ResetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_13);
  GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

void cw3Stop() {
  GPIO_ResetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_10);
  GPIO_SetBits(GPIOA, GPIO_Pin_9);
}

void cw4Stop() {
  GPIO_ResetBits(GPIOA, GPIO_Pin_11 | GPIO_Pin_15);
  GPIO_SetBits(GPIOA, GPIO_Pin_12);
}

void ccw1() {
  GPIO_SetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_10);
  GPIO_ResetBits(GPIOB, GPIO_Pin_9);
}

void ccw2() {
  GPIO_SetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_13);
  GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

void ccw3() {
  GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_10);
  GPIO_ResetBits(GPIOA, GPIO_Pin_9);
}

void ccw4() {
  GPIO_SetBits(GPIOA, GPIO_Pin_11 | GPIO_Pin_15);
  GPIO_ResetBits(GPIOA, GPIO_Pin_12);
}

void ccw1Stop() {
  GPIO_ResetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_9);
  GPIO_SetBits(GPIOB, GPIO_Pin_10);
}

void ccw2Stop() {
  GPIO_ResetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_12);
  GPIO_SetBits(GPIOB, GPIO_Pin_13);
}

void ccw3Stop() {
  GPIO_ResetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9);
  GPIO_SetBits(GPIOA, GPIO_Pin_10);
}

void ccw4Stop() {
  GPIO_ResetBits(GPIOA, GPIO_Pin_11 | GPIO_Pin_12);
  GPIO_SetBits(GPIOA, GPIO_Pin_15);
}

// 悬空, 不加速也不刹车
void vacant1() { GPIO_SetBits(GPIOB, GPIO_Pin_9 | GPIO_Pin_10); }

void vacant2() { GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13); }

void vacant3() { GPIO_SetBits(GPIOA, GPIO_Pin_9 | GPIO_Pin_10); }

void vacant4() { GPIO_SetBits(GPIOA, GPIO_Pin_12 | GPIO_Pin_15); }

// 刹车
void stop1() { GPIO_ResetBits(GPIOB, GPIO_Pin_9 | GPIO_Pin_10); }

void stop2() { GPIO_ResetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13); }

void stop3() { GPIO_ResetBits(GPIOA, GPIO_Pin_9 | GPIO_Pin_10); }

void stop4() { GPIO_ResetBits(GPIOA, GPIO_Pin_12 | GPIO_Pin_15); }

void go() {
  if (pwm) {
    if (cnt < pwm) {
      ccw1();
      ccw2();
      cw3();
      cw4();
    } else {
      ccw1Stop();
      ccw2Stop();
      cw3Stop();
      cw4Stop();
    }
  } else {
    vacant1();
    vacant2();
    vacant3();
    vacant4();
  }
}

void back() {
  if (pwm) {
    if (cnt < pwm) {
      cw1();
      cw2();
      ccw3();
      ccw4();
    } else {
      cw1Stop();
      cw2Stop();
      ccw3Stop();
      ccw4Stop();
    }
  } else {
    vacant1();
    vacant2();
    vacant3();
    vacant4();
  }
}

void left() {
  if (pwm) {
    if (cnt < pwm) {
      cw1();
      ccw2();
      cw3();
      ccw4();
    } else {
      cw1Stop();
      ccw2Stop();
      cw3Stop();
      ccw4Stop();
    }
  } else {
    vacant1();
    vacant2();
    vacant3();
    vacant4();
  }
}

void right() {
  if (pwm) {
    if (cnt < pwm) {
      ccw1();
      cw2();
      ccw3();
      cw4();
    } else {
      ccw1Stop();
      cw2Stop();
      ccw3Stop();
      cw4Stop();
    }
  } else {
    vacant1();
    vacant2();
    vacant3();
    vacant4();
  }
}

void cw() {
  if (pwm) {
    if (cnt < pwm) {
      cw1();
      cw2();
      cw3();
      cw4();
    } else {
      cw1Stop();
      cw2Stop();
      cw3Stop();
      cw4Stop();
    }
  } else {
    vacant1();
    vacant2();
    vacant3();
    vacant4();
  }
}

void ccw() {
  if (pwm) {
    if (cnt < pwm) {
      ccw1();
      ccw2();
      ccw3();
      ccw4();
    } else {
      ccw1Stop();
      ccw2Stop();
      ccw3Stop();
      ccw4Stop();
    }
  } else {
    vacant1();
    vacant2();
    vacant3();
    vacant4();
  }
}

void wheelInit() {
  wheelGpioInit();
  tim6IrqInit();
  tim6Init();
}

// init GPIO for 4 wheels
void wheelGpioInit() {
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

// init pwm control timer for wheels
void tim6IrqInit() {
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void tim6Init() {
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
  TIM_TimeBaseInitStructure.TIM_Prescaler = 71;
  TIM_TimeBaseInitStructure.TIM_Period = 29;
  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);
  TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM6, ENABLE);
}

void TIM6_IRQHandler() {
  if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) {
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
    cnt = (cnt + 1) % 100;
  }
}
