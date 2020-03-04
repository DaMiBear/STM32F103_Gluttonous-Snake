#ifndef __AD_H
#define __AD_H
#include "stm32f10x.h"
#include "stm32f10x_adc.h"
//主函数使用如下(包含stm32f10x_adc.h)
//int main()
//{
//  ADCx_Init();
//  read_ADC();
//  OLED_ShowNum(32,0,AD_a,1,12);            // y  x   number length    bits
//          OLED_ShowNum(48,0,AD_b,1,12);
//          OLED_ShowNum(56,0,AD_c,1,12);
//          OLED_ShowNum(65,0,AD_d,1,12);
//          delay(10);
//return 0;
//}
#define uint unsigned int 
#define uchar unsigned char
 //在连接端口改变时，需要改变一下宏定义   
#define   AD_GPIO		       GPIOA		//ADC使用的IO
#define   AD1                   GPIO_Pin_1	//IO引脚
#define   AD2                   GPIO_Pin_0
#define   AD_Channel		  ADC_Channel_1//对应通道
#define   AD2_Channel           ADC_Channel_0
void ADC1_Init(void);
void ADC2_Init(void);
void read_ADC(void);

#endif
