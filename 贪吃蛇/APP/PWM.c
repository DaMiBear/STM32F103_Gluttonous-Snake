#include "PWM.h"
#include "OLED.h"

unsigned int ms_n = 0;  //延时

void Tim1_Delay_ms(int ms)
{
     int n = 0;
     ms_n = 0;
     n= ms/0.05;    //TIM1定时器每50us把ms_n +1
     while(ms_n != n);
}
//初始化定时器
void time1_init(float D)     					 //D---Duty
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
     NVIC_InitTypeDef NVIC_InitStructure;
	//打开外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);

	//*************************************************************************
	//定时器设置20KHz
	//*************************************************************************
	TIM_TimeBaseStructure.TIM_Period = 1799;			//用于设置在下一个更新事件装入活动的自动装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 1;		//设置用来作为TIMx时钟频率除数的预分频值 频率 = (72000)/(Prescaler*Period)KHz
	TIM_TimeBaseStructure.TIM_ClockDivision =  0;	//设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//选择计数模式 TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //
	TIM_TimeBaseInit(TIM1 , &TIM_TimeBaseStructure);	//根据以上功能对定时器进行初始化
	// TIM_ARRPreloadConfig(TIM1, ENABLE); 
	//主定时器为PWM1模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;			//TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//选择输出比较状态，使能输出比较状态
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;	//失能输出比较N状态												
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		//TIM输出比较极性高
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;		//互补输出极性
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //   //MOE=0时，重置TIM输出比较空闲状态
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;//	//MOE=0时，重置TIM输出比较空闲N状态
	TIM_OCInitStructure.TIM_Pulse = (1800*D);				//占空比为50%（设置待装入捕获比较寄存器的脉冲值）Pulse=(Period*Duty)
	TIM1_OCInit(TIM1,&TIM_OCInitStructure);					//CH1占空比为50%  @@@@使用了宏定义
	TIM1_OCPreload(TIM1,TIM_OCPreload_Enable);				//使能的预装载寄存器	
     
     NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;                   //使能指定IRQ通道
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;         //设置中断先占优先级
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                //从优先级
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                   //使能NVIC IRQChannel中定义的IRQ通道
     NVIC_Init(&NVIC_InitStructure);
     
       // TIM_ARRPreloadConfig(TIM8,ENABLE);
	TIM_Cmd(TIM1,ENABLE);		//使能TIM1主输出																					//使能定时器
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
		
	TIM_ITConfig(      //使能或者失能指定的TIM中断  
    TIM1,            //TIM1  
    TIM_IT_Update  | //TIM 更新中断源  
    TIM_IT_Trigger,  //TIM 触发中断源   
    ENABLE           //使能  
    ); 
   
     
}
void TIM1_UP_IRQHandler(void)   
{      
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)//检查指定的TIM中断发生与否:TIM 中断源   
    { 
         ms_n++;    //用于延时函数
    }       
     TIM_ClearITPendingBit(TIM1, TIM_IT_Update);//清除TIMx的中断待处理位:TIM 中断源       
} 


//TIM2用于输出不同频率的PWM
void time2_init(float D)
{
  TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	//打开外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);

	//*************************************************************************
	//定时器设置
	//*************************************************************************
	TIM_TimeBaseStructure.TIM_Period = 199;				//用于设置在下一个更新事件装入活动的自动装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 7200;			//设置用来作为TIMx时钟频率除数的预分频值 频率 (72000)/(Prescaler*Period)KHz
	TIM_TimeBaseStructure.TIM_ClockDivision =  0;			//设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//选择计数模式 TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //     
	TIM_TimeBaseInit(TIM2 , &TIM_TimeBaseStructure);		//根据以上功能对定时器进行初始化
	//主定时器为PWM1模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				//TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//选择输出比较状态，使能输出比较状态
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;	//失能输出比较N状态												
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		//TIM输出比较极性高
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;		//互补输出极性
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //  //MOE=0时，重置TIM输出比较空闲状态
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;//	//MOE=0时，重置TIM输出比较空闲N状态
	TIM_OCInitStructure.TIM_Pulse = (200*D);					//占空比为50%（设置待装入捕获比较寄存器的脉冲值）Pulse=(Period*Duty)
	TIM2_OCInit(TIM2,&TIM_OCInitStructure);						//CH2占空比为50%
	TIM2_OCPreload(TIM2,TIM_OCPreload_Enable);					//使能的预装载寄存器	
		
 
	TIM_Cmd(TIM2,ENABLE);																							//使能定时器
}
//*****************************************************************************
//定义输出引脚
//*****************************************************************************
void time1_gpio()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(GPIO_Clock_PWM1|GPIO_Clock_PWM1N | RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_PWM1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_PWM1,&GPIO_InitStructure);
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_PWM1N  ;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIO_PWM1N,&GPIO_InitStructure);
  
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_PWM2 ;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIO_PWM2,&GPIO_InitStructure);
     
     
}
