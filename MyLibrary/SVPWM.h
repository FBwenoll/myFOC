//
// Created by fbwenoll on 24-1-11.
//

#ifndef MYFOC_SVPWM_H
#define MYFOC_SVPWM_H

#include <math.h>

//pi相关值
#define PI     3.14159265359
#define PI_6   0.52359877559
#define PI_3   1.04719755120
#define PI_2   1.57079632679
#define _3PI_2 4.71238898038
#define _2PI   6.28318530718

//根号3
#define SQRT3   1.73205080757
#define SQRT3_3 0.577

//电压值
#define VOLTAGE 12
#define PWM_PERIOD 100
//alpha beta 坐标系
typedef struct {
    float U_alpha;
    float U_beta;
} UAlphaBeta;

//dq坐标系
typedef struct {
    float U_d;
    float U_q;
    float angle;
} UDQ;

typedef struct {
    int a;
    int b;
    int c;
} Duty;

float NormalizeAngle(float angle);

UAlphaBeta RevPark(UDQ dq);

Duty SetPhaseVoltage(UDQ dq);

#endif //MYFOC_SVPWM_H
