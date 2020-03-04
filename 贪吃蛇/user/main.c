#include "stm32f10x.h"
//#include "InputCap.h"
//#include "OLED.h"
//#include "AD.h"
//#include "PWM.h"
//#include "Update_Interrupt.h"
#include "AD_DMA.h"
//#include "Key_Scan.h"
#include "LCD12864.h"
#include "Snake.h"
#include "delay.h"
int main()
{
    //LCD12864��ʼ��
    LCD_Init();         //LCD��ʼ��+��ʱ������ʼ��
    
    //��Ϸ˵��
    gameDescription();  //��Ϊ�����ClearGDRAM�����ȽϷ�ʱ�� ��������ʾһ����Ϸ˵���ֲ�һ��
    //GDRAM��ַ��ʼ��
    LCD_ClearGDRAM();   //������˵LCD�ո��ϵ� GDRAM��ַ���ҵģ������ͻ�ѵ���ʾ����,����Ҫ����ַ��ֵ
    
    //����
    gameDescription();   //��֪��Ϊʲô֮ǰ��ClearGDRAM֮��ֱ����������������ʾ�������֮ǰ������ʾ����
    LCD_Cls();  //Ȼ���������� Ŀǰ����������������
   
    //��Ϸ������� ���Ҳ�е��ʱ��
    wallCreate();   //����ǽ�ںͷ����ٶ�����
    snakeCreate();  //������
    spawnFood();    //����ʳ��
    //ҡ�˳�ʼ��
    ADC1_GPIO_Config();
    ADC1_Mode_Config();
    
    //��ʼ��Ϸ
    gameControl();	//������ѭ��
    while(1)
    {
         
      
//        if(MyDirection == NORTH)
//        {
//            LCD_ShowString(0,0,(unsigned char *)"��"); 
//        }
//        else if(MyDirection == SOUTH)
//        {
//            LCD_ShowString(0,0,(unsigned char *)"��");
//        }
//        else if(MyDirection == WEST)
//        {
//            LCD_ShowString(0,0,(unsigned char *)"��");
//        }
//        else if(MyDirection == EAST)
//        {
//            LCD_ShowString(0,0,(unsigned char *)"��");
//        }


    }
	
}
