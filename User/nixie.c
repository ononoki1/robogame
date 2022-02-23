#include "all.h"

void nixieInit() {
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |
                                GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 |
                                GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 |
                                GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void place(u8 k) {
  GPIOC->ODR &= 0xfffff0ff;
  switch (k) {
  case 0:
    GPIOC->ODR |= 0x00000100;
    break;
  case 1:
    GPIOC->ODR |= 0x00000200;
    break;
  case 2:
    GPIOC->ODR |= 0x00000400;
    break;
  case 3:
    GPIOC->ODR |= 0x00000800;
    break;
  default:
    GPIOC->ODR |= 0x00000000;
    break;
  }
}

void num(u8 m) {
  GPIOC->ODR &= 0xffffff00;
  switch (m) {
  case 0:
    GPIOC->ODR |= 0x000000c0;
    break;
  case 1:
    GPIOC->ODR |= 0x000000f9;
    break;
  case 2:
    GPIOC->ODR |= 0x000000a4;
    break;
  case 3:
    GPIOC->ODR |= 0x000000b0;
    break;
  case 4:
    GPIOC->ODR |= 0x00000099;
    break;
  case 5:
    GPIOC->ODR |= 0x00000092;
    break;
  case 6:
    GPIOC->ODR |= 0x00000082;
    break;
  case 7:
    GPIOC->ODR |= 0x000000f8;
    break;
  case 8:
    GPIOC->ODR |= 0x00000080;
    break;
  case 9:
    GPIOC->ODR |= 0x00000090;
    break;
  default:
    GPIOC->ODR |= 0x000000ff;
    break;
  }
}

void numPoint(int n) {
  switch (n) {
  case 0:
    GPIOC->ODR &= 0xffffff00;
    GPIOC->ODR |= 0x000000c0 - 128;
    break;
  case 1:
    GPIOC->ODR &= 0xffffff00;
    GPIOC->ODR |= 0x000000f9 - 128;
    break;
  case 2:
    GPIOC->ODR &= 0xffffff00;
    GPIOC->ODR |= 0x000000a4 - 128;
    break;
  case 3:
    GPIOC->ODR &= 0xffffff00;
    GPIOC->ODR |= 0x000000b0 - 128;
    break;
  case 4:
    GPIOC->ODR &= 0xffffff00;
    GPIOC->ODR |= 0x00000099 - 128;
    break;
  case 5:
    GPIOC->ODR &= 0xffffff00;
    GPIOC->ODR |= 0x00000092 - 128;
    break;
  case 6:
    GPIOC->ODR &= 0xffffff00;
    GPIOC->ODR |= 0x00000082 - 128;
    break;
  case 7:
    GPIOC->ODR &= 0xffffff00;
    GPIOC->ODR |= 0x000000f8 - 128;
    break;
  case 8:
    GPIOC->ODR &= 0xffffff00;
    GPIOC->ODR |= 0x00000080 - 128;
    break;
  case 9:
    GPIOC->ODR &= 0xffffff00;
    GPIOC->ODR |= 0x00000090 - 128;
    break;
  }
}

void numDisplay(int n) {
  u8 s[4];
  s[0] = n / 1 % 10;
  s[1] = n / 10 % 10;
  s[2] = n / 100 % 10;
  s[3] = n / 1000 % 10;
  for (int i = 0; i < 4; i++) {
    place(i);
    num(s[i]);
    delay_ms(1);
  }
}
