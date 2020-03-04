#include "LCD12864.h"
#include "delay.h"
#include "stdio.h"
//将所有引脚配置为输出模式
void LCD_GPIO_OutMode_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct; //结构体命名  
    //D,B,E,C端口使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOC,ENABLE);
	//PD15 PD14 PD12 PD10 PD8
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;         //推挽输出
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_12  | GPIO_Pin_10 | GPIO_Pin_8 ;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;			//最高输出速率50Mhz
	GPIO_Init(GPIOD,&GPIO_InitStruct);          //初始化PD端口
	//PB14 PB12 PB10 PB8 
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;         //推挽输出
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_14 | GPIO_Pin_12 | GPIO_Pin_10 | GPIO_Pin_8;	
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;			//最高输出速率50Mhz
	GPIO_Init(GPIOB,&GPIO_InitStruct);          //初始化PB端口
    
    //PE14 PE12 PE10 PE8    
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;         //推挽输出
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_14 | GPIO_Pin_12 | GPIO_Pin_10 | GPIO_Pin_8;	
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;			//最高输出速率50Mhz
	GPIO_Init(GPIOE,&GPIO_InitStruct);          //初始化PE端口
    //PC6
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;              //推挽输出
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;		
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;			//最高输出速率50Mhz
	GPIO_Init(GPIOC,&GPIO_InitStruct);                      //初始化PC端口
}
//将数据IO口配置为输入模式
void LCD_GPIO_InMode_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct; //结构体命名  
    //D,B,E端口使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE,ENABLE);
	//PD10 PD8
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;         //浮空输入
	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_10 | GPIO_Pin_8 ;
	GPIO_Init(GPIOD,&GPIO_InitStruct);          //初始化PD端口
	//PB14 PB12 PB10 PB8 
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;          //浮空输入
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_14 | GPIO_Pin_12 | GPIO_Pin_10 | GPIO_Pin_8;	
	GPIO_Init(GPIOB,&GPIO_InitStruct);          //初始化PB端口
    
    //PE14 PE12    
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;          //浮空输入
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_14 | GPIO_Pin_12 ;	
	GPIO_Init(GPIOE,&GPIO_InitStruct);          //初始化PE端口
   
}

