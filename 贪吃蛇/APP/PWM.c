#include "PWM.h"
#include "OLED.h"

unsigned int ms_n = 0;  //��ʱ

void Tim1_Delay_ms(int ms)
{
     int n = 0;
     ms_n = 0;
     n= ms/0.05;    //TIM1��ʱ��ÿ50us��ms_n +1
     while(ms_n != n);
}
//��ʼ����ʱ��
void time1_init(float D)     					 //D---Duty
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
     NVIC_InitTypeDef NVIC_InitStructure;
	//������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);

	//*************************************************************************
	//��ʱ������20KHz
	//*************************************************************************
	TIM_TimeBaseStructure.TIM_Period = 1799;			//������������һ�������¼�װ�����Զ�װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 1;		//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ Ƶ�� = (72000)/(Prescaler*Period)KHz
	TIM_TimeBaseStructure.TIM_ClockDivision =  0;	//����ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//ѡ�����ģʽ TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //
	TIM_TimeBaseInit(TIM1 , &TIM_TimeBaseStructure);	//�������Ϲ��ܶԶ�ʱ�����г�ʼ��
	// TIM_ARRPreloadConfig(TIM1, ENABLE); 
	//����ʱ��ΪPWM1ģʽ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;			//TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ѡ������Ƚ�״̬��ʹ������Ƚ�״̬
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;	//ʧ������Ƚ�N״̬												
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		//TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;		//�����������
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //   //MOE=0ʱ������TIM����ȽϿ���״̬
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;//	//MOE=0ʱ������TIM����ȽϿ���N״̬
	TIM_OCInitStructure.TIM_Pulse = (1800*D);				//ռ�ձ�Ϊ50%�����ô�װ�벶��ȽϼĴ���������ֵ��Pulse=(Period*Duty)
	TIM1_OCInit(TIM1,&TIM_OCInitStructure);					//CH1ռ�ձ�Ϊ50%  @@@@ʹ���˺궨��
	TIM1_OCPreload(TIM1,TIM_OCPreload_Enable);				//ʹ�ܵ�Ԥװ�ؼĴ���	
     
     NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;                   //ʹ��ָ��IRQͨ��
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;         //�����ж���ռ���ȼ�
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                //�����ȼ�
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                   //ʹ��NVIC IRQChannel�ж����IRQͨ��
     NVIC_Init(&NVIC_InitStructure);
     
       // TIM_ARRPreloadConfig(TIM8,ENABLE);
	TIM_Cmd(TIM1,ENABLE);		//ʹ��TIM1�����																					//ʹ�ܶ�ʱ��
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
		
	TIM_ITConfig(      //ʹ�ܻ���ʧ��ָ����TIM�ж�  
    TIM1,            //TIM1  
    TIM_IT_Update  | //TIM �����ж�Դ  
    TIM_IT_Trigger,  //TIM �����ж�Դ   
    ENABLE           //ʹ��  
    ); 
   
     
}
void TIM1_UP_IRQHandler(void)   
{      
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)//���ָ����TIM�жϷ������:TIM �ж�Դ   
    { 
         ms_n++;    //������ʱ����
    }       
     TIM_ClearITPendingBit(TIM1, TIM_IT_Update);//���TIMx���жϴ�����λ:TIM �ж�Դ       
} 


//TIM2���������ͬƵ�ʵ�PWM
void time2_init(float D)
{
  TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	//������ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);

	//*************************************************************************
	//��ʱ������
	//*************************************************************************
	TIM_TimeBaseStructure.TIM_Period = 199;				//������������һ�������¼�װ�����Զ�װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 7200;			//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ Ƶ�� (72000)/(Prescaler*Period)KHz
	TIM_TimeBaseStructure.TIM_ClockDivision =  0;			//����ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//ѡ�����ģʽ TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //     
	TIM_TimeBaseInit(TIM2 , &TIM_TimeBaseStructure);		//�������Ϲ��ܶԶ�ʱ�����г�ʼ��
	//����ʱ��ΪPWM1ģʽ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				//TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ѡ������Ƚ�״̬��ʹ������Ƚ�״̬
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;	//ʧ������Ƚ�N״̬												
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		//TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;		//�����������
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //  //MOE=0ʱ������TIM����ȽϿ���״̬
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;//	//MOE=0ʱ������TIM����ȽϿ���N״̬
	TIM_OCInitStructure.TIM_Pulse = (200*D);					//ռ�ձ�Ϊ50%�����ô�װ�벶��ȽϼĴ���������ֵ��Pulse=(Period*Duty)
	TIM2_OCInit(TIM2,&TIM_OCInitStructure);						//CH2ռ�ձ�Ϊ50%
	TIM2_OCPreload(TIM2,TIM_OCPreload_Enable);					//ʹ�ܵ�Ԥװ�ؼĴ���	
		
 
	TIM_Cmd(TIM2,ENABLE);																							//ʹ�ܶ�ʱ��
}
//*****************************************************************************
//�����������
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
