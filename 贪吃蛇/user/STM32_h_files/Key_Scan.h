#ifndef __KEY_SCAN_H
#define __KEY_SCAN_H
#include "stm32f10x.h"
//主函数使用如下
//int main()
//{
//	Key_Scan_Init();
//	
//	while(1)
//	{	
//		Key_Scan();
//	}	
//	return 0;
//}

#define 		X1_H			GPIO_SetBits(GPIOA,GPIO_Pin_12)
#define 		X2_H			GPIO_SetBits(GPIOA,GPIO_Pin_11)
#define 		X3_H			GPIO_SetBits(GPIOA,GPIO_Pin_10)
#define 		X4_H			GPIO_SetBits(GPIOA,GPIO_Pin_9)


#define	     X1_L			GPIO_ResetBits(GPIOA,GPIO_Pin_12)
#define		X2_L			GPIO_ResetBits(GPIOA,GPIO_Pin_11)
#define		X3_L			GPIO_ResetBits(GPIOA,GPIO_Pin_10)
#define		X4_L			GPIO_ResetBits(GPIOA,GPIO_Pin_9)

#define        ReadY1State    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)
#define        ReadY2State    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)
#define        ReadY3State    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)
#define        ReadY4State    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)
void Key_Scan_Init(void);
void Key_Scan(void);


#endif