//LCD写命令函数
void LCD_WriteCmd(uint8_t cmd)
{
    LCD_WaitBusy();     //忙检测
    
    RS_LOW;             //RS = 0
    RW_LOW;             //RW = 0
    E_HIGH;             //EN = 1
    
    LCD_DBWrite(cmd);   //写数据
    delay_ms(2);
    
    E_LOW;              //EN = 0
   delay_ms(2);
}
//LCD忙检测函数
void LCD_WaitBusy()
{
    LCD_GPIO_InMode_Init();     //把数据引脚改为输入模式
    RS_LOW;             //RS = 0    读出忙标志
    RW_HIGH;            //RW = 1;
    E_HIGH;             //EN = 1;//配合R进行读数据和指令
    
    while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12));       //检测DB7端口的状态  1忙碌  0不忙碌
    
    E_LOW;
    LCD_GPIO_OutMode_Init();    //把引脚改为输出 准备进行写数据和指令
}
//对LCD的DB的8个端口写操作函数
void LCD_DBWrite(uint8_t oct)
{  
    if((oct) & 1) //每次把8位数据右移一位再取第一位的数进行判断来操控端口
        DB0_HIGH;
    else
        DB0_LOW;
    
    if((oct>>1) & 1)
        DB1_HIGH;
    else
        DB1_LOW;
    
    if((oct>>2) & 1)
        DB2_HIGH;
    else
        DB2_LOW;
    
    if((oct>>3) & 1)
        DB3_HIGH;
    else 
        DB3_LOW;
    
    if((oct>>4) & 1)
        DB4_HIGH;
    else
        DB4_LOW;
    
    if((oct>>5) & 1)
        DB5_HIGH;
    else
        DB5_LOW;
    
    if((oct>>6) & 1)
        DB6_HIGH;
    else
        DB6_LOW;
    
    if((oct>>7) & 1)
        DB7_HIGH;
    else
        DB7_LOW;
    
}
//LCD写数据函数
void LCD_WriteData(uint8_t data)
{
    LCD_WaitBusy();     //忙检测
    
    RS_HIGH;            //RS = 1
    RW_LOW;             //RW = 0
    E_HIGH;             //EN = 1
    
    LCD_DBWrite(data);
    
    delay_ms(2);
    E_LOW;              //EN = 0
    delay_ms(2);
}
//LCD定位函数----
/*地址实际上是两行*/
void LCD_SetPosition(uint8_t xpos,uint8_t ypos)
{
    uint8_t xy_pos;
    if((xpos >= 8) || (ypos >= 4))      //4行8列显示 判断是否超出范围
        return;
    /*计算转换地址*/
    if(ypos==0)      xy_pos = 0x80 + xpos;
	else if(ypos==1) xy_pos = 0x90 + xpos; 
	else if(ypos==2) xy_pos = 0x88 + xpos;
	else if(ypos==3) xy_pos = 0x98 + xpos;
    //写地址
    LCD_WriteCmd(xy_pos);
}
//显示字符串
void LCD_ShowString(uint8_t x,uint8_t y,uint8_t * str)
{
    LCD_WriteCmd(0x30);     //8位数据模式
    LCD_SetPosition(x,y);
    
    for(;*str!='\0';str++)
	{
		LCD_WriteData(*str);
        delay_ms(2);
	}
}
//清除GDRAM
/*看不懂*/
void LCD_ClearGDRAM()
{
    uint8_t x,y;
    LCD_WriteCmd(0x34);     //扩充指令集
    
    for(y=0;y<32;y++) 
    {
        for(x=0;x<16;x++) 
        {            
//            sprintf(st,"x:%d y:%d",x,y);
//			LCD_ShowString(0,2,(unsigned char *)st);
            LCD_WriteCmd(y+0x80);        //行地址 
            LCD_WriteCmd(x+0x80);     	 //列地址 				
            LCD_WriteData(0x00); 
            LCD_WriteData(0x00);  
          
        }   
    }
    
    LCD_WriteCmd(0x36); 
}
//从LCD读数据
uint8_t LCD_ReadOneData()
{
    unsigned char dat;
    LCD_WaitBusy();
	
	LCD_GPIO_InMode_Init();
	
	RS_HIGH;
	RW_HIGH; 
	E_HIGH;

	delay_ms(10);
    dat = LCD_DBRead();
	
    E_LOW;                          //EN = 0;
 
    LCD_GPIO_OutMode_Init();        
    return (dat);
}    
//读取DB端口的值
uint8_t LCD_DBRead(void)
{
    uint8_t data;
    data = GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12);
    data = (GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)) | (data<<1);
    data = (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)) | (data<<1);
    data = (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)) | (data<<1);
    data = (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)) | (data<<1);
    data = (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)) | (data<<1);
    data = (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_8)) | (data<<1);
    data = (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_10)) | (data<<1);
    return data;
}
//看不懂 看不懂！！！！！
void LCD_DrawPoint(uint8_t x,uint8_t y,uint8_t displayOrNot)
{
    unsigned char zuobiao_x0,zuobiao_y0,zuobiao_y1;
    unsigned int zuobiao_x1,dat;
    
    zuobiao_y0 = y/32;  //在上行0，在下行1
    zuobiao_y1 = y%32;  //行地址 
    zuobiao_x0 = x/16;  //列地址的分量
    zuobiao_x1 = 0x8000>>(x%16);
    
    LCD_WriteCmd(0x34); //执行扩展指令
    LCD_WriteCmd(0x36); //开画图显示
    LCD_WriteCmd(0x80 + zuobiao_y1);     //行地址 
    LCD_WriteCmd(0x80 + zuobiao_y0*8 + zuobiao_x0);     //列地址 
    

    //读当前地址数据
    LCD_ReadOneData();//假读一次
    dat = (unsigned int)LCD_ReadOneData()<<8;//读高8位
    dat |=  LCD_ReadOneData();//读低8位
    if(displayOrNot==0) zuobiao_x1 = (~zuobiao_x1)&dat;
    else zuobiao_x1 |= dat;
    
    LCD_WriteCmd(0x80 + zuobiao_y1);     //行地址 
    LCD_WriteCmd(0x80 + zuobiao_y0*8 + zuobiao_x0);     //列地址 
    
    LCD_WriteData((unsigned char)(zuobiao_x1>>8)); 
    LCD_WriteData((unsigned char)zuobiao_x1);
    
    
}
//读点 x:0~127 y:0~63 返回值:当前点的值
uint8_t LCD_ReadPoint(uint8_t x,uint8_t y)
{
    unsigned char zuobiao_x0,zuobiao_y0,zuobiao_y1;
    unsigned int zuobiao_x1,dat;
    
    zuobiao_y0 = y/32;  //在上行0，在下行1
    zuobiao_y1 = y%32;  //行地址 
    zuobiao_x0 = x/16;  //列地址的分量
    zuobiao_x1 = 0x8000>>(x%16);
    
//    LCD12864_COM_Write(0x36); //执行扩展指令，开画图显示
    LCD_WriteCmd(0x80 + zuobiao_y1);     //行地址 
    LCD_WriteCmd(0x80 + zuobiao_y0*8 + zuobiao_x0);     //列地址 
    
    //读当前地址数据
    LCD_ReadOneData();//假读一次
    dat = (unsigned int)LCD_ReadOneData()<<8;//读高8位
    dat |=  LCD_ReadOneData();//读低8位
    
    if((dat&zuobiao_x1) == 0) return 0;  
    
    else return 1;
}
//初始化
void LCD_Init(void)
{
    LCD_GPIO_OutMode_Init();            //引脚改为输出
    RESET_HIGH;              
    delay_init();       //初始化延时函数
               
    PSB_HIGH;                   //并口方式
    
    
    
    delay_ms(2); 
    LCD_WriteCmd(0x30);         //选择基本指令集，和，8位数据模式。
    
    delay_ms(2); 
    LCD_WriteCmd(0x0c);         //开显示,无游标,不反白.
    
    delay_ms(2); 
    LCD_WriteCmd(0x01);         //清除显示，并将 DDRAM 的地址计数器 AC 设为 00H.
    
    delay_ms(2); 
    LCD_WriteCmd(0x06);         //设置，外部读写数据后,地址记数器 AC 会自动加 1。
    
    delay_ms(2); 
    LCD_WriteCmd(0x80);         ////将 DDRAM 地址计数器 AC 设为 0.
    
    delay_ms(2); 
      
}
//清屏
void LCD_Cls()
{
   LCD_WriteCmd(0x01);
}
