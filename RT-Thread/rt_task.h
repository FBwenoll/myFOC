//
// Created by FBwenoll on 2024/1/14.
//

#ifndef RT_TASK_ENTRY_H
#define RT_TASK_ENTRY_H

#include "rtthread.h"
#include "tim.h"
#include "rt_mailbox.h"
#include "SVPWM.h"

/*------------------------------------*/
/*LED线程*/
/*------------------------------------*/
int create_led_thread(void);

void led_thread_entry(void *parameter);

static rt_thread_t led_thread = RT_NULL;

#define LED_STACK_SIZE 512
#define LED_PRIORITY   5
#define LED_TICK       20
/*------------------------------------*/
/*ADC相电流采样线程*/
/*------------------------------------*/
int create_adc_thread(void);

void adc_thread_entry(void *parameter);

static rt_thread_t adc_thread = RT_NULL;

#define ADC_STACK_SIZE 512
#define ADC_PRIORITY   2
#define ADC_TICK       20
#endif //RT_TASK_ENTRY_H
