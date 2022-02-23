#ifndef __INFRARED_H
#define __INFRARED_H
#include "stm32f10x.h"

void adcChannelInit(u8 channel);
void adcGpioInit(void);
void adcCheck(void);
void adcInit(void);

#endif
