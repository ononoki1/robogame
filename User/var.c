#include "all.h"

// wheel
u8 pwm = 0; // 4 个轮子的 pwm 占空比, 范围 [0, 100]
u8 cnt = 0;
u8 needCount = 1; // =1 代表当前状态的行走距离需要被编码器记录

// infrared
int divide[10] = {3400, 2300, 3000, 3200, 3400,
                  2700, 2900, 2700, 3000, 3000}; // 红外模块亮暗的分界值
u8 gray[10] = {0};
enum Action act = NO;  // 代表依据红外校准该走的方向
int infDistance = 110; // 车身正中和边角处红外模块的垂直距离
u8 hasInf = 0; // =1 代表已经被红外模块校准, =0 代表还没有
u8 safe = 1;   // =1 代表循迹模块无损坏, =0 代表存在损坏的模块
u8 turn = 0, nowTurn = 0;

// locate
int ppr = 867;    // 17*51, 麦轮旋转一圈的脉冲数
int square = 900; // 比赛场地一格的边长, 单位: mm
// pi*wheelD/sqrt(2)=314.16*127/sqrt(2)=39898.32/sqrt(2)=28212.37
int wheelC = 39898;
int pprTimes = 0, pprTimes2 = -1;
int movePart = 0; // 轮子走过了当前格子的百分比, 范围 [0, 100]
int pprInfDistance = 0; // 代表 square - infDistance 对应的脉冲数
int squareDistance = 0; // 代表 square 对应的脉冲数
u8 part = 20, fetchPart = 20;
int partDistance = 0, fetchDistance = 0;

// control
enum Action way[8] = {GO, GO, GO, CCW, GO, GO, CW, NO};
u8 forceSpeed = 0, forceInfra = 0;
enum Speed speed;
enum Step step = START;
u8 finish = 0, hasFetch = 0;
u8 rightBall[9] = {255}, leftBall[6] = {255};
u8 rightIndex = 0, leftIndex = 0;
u8 cross = 0, nowBlack = 0;
u8 min = 10, max = 30;
u8 now = 0;
u8 stop = 0;
