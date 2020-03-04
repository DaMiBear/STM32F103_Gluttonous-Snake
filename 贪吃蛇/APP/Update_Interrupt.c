#include "Update_Interrupt.h"
void time3_init()
{
    //  TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
      NVIC_InitTypeDef NVIC_InitStructure;

	//打开外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);

	//*************************************************************************
	//定时器设置20KHz
	//*************************************************************************
	TIM_TimeBaseStructure.TIM_Period = 1799;			//用于设置在下一个更新事件装入活动的自动装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 1;			//设置用来作为TIMx时钟频率除数的预分频值 频率 (72000)/(Prescaler*Period)KHz
	TIM_TimeBaseStructure.TIM_ClockDivision =  0;		//设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;			//选择计数模式 TIM向上计数模式
	TIM_TimeBaseInit(TIM3 , &TIM_TimeBaseStructure);			//根据以上功能对定时器进行初始化
     TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                //开定时器中断
     TIM_Cmd(TIM3,ENABLE);                                  //使能定时器
 
       //使能TIM3中断
     NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                   //使能指定IRQ通道
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;         //设置中断先占优先级
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                //从优先级
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                   //使能NVIC IRQChannel中定义的IRQ通道
     NVIC_Init(&NVIC_InitStructure);
  

} 

void TIM3_IRQHandler()
{   
   if(TIM_GetITStatus(TIM3,TIM_IT_Update) !=RESET)
   {
        TIM_ClearITPendingBit(TIM3,TIM_IT_Update);

          
        
   }
}
