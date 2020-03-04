#include "LCD12864.h"
#include "delay.h"
#include "stdio.h"
//��������������Ϊ���ģʽ
void LCD_GPIO_OutMode_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct; //�ṹ������  
    //D,B,E,C�˿�ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOC,ENABLE);
	//PD15 PD14 PD12 PD10 PD8
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;         //�������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_12  | GPIO_Pin_10 | GPIO_Pin_8 ;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;			//����������50Mhz
	GPIO_Init(GPIOD,&GPIO_InitStruct);          //��ʼ��PD�˿�
	//PB14 PB12 PB10 PB8 
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;         //�������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_14 | GPIO_Pin_12 | GPIO_Pin_10 | GPIO_Pin_8;	
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;			//����������50Mhz
	GPIO_Init(GPIOB,&GPIO_InitStruct);          //��ʼ��PB�˿�
    
    //PE14 PE12 PE10 PE8    
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;         //�������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_14 | GPIO_Pin_12 | GPIO_Pin_10 | GPIO_Pin_8;	
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;			//����������50Mhz
	GPIO_Init(GPIOE,&GPIO_InitStruct);          //��ʼ��PE�˿�
    //PC6
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;              //�������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;		
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;			//����������50Mhz
	GPIO_Init(GPIOC,&GPIO_InitStruct);                      //��ʼ��PC�˿�
}
//������IO������Ϊ����ģʽ
void LCD_GPIO_InMode_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct; //�ṹ������  
    //D,B,E�˿�ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE,ENABLE);
	//PD10 PD8
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;         //��������
	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_10 | GPIO_Pin_8 ;
	GPIO_Init(GPIOD,&GPIO_InitStruct);          //��ʼ��PD�˿�
	//PB14 PB12 PB10 PB8 
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;          //��������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_14 | GPIO_Pin_12 | GPIO_Pin_10 | GPIO_Pin_8;	
	GPIO_Init(GPIOB,&GPIO_InitStruct);          //��ʼ��PB�˿�
    
    //PE14 PE12    
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;          //��������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_14 | GPIO_Pin_12 ;	
	GPIO_Init(GPIOE,&GPIO_InitStruct);          //��ʼ��PE�˿�
   
}

