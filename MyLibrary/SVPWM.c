//
// Created by fbwenoll on 24-1-11.
//

#include "SVPWM.h"

//将电角度转换为[0,2pi]
float NormalizeAngle(float angle) {
    float a = fmod(angle, _2PI);
    return a >= 0 ? a : (a + _2PI);
}

//反PARK变换
UAlphaBeta RevPark(UDQ dq) {
    UAlphaBeta alpha_beta;

    alpha_beta.U_alpha = cos(dq.angle) * dq.U_d - sin(dq.angle) * dq.U_q;
    alpha_beta.U_beta = sin(dq.angle) * dq.U_d - cos(dq.angle) * dq.U_q;

    return alpha_beta;
}

//SVPWM
Duty SetPhaseVoltage(UDQ dq) {
    UAlphaBeta alpha_beta;
    float U_ref = 0;
    int sector = 0;
    float T0, T1, T2;
    float Ta, Tb, Tc;
    Duty duty;

    if (dq.U_q > 0)
        // 参考电压角度（U_q)=电角度位置(U_d)+pi/2
        dq.angle = NormalizeAngle(dq.angle + PI_2);
    else
        // 参考电压角度（U_q)=电角度位置(U_d)-pi/2
        dq.angle = NormalizeAngle(dq.angle - PI_2);

    alpha_beta = RevPark(dq);
    U_ref = sqrt(alpha_beta.U_alpha * alpha_beta.U_alpha + alpha_beta.U_beta * alpha_beta.U_beta) / VOLTAGE;

    //Uref限幅至六边形内切圆内
    if (U_ref > SQRT3_3) U_ref = SQRT3_3;
    if (U_ref < -SQRT3_3) U_ref = -SQRT3_3;

    //判断所在扇区
    sector = (dq.angle / PI_3) + 1;
    T1 = SQRT3 * sin(sector * PI_3 - dq.angle) * U_ref;
    T2 = SQRT3 * sin(dq.angle - (sector - 1) * PI_3) * U_ref;
    T0 = 1 - T1 - T2;

    switch (sector) {
        case 1:
            Ta = T1 + T2 + T0 / 2;
            Tb = T2 + T0 / 2;
            Tc = T0 / 2;
            break;
        case 2:
            Ta = T1 + T0 / 2;
            Tb = T1 + T2 + T0 / 2;
            Tc = T0 / 2;
            break;
        case 3:
            Ta = T0 / 2;
            Tb = T1 + T2 + T0 / 2;
            Tc = T2 + T0 / 2;
            break;
        case 4:
            Ta = T0 / 2;
            Tb = T1 + T0 / 2;
            Tc = T1 + T2 + T0 / 2;
            break;
        case 5:
            Ta = T2 + T0 / 2;
            Tb = T0 / 2;
            Tc = T1 + T2 + T0 / 2;
            break;
        case 6:
            Ta = T1 + T2 + T0 / 2;
            Tb = T0 / 2;
            Tc = T1 + T0 / 2;
            break;
        default:
            Ta = 0;
            Tb = 0;
            Tc = 0;
    }

    duty.a = (int) (Ta * PWM_PERIOD);
    duty.b = (int) (Tb * PWM_PERIOD);
    duty.c = (int) (Tc * PWM_PERIOD);
    return duty;
}