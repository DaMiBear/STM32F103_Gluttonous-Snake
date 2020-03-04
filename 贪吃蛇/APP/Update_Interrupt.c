#include "Update_Interrupt.h"
void time3_init()
{
    //  TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
      NVIC_InitTypeDef NVIC_InitStructure;

	//������ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);

	//*************************************************************************
	//��ʱ������20KHz
	//*************************************************************************
	TIM_TimeBaseStructure.TIM_Period = 1799;			//������������һ�������¼�װ�����Զ�װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 1;			//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ Ƶ�� (72000)/(Prescaler*Period)KHz
	TIM_TimeBaseStructure.TIM_ClockDivision =  0;		//����ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;			//ѡ�����ģʽ TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3 , &TIM_TimeBaseStructure);			//�������Ϲ��ܶԶ�ʱ�����г�ʼ��
     TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                //����ʱ���ж�
     TIM_Cmd(TIM3,ENABLE);                                  //ʹ�ܶ�ʱ��
 
       //ʹ��TIM3�ж�
     NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                   //ʹ��ָ��IRQͨ��
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;         //�����ж���ռ���ȼ�
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                //�����ȼ�
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                   //ʹ��NVIC IRQChannel�ж����IRQͨ��
     NVIC_Init(&NVIC_InitStructure);
  

} 

void TIM3_IRQHandler()
{   
   if(TIM_GetITStatus(TIM3,TIM_IT_Update) !=RESET)
   {
        TIM_ClearITPendingBit(TIM3,TIM_IT_Update);

          
        
   }
}
