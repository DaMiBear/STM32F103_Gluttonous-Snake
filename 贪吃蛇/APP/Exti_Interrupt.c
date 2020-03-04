#include "Exti_Interrupt.h"


void Exti_Init()
{
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);    //�������ù���!!
  GPIO_InitStructure.GPIO_Pin= GPIO_Pin_8; 
  GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IN_FLOATING;          //����Ϊ����
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;          
  GPIO_Init(GPIOC,&GPIO_InitStructure);  
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;        //              //�ⲿ�ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;             //��ռ���ȼ�
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                    //�����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
  NVIC_Init(&NVIC_InitStructure);
  
  EXTI_ClearITPendingBit(EXTI_Line8);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource8);          //�����ж���IO��
  EXTI_InitStructure.EXTI_Line = EXTI_Line8;                          //��ʹ���ⲿ��·
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;                 //EXTI����Ϊ�ж�����
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;              //�����ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;                   
  EXTI_Init(&EXTI_InitStructure);
}

//�ⲿ�ж�8���жϺ���
void EXTI9_5_IRQHandler(void)
{
   if(EXTI_GetITStatus(EXTI_Line8) != RESET)
   {
      EXTI_ClearITPendingBit(EXTI_Line8);
     
  
  }
}
