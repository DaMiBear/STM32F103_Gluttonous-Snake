#ifndef __PWM_H
#define __PWM_H
#include "stm32f10x.h"
//��������ʹ������(�����stm32f10x_tim.c)
//int main()
//{
//	
//	time_gpio();
//	time1_init(0.5);
//  time2_init(0.60);

//return 0;
//}
void time1_init(float D);
void time1_gpio(void);
void time2_init(float D);
void Tim1_Delay_ms(int ms);

#define			TIM1_OCInit						TIM_OC1Init	//TIM1ͨ��1 PA8
#define			TIM1_OCPreload						TIM_OC1PreloadConfig	//PB13				
#define			TIM2_OCInit						TIM_OC4Init	//TIM2ͨ��4
#define			TIM2_OCPreload						TIM_OC4PreloadConfig
#define			GPIO_Clock_PWM1					RCC_APB2Periph_GPIOA	//TIM8 ͨ��2  ��Ӧ����
#define			GPIO_Clock_PWM1N					RCC_APB2Periph_GPIOB	//TIM8 ���������Ӧ����
#define			GPIO_Clock_PWM2					RCC_APB2Periph_GPIOA	//TIM2 ͨ��4  ��Ӧ����
#define			GPIO_PWM1							GPIOA
#define			GPIO_PWM1N						GPIOB
#define			GPIO_PWM2							GPIOA
#define			GPIO_Pin_PWM1						GPIO_Pin_8
#define			GPIO_Pin_PWM1N						GPIO_Pin_13
#define 		     GPIO_Pin_PWM2						GPIO_Pin_3


#endif
