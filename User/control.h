#ifndef __CONTROL_H
#define __CONTROL_H
#include "stm32f10x.h"

void grayCheck(void);
void setPwm(void);
void move(void);
enum Speed getSpeed(void);
void crossCheck(void);

#endif
