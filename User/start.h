#ifndef __START_H
#define __START_H
#include "stm32f10x.h"

void start(void);
void update(void);
void updateStep(void);
void updateWay(void);
void init(void);
void debugInfra(u8 adc);
void checkInfra(void);

#endif
