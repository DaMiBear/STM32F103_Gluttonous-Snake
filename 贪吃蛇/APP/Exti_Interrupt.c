#include "Exti_Interrupt.h"


void Exti_Init()
{
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);    //启动复用功能!!
  GPIO_InitStructure.GPIO_Pin= GPIO_Pin_8; 
  GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IN_FLOATING;          //配置为输入
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;          
  GPIO_Init(GPIOC,&GPIO_InitStructure);  
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;        //              //外部中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;             //先占优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                    //从优先级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
  NVIC_Init(&NVIC_InitStructure);
  
  EXTI_ClearITPendingBit(EXTI_Line8);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource8);          //连接中断与IO口
  EXTI_InitStructure.EXTI_Line = EXTI_Line8;                          //待使能外部线路
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;                 //EXTI设置为中断请求
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;              //上升沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;                   
  EXTI_Init(&EXTI_InitStructure);
}

//外部中断8的中断函数
void EXTI9_5_IRQHandler(void)
{
   if(EXTI_GetITStatus(EXTI_Line8) != RESET)
   {
      EXTI_ClearITPendingBit(EXTI_Line8);
     
  
  }
}
