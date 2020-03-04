//主函数使用 PB6(TIM4 CH1) PB7(TIM4 CH2)
//int main()
//{
//     TIM4_Cap_Init();  
//      while(1)
//      {
//           
//      }
//	
//} 设置相应的中断程序内容
//优先级分组方式:最高2位用于指定抢占式优先级，最低2位用于指定响应优先级。有多个中断必须添加下面这一行！！
//   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
#ifndef __INPUTCAP_H
#define __INPUTCAP_H
void TIM4_Cap_Init(void);
#endif
