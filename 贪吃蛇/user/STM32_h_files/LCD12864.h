#ifndef _LCD12864_H
#define _LCD12864_H
#include "stm32f10x.h"

#define     RS_HIGH         GPIO_SetBits(GPIOD,GPIO_Pin_15)
#define     RS_LOW          GPIO_ResetBits(GPIOD,GPIO_Pin_15)

#define     RW_HIGH         GPIO_SetBits(GPIOD,GPIO_Pin_14)
#define     RW_LOW          GPIO_ResetBits(GPIOD,GPIO_Pin_14)

#define     E_HIGH          GPIO_SetBits(GPIOD,GPIO_Pin_12)
#define     E_LOW           GPIO_ResetBits(GPIOD,GPIO_Pin_12)

#define     DB0_HIGH        GPIO_SetBits(GPIOD,GPIO_Pin_10)
#define     DB0_LOW         GPIO_ResetBits(GPIOD,GPIO_Pin_10)

#define     DB1_HIGH        GPIO_SetBits(GPIOD,GPIO_Pin_8)
#define     DB1_LOW         GPIO_ResetBits(GPIOD,GPIO_Pin_8)

#define     DB2_HIGH        GPIO_SetBits(GPIOB,GPIO_Pin_14)
#define     DB2_LOW         GPIO_ResetBits(GPIOB,GPIO_Pin_14)

#define     DB3_HIGH        GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define     DB3_LOW         GPIO_ResetBits(GPIOB,GPIO_Pin_12)

#define     DB4_HIGH        GPIO_SetBits(GPIOB,GPIO_Pin_10)
#define     DB4_LOW         GPIO_ResetBits(GPIOB,GPIO_Pin_10)

#define     DB5_HIGH        GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define     DB5_LOW         GPIO_ResetBits(GPIOB,GPIO_Pin_8)

#define     DB6_HIGH        GPIO_SetBits(GPIOE,GPIO_Pin_14)
#define     DB6_LOW         GPIO_ResetBits(GPIOE,GPIO_Pin_14)

#define     DB7_HIGH        GPIO_SetBits(GPIOE,GPIO_Pin_12)
#define     DB7_LOW         GPIO_ResetBits(GPIOE,GPIO_Pin_12)

#define     PSB_HIGH        GPIO_SetBits(GPIOE,GPIO_Pin_10)          
#define     PSB_LOW         GPIO_ResetBits(GPIOE,GPIO_Pin_10)

#define     NC_HIGH         GPIO_SetBits(GPIOE,GPIO_Pin_8)   
#define     NC_LOW          GPIO_ResetBits(GPIOE,GPIO_Pin_8)

#define     RESET_HIGH     GPIO_SetBits(GPIOC,GPIO_Pin_6)
#define     RESET_LOW       GPIO_ResetBits(GPIOC,GPIO_Pin_6)


void    LCD_GPIO_OutMode_Init(void);    //������������Ϊ���ģʽ
void    LCD_GPIO_InMode_Init(void);     //������������Ϊ����ģʽ
void    LCD_WriteCmd(uint8_t);          //LCDд�����     
void    LCD_WaitBusy(void);              //LCDæ��⺯��
void    LCD_DBWrite(uint8_t);           //LCD DB��������
void    LCD_WriteData(uint8_t);         //LCDд���ݺ���
void    LCD_SetPosition(uint8_t ,uint8_t);//LCD��λ
void    LCD_ShowString(uint8_t,uint8_t,uint8_t *);//��ʾ�ַ���
void    LCD_ClearGDRAM(void);               //LCD���GDRAM
uint8_t LCD_ReadOneData(void);               //LCD������
uint8_t LCD_DBRead(void);                   //��ȡDB�˿ڵ�ֵ
void    LCD_DrawPoint(uint8_t,uint8_t,uint8_t);//����
uint8_t LCD_ReadPoint(uint8_t,uint8_t);        //����
void    LCD_Init(void);                     //LCD12864��ʼ������
void    LCD_Cls(void);                  //LCD����
#endif
