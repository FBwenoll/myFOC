//
// Created by FBwenoll on 2024/1/14.
//

#include "rt_task.h"

INIT_APP_EXPORT(create_led_thread);
INIT_APP_EXPORT(create_adc_thread);
/*------------------------------------*/
/*LED线程*/
/*------------------------------------*/

void led_thread_entry(void *parameter) {
    MX_TIM3_Init();
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    int i = 1000 - 1;
    while (1) {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, i);
        i = i - 50;
        if (i < 0) i = 999;
        rt_thread_delay(100);
    }
}

int create_led_thread(void) {
    led_thread = rt_thread_create("LED",
                                  led_thread_entry,
                                  RT_NULL,
                                  LED_STACK_SIZE,
                                  LED_PRIORITY,
                                  LED_TICK);

    if (led_thread != RT_NULL) {
        rt_thread_startup(led_thread);
        rt_kprintf("led_thread create...ok\n");
        return 0;
    } else {
        rt_kprintf("led_thread create...failed\n");
        return -1;
    }
}
/*------------------------------------*/
/*ADC相电流采样线程*/
/*------------------------------------*/
void adc_thread_entry(void *parameter) {
    MX_ADC1_Init();


    uint16_t adc_value = 0;  //AD采集值
    int adc_real_value = 0;//AD电压值

    while (1) {
        HAL_ADC_Start(&hadc1);
        adc_value = HAL_ADC_GetValue(&hadc1);
        adc_real_value = (int) ((float) (adc_value) / 4096 * 330);
        rt_kprintf("adc is %d\t%d \n", adc_value, adc_real_value);
        rt_thread_delay(50);
    }
}

int create_adc_thread(void) {
    adc_thread = rt_thread_create("ADC",
                                  adc_thread_entry,
                                  RT_NULL,
                                  ADC_STACK_SIZE,
                                  ADC_PRIORITY,
                                  ADC_TICK);

    if (adc_thread != RT_NULL) {
        rt_thread_startup(adc_thread);
        rt_kprintf("adc_thread create...ok\n");
        return 0;
    } else {
        rt_kprintf("adc_thread create...failed\n");
        return -1;
    }
}