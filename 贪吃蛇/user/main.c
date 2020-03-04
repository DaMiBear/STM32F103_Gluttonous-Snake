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
    //LCD12864初始化
    LCD_Init();         //LCD初始化+延时函数初始化
    
    //游戏说明
    gameDescription();  //因为下面的ClearGDRAM函数比较费时间 所以先显示一串游戏说明弥补一下
    //GDRAM地址初始化
    LCD_ClearGDRAM();   //据网上说LCD刚刚上电 GDRAM地址是乱的，这样就会把点显示错误,所以要给地址赋值
    
    //清屏
    gameDescription();   //不知道为什么之前在ClearGDRAM之后直接清屏，后面再显示会把清屏之前的再显示出来
    LCD_Cls();  //然后发现这样干 目前可以先清除这个问题
   
    //游戏界面绘制 这个也有点费时间
    wallCreate();   //绘制墙壁和分数速度文字
    snakeCreate();  //绘制蛇
    spawnFood();    //生成食物
    //摇杆初始化
    ADC1_GPIO_Config();
    ADC1_Mode_Config();
    
    //开始游戏
    gameControl();	//内有死循环
    while(1)
    {
         
      
//        if(MyDirection == NORTH)
//        {
//            LCD_ShowString(0,0,(unsigned char *)"上"); 
//        }
//        else if(MyDirection == SOUTH)
//        {
//            LCD_ShowString(0,0,(unsigned char *)"下");
//        }
//        else if(MyDirection == WEST)
//        {
//            LCD_ShowString(0,0,(unsigned char *)"左");
//        }
//        else if(MyDirection == EAST)
//        {
//            LCD_ShowString(0,0,(unsigned char *)"右");
//        }


    }
	
}
