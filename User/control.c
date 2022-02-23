#include "all.h"

void grayCheck() {
  for (u8 i = 0; i < 10; i++) {
    adcChannelInit(i);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET)
      ;
    gray[i] = ADC_GetConversionValue(ADC1) < divide[i]; // dark times
  }
  if (!hasInf && (((way[now] == GO && gray[0] && gray[1] && gray[2] &&
                    gray[3] && gray[4])) ||
                  (way[now] == BACK && gray[5] && gray[6] && gray[7] &&
                   gray[8] && gray[9]))) {
    hasInf = 1;
    pprTimes = pprInfDistance;
  }
  if (hasInf) {
    act = NO;
    return;
  }
  if ((way[now] == GO && gray[5] && gray[6] && gray[7] && gray[8] && gray[9]) ||
      (way[now] == BACK && gray[0] && gray[1] && gray[2] && gray[3] &&
       gray[4])) {
    act = NO;
    return;
  }
  if (way[now] == GO || way[now] == BACK) {
    if (gray[0] && gray[5])
      act = LEFT;
    else if (gray[4] && gray[9])
      act = RIGHT;
    else if ((gray[9] && (gray[0] || gray[1] || gray[2] || gray[3])) ||
             (gray[8] && (gray[0] || gray[1] || gray[2])) ||
             (gray[7] && (gray[0] || gray[1])) || (gray[6] && gray[0]))
      act = CCW;
    else if ((gray[4] && (gray[5] || gray[6] || gray[7] || gray[8])) ||
             (gray[3] && (gray[5] || gray[6] || gray[7])) ||
             (gray[2] && (gray[5] || gray[6])) || (gray[1] && gray[5]))
      act = CW;
    else
      act = NO;
  } else if (way[now] == CW) {
    if (!turn && !gray[1] && !gray[2] && !gray[3]) {
      turn = 1;
    } else if (turn && gray[2]) {
      turn = 0;
      now++;
    }
  } else if (way[now] == CCW) {
    if (!turn && !gray[1] && !gray[2] && !gray[3]) {
      turn = 1;
    } else if (turn && gray[2]) {
      turn = 0;
      now++;
    }
  }
}

void crossCheck() {
  for (u8 i = 0; i < 10; i++) {
    adcChannelInit(i);
    gray[i] = 0;
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET)
      ;
    gray[i] = ADC_GetConversionValue(ADC1) < divide[i]; // dark times
  }
  if (step == GO_FETCH && now == 0 && gray[3] && gray[4] && !nowBlack) {
    nowBlack = 1;
    cross++;
  } else if (step == BACK_FETCH && now == 2 && gray[3] && gray[4] &&
             !nowBlack) {
    nowBlack = 1;
    cross--;
  } else if (step == GO_FETCH && now == 0 && !gray[3] && !gray[4] && nowBlack)
    nowBlack = 0;
  else if (step == BACK_FETCH && now == 2 && !gray[3] && !gray[4] && nowBlack)
    nowBlack = 0;
  if (((step == GO_FETCH && now == 0 && gray[3] && gray[4])) ||
      (step == BACK_FETCH && now == 2 && gray[3] && gray[4])) {
    if (!hasInf) {
      hasInf = 1;
      pprTimes = pprInfDistance;
    } else {
      pprTimes2 = pprInfDistance;
    }
  }
  if (way[now] == CW || way[now] == CCW) {
    if (turn != 3 && gray[2] && !nowTurn) {
      turn++;
      nowTurn = 1;
    } else if (turn != 3 && !gray[2] && nowTurn) {
      nowTurn = 0;
    } else if (turn == 3) {
      turn = 0;
      nowTurn = 0;
      now++;
    }
  }
  if ((step == GO_FETCH && now == 2) || (step == BACK_FETCH && now == 0)) {
    if (!gray[6] && !gray[7] && !gray[8]) {
      if (gray[3])
        act = CW;
      else if (gray[1])
        act = CCW;
    } else {
      if (gray[3] && (gray[6] || gray[7]))
        act = CW;
      else if (gray[1] && (gray[8] || gray[7]))
        act = CCW;
      else if (gray[1] && gray[6])
        act = LEFT;
      else if (gray[3] && gray[8])
        act = RIGHT;
    }
  }
}

enum Speed getSpeed() {
  if ((now == 0 && (way[1] == NO || way[1] == CW || way[1] == CCW)) ||
      (now > 0 && way[now - 1] == NO &&
       (way[now + 1] == NO || way[now + 1] == CW || way[now + 1] == CCW)) ||
      (way[now + 1] == NO && now > 0 &&
       (way[now - 1] == CW || way[now - 1] == CCW))) {
    return MINMIN;
  }
  if (now == 0 || way[now - 1] == CW || way[now - 1] == CCW) {
    return MINMAX;
  }
  if (way[now + 1] == NO || way[now + 1] == CW || way[now + 1] == CCW) {
    return MAXMIN;
  }
  if (act != NO || way[now] == CW || way[now] == CCW) {
    return MIN;
  }
  return MAX;
}

void setPwm() {
  if (stop || !safe) {
    pwm = 0;
    ledOn();
    return;
  }
  if (way[now] == NO) {
    pwm = 0;
    if (way[0] != NO)
      finish = 1;
    return;
  }
  ledOff();
  movePart = wheelC * pprTimes / (ppr * square); // 计算当前格移动的百分比
  if (!forceSpeed)
    speed = getSpeed();
  if (speed == MINMIN) {
    if (movePart < min)
      pwm = min;
    else if (movePart < (max > 50 ? 50 : max))
      pwm = movePart;
    else if (max < 50 && movePart < 100 - max)
      pwm = max;
    else if (movePart < 100 - min)
      pwm = 100 - movePart;
    else
      pwm = min;
  } else if (speed == MINMAX) {
    if (movePart < min)
      pwm = min;
    else if (movePart < max)
      pwm = movePart;
    else
      pwm = max;
  } else if (speed == MAXMIN) {
    if (movePart < 100 - max)
      pwm = max;
    else if (movePart < 100 - min)
      pwm = 100 - movePart;
    else
      pwm = min;
  } else if (speed == MIN) {
    pwm = min;
  } else {
    pwm = max;
  }
}

void move() {
  setPwm();
  if (act != NO) {
    needCount = 0;
    switch (act) {
    case CW:
      cw();
      break;
    case CCW:
      ccw();
      break;
    case LEFT:
      left();
      break;
    case RIGHT:
      right();
      break;
    default:;
    }
  } else {
    switch (way[now]) {
    case GO:
      needCount = 1;
      go();
      break;
    case BACK:
      needCount = 1;
      back();
      break;
    case CW:
      needCount = 0;
      cw();
      break;
    case CCW:
      needCount = 0;
      ccw();
      break;
    default:;
    }
  }
  if ((hasInf || forceInfra) && pprTimes >= squareDistance) {
    if (pprTimes2 == -1) {
      pprTimes %= squareDistance;
      hasInf = 0;
      now++;
    } else {
      pprTimes = pprTimes2;
      pprTimes2 = -1;
      if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15))
        now++;
    }
  }
}
