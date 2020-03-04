#include "InputCap.h"
#include "stm32f10x.h"
#include "OLED.h"
#include "PWM.h"       
void TIM4_Cap_Init()
{
     //�ṹ������
     GPIO_InitTypeDef GPIO_InitStructure;
     TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
     TIM_ICInitTypeDef  TIM4_ICInitStructure;
     NVIC_InitTypeDef NVIC_InitStructureIC;
     //ʹ��ʱ��TIM4��GPIOB
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //���ȼ����鷽ʽ:���2λ����ָ����ռʽ���ȼ������2λ����ָ����Ӧ���ȼ���
     //���ö˿�Ϊ��������ģʽ
     GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;  
     GPIO_Init(GPIOB, &GPIO_InitStructure);
     GPIO_ResetBits(GPIOB,GPIO_Pin_6 | GPIO_Pin_7);
     //��ʱ������   1200kHz
     TIM_TimeBaseStructure.TIM_Period = 29; //���ü���ֵ�����ֵ
     TIM_TimeBaseStructure.TIM_Prescaler = 9;     //�����Ĵ�����Ƶ�ʵķ�Ƶϵ��
     TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //ʱ�ӷָ�
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //�������ϼ��� 
     TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);  //��ʼ��
     //��ʱ�����벶������ ͨ��1
     TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1;             //ѡ��ͨ��1
     TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;  //�����ش��������½��ش���������
     TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TT1��
     TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;        //���������Ƶ ����Ƶ
     TIM4_ICInitStructure.TIM_ICFilter = 0xf;                     //�˲������� ����Ƶ��fSAMPLING=fDTS/32�� N=8
     TIM_ICInit(TIM4, &TIM4_ICInitStructure);
     //ͨ��2
     TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2;               
     TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; 
     TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
     TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;       
     TIM4_ICInitStructure.TIM_ICFilter = 0xf; 
     TIM_ICInit(TIM4, &TIM4_ICInitStructure);
     //�ж�����
     NVIC_InitStructureIC.NVIC_IRQChannel = TIM4_IRQn;  //TIM4�����ж�
     NVIC_InitStructureIC.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ�жϵȼ�
     NVIC_InitStructureIC.NVIC_IRQChannelSubPriority = 0;         //���жϵȼ�
     NVIC_InitStructureIC.NVIC_IRQChannelCmd = ENABLE; //ʹ���ж�ͨ��
     NVIC_Init(&NVIC_InitStructureIC);  //��ʼ�� 
     
     TIM_ITConfig(TIM4,TIM_IT_CC1 | TIM_IT_CC2,ENABLE);//ʹ�ܸ����ж�
     TIM_Cmd(TIM4,ENABLE ); //ʹ�ܶ�ʱ��TIM4
     
     
}
     
//���벶��---�����жϳ���
void TIM4_IRQHandler(void)
{
     //CH1ͨ����PB6���½��ط��������¼�
     if(TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET) 
     {
     /*�������*/
          
     }
     //CH2ͨ����PB7�������ش��������¼�
    if(TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET) 
    { 
     /* ������� **/
        
    }
     TIM_ClearITPendingBit(TIM4, TIM_IT_CC1 | TIM_IT_CC2); //����жϱ�־
}
