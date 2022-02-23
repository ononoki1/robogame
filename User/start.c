#include "all.h"

void start() {
  init();
  while (1) {
    if (step == BACK_THROW)
      stop = 1;
    if (step == GO_FETCH && now == 2)
      pprTimes = fetchDistance;
    if (forceInfra != 2 || act != NO)
      grayCheck();
    else
      crossCheck();
    if (finish)
      update();
    if (step == GO_FETCH && now == 0 && movePart > 10) {
      forceInfra = 2;
    } else if (step == BACK_FETCH && now == 2 && movePart > 80) {
      forceInfra = 0;
    }
    move();
  }
}

void update() {
  finish = 0;
  now = 0;
  for (u8 i = 0; i < 8; i++)
    way[i] = NO;
  updateStep();
  updateWay();
}

void updateWay() {
  if (step == GO_CROSS) {
    forceInfra = 0;
    forceSpeed = 0;
    way[0] = GO;
    way[1] = GO;
    way[2] = GO;
    way[3] = CCW;
    way[4] = NO;
  } else if (step == BACK_CROSS) {
    forceInfra = 0;
    forceSpeed = 0;
    way[0] = CW;
    way[1] = BACK;
    way[2] = BACK;
    way[3] = BACK;
    way[4] = NO;
  } else if (step == GO_THROW) {
    forceInfra = 1;
    forceSpeed = 1;
    speed = MIN;
    pprTimes = partDistance;
    way[0] = CCW;
    way[1] = GO;
    way[2] = NO;
  } else if (step == WAIT_THROW) {
    way[0] = NO;
    USART_SendData(USART1, COMMU_ACT_LAUNCH);
  } else if (step == BACK_THROW) {
    forceInfra = 0;
    forceSpeed = 1;
    speed = MIN;
    way[0] = BACK;
    way[1] = CW;
    way[2] = NO;
  } else if (step == GO_FETCH) {
    forceInfra = 0;
    forceSpeed = 1;
    speed = MIN;
    way[0] = GO;
    way[1] = CW;
    way[2] = GO;
    way[3] = NO;
  } else if (step == WAIT_FETCH) {
    way[0] = NO;
    USART_SendData(USART1, COMMU_ACT_BALL);
  } else if (step == BACK_FETCH) {
    forceInfra = 2;
    forceSpeed = 1;
    speed = MIN;
    way[0] = BACK;
    way[1] = CCW;
    way[2] = BACK;
    way[3] = NO;
  }
}

void updateStep() {
  if (step == START)
    step = GO_CROSS;
  else if (step == GO_CROSS)
    step = GO_FETCH;
  else if (step == GO_FETCH)
    step = WAIT_FETCH;
  else if (step == WAIT_FETCH)
    step = BACK_FETCH;
  else if (step == BACK_FETCH)
    step = BACK_CROSS;
  else if (step == BACK_CROSS)
    step = GO_THROW;
  else if (step == GO_THROW)
    step = WAIT_THROW;
  else if (step == WAIT_THROW)
    step = BACK_THROW;
  else if (step == BACK_THROW)
    step = GO_CROSS;
}

void init() {
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  delay_init();
  locateInit();
  wheelInit();
  ledInit();
  adcInit();
  uart1Init();
  squareDistance = square * ppr * 100 / wheelC;
  pprInfDistance = (square - infDistance) * ppr * 100 / wheelC;
  partDistance = (100 - part) * ppr * square / wheelC;
  fetchDistance = (100 - part) * ppr * square / wheelC;
}

void debugInfra(u8 adc) {
  delay_init();
  nixieInit();
  adcGpioInit();
  adcChannelInit(adc);
  while (1) {
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET)
      ;
    for (int i = 0; i < 150; i++)
      numDisplay(ADC_GetConversionValue(ADC1));
  }
}

void checkInfra() {
  delay_init();
  nixieInit();
  adcInit();
  if (safe)
    while (1)
      numDisplay(1);
}
