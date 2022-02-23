#ifndef __COMMU_H
#define __COMMU_H
#include "stm32f10x.h"

// 103和407板子通信，1B数据，data字段内容定义

//空信息
#define COMMU_NULL 0x00

//运动相关，103给407
#define COMMU_ACT_BALL ((u8)0x10)   //到达取球地点
#define COMMU_ACT_LAUNCH ((u8)0x20) //到达发射地点

//操作相关，407给103
#define COMMU_OPR_BALL ((u8)0x30)   //取球完毕
#define COMMU_OPR_LAUNCH ((u8)0x40) //发射完毕

//识别球相关，407给103
#define COMMU_BALL_TARGET ((u8)0x00) //目标球
#define COMMU_BALL_OTHERS ((u8)0x01) //其他球

// locate是位置，参数0-7代表八个球，ball是球的属性，也就是是否是目标球
#define COMMU_BallLocate(locate, ball) ((u8)(locate << 1 + ball))

#endif