//LCDд�����
void LCD_WriteCmd(uint8_t cmd)
{
    LCD_WaitBusy();     //æ���
    
    RS_LOW;             //RS = 0
    RW_LOW;             //RW = 0
    E_HIGH;             //EN = 1
    
    LCD_DBWrite(cmd);   //д����
    delay_ms(2);
    
    E_LOW;              //EN = 0
   delay_ms(2);
}
//LCDæ��⺯��
void LCD_WaitBusy()
{
    LCD_GPIO_InMode_Init();     //���������Ÿ�Ϊ����ģʽ
    RS_LOW;             //RS = 0    ����æ��־
    RW_HIGH;            //RW = 1;
    E_HIGH;             //EN = 1;//���R���ж����ݺ�ָ��
    
    while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12));       //���DB7�˿ڵ�״̬  1æµ  0��æµ
    
    E_LOW;
    LCD_GPIO_OutMode_Init();    //�����Ÿ�Ϊ��� ׼������д���ݺ�ָ��
}
//��LCD��DB��8���˿�д��������
void LCD_DBWrite(uint8_t oct)
{  
    if((oct) & 1) //ÿ�ΰ�8λ��������һλ��ȡ��һλ���������ж����ٿض˿�
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
//LCDд���ݺ���
void LCD_WriteData(uint8_t data)
{
    LCD_WaitBusy();     //æ���
    
    RS_HIGH;            //RS = 1
    RW_LOW;             //RW = 0
    E_HIGH;             //EN = 1
    
    LCD_DBWrite(data);
    
    delay_ms(2);
    E_LOW;              //EN = 0
    delay_ms(2);
}
//LCD��λ����----
/*��ַʵ����������*/
void LCD_SetPosition(uint8_t xpos,uint8_t ypos)
{
    uint8_t xy_pos;
    if((xpos >= 8) || (ypos >= 4))      //4��8����ʾ �ж��Ƿ񳬳���Χ
        return;
    /*����ת����ַ*/
    if(ypos==0)      xy_pos = 0x80 + xpos;
	else if(ypos==1) xy_pos = 0x90 + xpos; 
	else if(ypos==2) xy_pos = 0x88 + xpos;
	else if(ypos==3) xy_pos = 0x98 + xpos;
    //д��ַ
    LCD_WriteCmd(xy_pos);
}
//��ʾ�ַ���
void LCD_ShowString(uint8_t x,uint8_t y,uint8_t * str)
{
    LCD_WriteCmd(0x30);     //8λ����ģʽ
    LCD_SetPosition(x,y);
    
    for(;*str!='\0';str++)
	{
		LCD_WriteData(*str);
        delay_ms(2);
	}
}
//���GDRAM
/*������*/
void LCD_ClearGDRAM()
{
    uint8_t x,y;
    LCD_WriteCmd(0x34);     //����ָ�
    
    for(y=0;y<32;y++) 
    {
        for(x=0;x<16;x++) 
        {            
//            sprintf(st,"x:%d y:%d",x,y);
//			LCD_ShowString(0,2,(unsigned char *)st);
            LCD_WriteCmd(y+0x80);        //�е�ַ 
            LCD_WriteCmd(x+0x80);     	 //�е�ַ 				
            LCD_WriteData(0x00); 
            LCD_WriteData(0x00);  
          
        }   
    }
    
    LCD_WriteCmd(0x36); 
}
//��LCD������
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
//��ȡDB�˿ڵ�ֵ
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
//������ ����������������
void LCD_DrawPoint(uint8_t x,uint8_t y,uint8_t displayOrNot)
{
    unsigned char zuobiao_x0,zuobiao_y0,zuobiao_y1;
    unsigned int zuobiao_x1,dat;
    
    zuobiao_y0 = y/32;  //������0��������1
    zuobiao_y1 = y%32;  //�е�ַ 
    zuobiao_x0 = x/16;  //�е�ַ�ķ���
    zuobiao_x1 = 0x8000>>(x%16);
    
    LCD_WriteCmd(0x34); //ִ����չָ��
    LCD_WriteCmd(0x36); //����ͼ��ʾ
    LCD_WriteCmd(0x80 + zuobiao_y1);     //�е�ַ 
    LCD_WriteCmd(0x80 + zuobiao_y0*8 + zuobiao_x0);     //�е�ַ 
    

    //����ǰ��ַ����
    LCD_ReadOneData();//�ٶ�һ��
    dat = (unsigned int)LCD_ReadOneData()<<8;//����8λ
    dat |=  LCD_ReadOneData();//����8λ
    if(displayOrNot==0) zuobiao_x1 = (~zuobiao_x1)&dat;
    else zuobiao_x1 |= dat;
    
    LCD_WriteCmd(0x80 + zuobiao_y1);     //�е�ַ 
    LCD_WriteCmd(0x80 + zuobiao_y0*8 + zuobiao_x0);     //�е�ַ 
    
    LCD_WriteData((unsigned char)(zuobiao_x1>>8)); 
    LCD_WriteData((unsigned char)zuobiao_x1);
    
    
}
//���� x:0~127 y:0~63 ����ֵ:��ǰ���ֵ
uint8_t LCD_ReadPoint(uint8_t x,uint8_t y)
{
    unsigned char zuobiao_x0,zuobiao_y0,zuobiao_y1;
    unsigned int zuobiao_x1,dat;
    
    zuobiao_y0 = y/32;  //������0��������1
    zuobiao_y1 = y%32;  //�е�ַ 
    zuobiao_x0 = x/16;  //�е�ַ�ķ���
    zuobiao_x1 = 0x8000>>(x%16);
    
//    LCD12864_COM_Write(0x36); //ִ����չָ�����ͼ��ʾ
    LCD_WriteCmd(0x80 + zuobiao_y1);     //�е�ַ 
    LCD_WriteCmd(0x80 + zuobiao_y0*8 + zuobiao_x0);     //�е�ַ 
    
    //����ǰ��ַ����
    LCD_ReadOneData();//�ٶ�һ��
    dat = (unsigned int)LCD_ReadOneData()<<8;//����8λ
    dat |=  LCD_ReadOneData();//����8λ
    
    if((dat&zuobiao_x1) == 0) return 0;  
    
    else return 1;
}
//��ʼ��
void LCD_Init(void)
{
    LCD_GPIO_OutMode_Init();            //���Ÿ�Ϊ���
    RESET_HIGH;              
    delay_init();       //��ʼ����ʱ����
               
    PSB_HIGH;                   //���ڷ�ʽ
    
    
    
    delay_ms(2); 
    LCD_WriteCmd(0x30);         //ѡ�����ָ����ͣ�8λ����ģʽ��
    
    delay_ms(2); 
    LCD_WriteCmd(0x0c);         //����ʾ,���α�,������.
    
    delay_ms(2); 
    LCD_WriteCmd(0x01);         //�����ʾ������ DDRAM �ĵ�ַ������ AC ��Ϊ 00H.
    
    delay_ms(2); 
    LCD_WriteCmd(0x06);         //���ã��ⲿ��д���ݺ�,��ַ������ AC ���Զ��� 1��
    
    delay_ms(2); 
    LCD_WriteCmd(0x80);         ////�� DDRAM ��ַ������ AC ��Ϊ 0.
    
    delay_ms(2); 
      
}
//����
void LCD_Cls()
{
   LCD_WriteCmd(0x01);
}
