#ifndef __NIXIE_H
#define __NIXIE_H
#include "stm32f10x.h"

void nixieInit(void);
void place(u8 k);
void num(u8 m);
void numPoint(int n);
void numDisplay(int n);

#endif
