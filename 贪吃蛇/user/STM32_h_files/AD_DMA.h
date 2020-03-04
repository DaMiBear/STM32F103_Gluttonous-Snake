#ifndef __AD_DMA_H
#define __AD_DMA_H

#include "stm32f10x.h"
#define  ADC1_DR_Address    ((u32)0x40012400+0x4c)

void ADC1_GPIO_Config(void);
void ADC1_Mode_Config(void);
enum objectiveDirections read_ADC_DMA(void);    //返回值是方向
//主函数使用如下
/*int main()
{
	ADC1_GPIO_Config();
	ADC1_Mode_Config();
	OLED_Init();
	OLED_Clear();
	OLED_ShowString(0,0,"u1= 0.00");
	OLED_ShowString(0,2,"u2= 0.00");
	OLED_ShowString(0,4,"u3= 0.00");
	OLED_ShowString(0,6,"u4= 0.00");
	

	while(1)
	{
				read_ADC();
				OLED_ShowNum(32,0,AD1_a,1,12);           
        OLED_ShowNum(48,0,AD1_b,1,12);
				OLED_ShowNum(56,0,AD1_c,1,12);
		
				OLED_ShowNum(32,2,AD2_a,1,12);           
        OLED_ShowNum(48,2,AD2_b,1,12);
				OLED_ShowNum(56,2,AD2_c,1,12);
		
				OLED_ShowNum(32,4,AD3_a,1,12);           
        OLED_ShowNum(48,4,AD3_b,1,12);
				OLED_ShowNum(56,4,AD3_c,1,12);
		
				OLED_ShowNum(32,6,AD4_a,1,12);           
        OLED_ShowNum(48,6,AD4_b,1,12);
				OLED_ShowNum(56,6,AD4_c,1,12);
			
      //  OLED_ShowNum(68,0,ADC_ConvertedValue[0],4,12);
	}
	return 0;
}*/
#endif
