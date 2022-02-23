#ifndef __VAR_H
#define __VAR_H
#include "stm32f10x.h"

// wheel
extern u8 pwm;
extern u8 cnt;
extern u8 needCount;

// infrared
extern int divide[];
extern u8 gray[];
enum Action { GO, BACK, CW, CCW, NO, LEFT, RIGHT };
extern enum Action act;
extern int infDistance;
extern u8 hasInf, safe;
extern u8 turn, nowTurn;

// locate
extern int ppr, square;
extern int wheelC;
extern int pprTimes, pprTimes2;
extern int pprInfDistance, squareDistance, movePart;
extern u8 part, fetchPart;
extern int partDistance, fetchDistance;

// control
enum Speed { MINMIN, MINMAX, MAXMIN, MIN, MAX };
extern enum Action way[];
extern u8 forceSpeed, forceInfra;
extern enum Speed speed;
enum Step {
  START,
  GO_CROSS,
  BACK_CROSS,
  GO_FETCH_ALL,
  BACK_FETCH_ALL,
  GO_THROW,
  BACK_THROW,
  GO_FETCH,
  GO_FETCH_2,
  BACK_FETCH,
  WAIT_FETCH,
  WAIT_THROW
};
extern enum Step step;
extern u8 finish, hasFetch;
extern u8 rightBall[], leftBall[];
extern u8 rightIndex, leftIndex;
extern u8 cross, nowBlack;
extern u8 min, max;
extern u8 now;
extern u8 stop;

#endif
