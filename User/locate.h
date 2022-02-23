#ifndef __LOCATE_H
#define __LOCATE_H
#include "stm32f10x.h"

void locateInit(void);
void exti15_10IrqInit(void);
void exitInit(void);
void afioInit(void);
void gpioInit(void);

#endif
