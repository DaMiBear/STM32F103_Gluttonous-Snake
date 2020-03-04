#include "Key_Scan.h"
#include "OLED.h"
void Key_Scan_Init()
{
	//选中引脚为推挽输出
	GPIO_InitTypeDef GPIO_InitStructure;
     //时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);
     
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10|GPIO_Pin_9;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			
	GPIO_Init(GPIOA,&GPIO_InitStructure);		

	//选中引脚为浮空输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;			
	GPIO_Init(GPIOC,&GPIO_InitStructure);		
			
	
}

char num1[10]={0},num2[10]={0};//定义两个数组，num1表示电压，num2表示电流
char num=0;				//中间数
char num_n=0;				//数组的下标
char show_x=0;				//用于按键后右移显示数字
unsigned char a=0;			//用于区别输入的第一个数和第二个数 a=0是输入第一个数，a=1是输入第二个数
float  num1_result=0,num2_result=0;//num1_result->，num2_result->

void Key_Dealy()
{
     int n,t;
     for(t=0;t<100;t++)
     for(n=0;n<2900;n++);
          
}
void Key_Scan()
{
	/**********************************************************
                              第一行
     **********************************************************/
          X1_H;
		X2_L;X3_L;X4_L;
     /***********************************************************/
      if(ReadY1State)
      {
           Key_Dealy();
		if(ReadY1State)		//111111111111111111111111111111
		{  
			while(ReadY1State);
			num = 1;	
			if(a==0)
			{	
				num1[num_n]=num;//对数组当前num_n对应的下标开始赋值
				OLED_ShowNum(16+show_x*8,0,num,1,16);
				num_n++;		//下标+1
				show_x++;
			}
			if(a==1)	//如果表明计算键按下a==1开始对第二个数赋值
			{
				num2[num_n]=num;
				OLED_ShowNum(16+show_x*8,2,num,1,16);
				num_n++;
				show_x++;
			}
		}
     }
      /***********************************************************/
      if(ReadY2State)
      {
           Key_Dealy();
		if(ReadY2State)   //22222222222222222222222222222222
		{	 
               while(ReadY2State);
			num = 2;
			if(a==0)
			{
				num1[num_n]=num;//对数组当前num_n对应的下标开始赋值
				OLED_ShowNum(16+show_x*8,0,num,1,16);
				num_n++;		//下标+1
				show_x++;
			}	
			if(a==1)	//如果表明计算键按下a==1开始对第二个数赋值
			{
				num2[num_n]=num;
				OLED_ShowNum(16+show_x*8,2,num,1,16);
				num_n++;
				show_x++;
			}
		}
     }
      /***********************************************************/
      if(ReadY3State)
      {
           Key_Dealy();
		if(ReadY3State)   //33333333333333333333333333333333
		{	
               while(ReadY3State);
			num = 3;
			if(a==0)
			{
				num1[num_n]=num;//对数组当前num_n对应的下标开始赋值
				OLED_ShowNum(16+show_x*8,0,num,1,16);
				num_n++;		//下标+1
				show_x++;
			}
			if(a==1)	//如果表明计算键按下a==1开始对第二个数赋值
			{
				num2[num_n]=num;
				OLED_ShowNum(16+show_x*8,2,num,1,16);
				num_n++;
				show_x++;
			}
			
		}
     }
      /***********************************************************/
      if(ReadY4State)
      {
           Key_Dealy();
		if(ReadY4State) 	//(1行,4列)表示确定输入输出电压
          {		
               while(ReadY4State);
              if(num1[3]==0)                //如果输入的是整数
              if(num1[1]==0&&num_n==1)	//如果第一个数是一位整数
               {
                    num1[1]=num1[0];//把原来十位的数 赋值给个位
                    num1[0]=0;			//赋值完成后把十位置零
               }
			num_n=0;				//数组下标清零
			show_x=0;
			a=1;					//令a=1 以后输入的都是对第二个数赋值
            
        	
		}
     }
      /**********************************************************
                         第二行
     **********************************************************/
		X2_H;
		X1_L;X3_L;X4_L;
     if(ReadY1State)
     {
          Key_Dealy();
		if(ReadY1State)		//444444444444444444444444
		{    
               while(ReadY1State);
			num = 4;
			if(a==0)
			{
				num1[num_n]=num;//对数组当前num_n对应的下标开始赋值
				OLED_ShowNum(16+show_x*8,0,num,1,16);
				num_n++;		//下标+1
				show_x++;
			}
			if(a==1)	//如果表明计算键按下a==1开始对第二个数赋值
			{
				num2[num_n]=num;
				OLED_ShowNum(16+show_x*8,2,num,1,16);
				num_n++;
				show_x++;
			}
		}
     }
     /***********************************************************/
     if(ReadY2State)
     {
          Key_Dealy();
		if(ReadY2State)   //555555555555555555555555
		{		
               while(ReadY2State);
			num = 5;
			if(a==0)
			{
				num1[num_n]=num;//对数组当前num_n对应的下标开始赋值
				OLED_ShowNum(16+show_x*8,0,num,1,16);
				num_n++;		//下标+1
				show_x++;
			}
			if(a==1)	//如果表明计算键按下a==1开始对第二个数赋值
			{
				num2[num_n]=num;
				OLED_ShowNum(16+show_x*8,2,num,1,16);
				num_n++;
				show_x++;
			}
			
		}
     }
     /***********************************************************/
     if(ReadY3State) 
     {
          Key_Dealy();
		if(ReadY3State)   //66666666666666666666666
		{	  
               while(ReadY3State);
			num = 6;			
			if(a==0)
			{
				num1[num_n]=num;//对数组当前num_n对应的下标开始赋值
				OLED_ShowNum(16+show_x*8,0,num,1,16);
				num_n++;		//下标+1
				show_x++;
			}
			if(a==1)	//如果表明计算键按下a==1开始对第二个数赋值
			{
				num2[num_n]=num;
				OLED_ShowNum(16+show_x*8,2,num,1,16);
				num_n++;
				show_x++;
			}
			
		}
     }
     /***********************************************************/
     if(ReadY4State) 
     {
          Key_Dealy();
		if(ReadY4State)   //  2行4列
		{	  	
               while(ReadY4State);
			num_n=0;				//数组下标清零
			show_x=0;
			a=1;					//令a=1 以后输入的都是对第二个数赋值
			
		}
     }
     /**********************************************************
                         第三行
     **********************************************************/
		X3_H;
		X1_L;X2_L;X4_L;
     if(ReadY1State)	
     {
         Key_Dealy();
		if(ReadY1State)		//77777777777777777777777
		{ 
               while(ReadY1State);
			num = 7;
			if(a==0)
			{
				num1[num_n]=num;//对数组当前num_n对应的下标开始赋值
				OLED_ShowNum(16+show_x*8,0,num,1,16);
				num_n++;		//下标+1
				show_x++;
			}
			if(a==1)	//如果表明计算键按下a==1开始对第二个数赋值
			{
				num2[num_n]=num;
				OLED_ShowNum(16+show_x*8,2,num,1,16);
				num_n++;
				show_x++;
			}
		}
     }
     /***********************************************************/
     if(ReadY2State)  
     {
          Key_Dealy();
		if(ReadY2State)   //888888888888888888888888
		{  
               while(ReadY2State);
			num = 8;
			if(a==0)
			{
				num1[num_n]=num;//对数组当前num_n对应的下标开始赋值
				OLED_ShowNum(16+show_x*8,0,num,1,16);
				num_n++;		//下标+1
				show_x++;
			}
			if(a==1)	//如果表明计算键按下a==1开始对第二个数赋值
			{
				num2[num_n]=num;
				OLED_ShowNum(16+show_x*8,2,num,1,16);
				num_n++;
				show_x++;
			}
		}
     }
     /***********************************************************/
     if(ReadY3State) 
     {
          Key_Dealy();
		if(ReadY3State)   //9999999999999999999999999
		{	  
               while(ReadY3State);               
			num = 9;
			if(a==0)
			{
				num1[num_n]=num;//对数组当前num_n对应的下标开始赋值
				OLED_ShowNum(16+show_x*8,0,num,1,16);
				num_n++;		//下标+1
				show_x++;
			}
			if(a==1)	//如果表明计算键按下a==1开始对第二个数赋值
			{
				num2[num_n]=num;
				OLED_ShowNum(16+show_x*8,2,num,1,16);
				num_n++;
				show_x++;
			}
		}
     }
     /***********************************************************/
     if(ReadY4State) 
     {
          Key_Dealy();
		if(ReadY4State)   //3行4列
		{  	
               while(ReadY4State);
			num_n=0;				//数组下标清零
			show_x=0;
			a=1;					//令a=1 以后输入的都是对第二个数赋值
			OLED_ShowString(0,0,(uchar *)"U");	
		}
     }
     /**********************************************************
                         第四行
     **********************************************************/
		X4_H;
		X1_L;X2_L;X3_L;
     if(ReadY1State)
     {
          Key_Dealy();
		if(ReadY1State)		//................
		{  
               while(ReadY1State);
			if(a==0)						//输入第一个数
			{
				num1[num_n]='.';
				OLED_ShowString(16+num_n*8,0,(uchar *)".");
				if(num1[1]=='.')		//整数部分只输入了一个数字
				{
					//数组往后移一位
					num1[2]=num1[1]; 
					num1[1]=num1[0];
					num1[0]=0;		//十位补0
					num_n++;//用于下标为3的数组接受小数部分
				}
			}
			if(a==1)					//输入第二个数
			{
				num2[num_n]='.';
				OLED_ShowString(16+num_n*8,2,(uchar *)".");
				if(num2[1]=='.')		//整数部分只输入了一个数字
				{
					//数组往后移一位
					num2[2]=num2[1];
					num2[1]=num2[0];
					num2[0]=0;		//十位补0
					num_n++;			
				}
			}
			num_n++;
			show_x++;
		}
     }
     /***********************************************************/
     if(ReadY2State) 
     {
          Key_Dealy();
		if(ReadY2State)   //0000000000000000000000
		{  	
               while(ReadY2State);
			num = 0;
			if(a==0)
			{
				num1[num_n]=num;//对数组当前num_n对应的下标开始赋值
				OLED_ShowNum(16+show_x*8,0,num,1,16);
				num_n++;		//下标+1
				show_x++;
			}
			if(a==1)	//如果表明计算键按下a==1开始对第二个数赋值
			{
				num2[num_n]=num;
				OLED_ShowNum(16+show_x*8,2,num,1,16);
				num_n++;
				show_x++;
			}
			
		}
     }
     /***********************************************************/
     if(ReadY3State) 
     {
          Key_Dealy();
		if(ReadY3State)  //DEL 
		{	 
               int i=0;
               while(ReadY3State);
			num_n=0;//数组下标初始化
			a=0;
			show_x=0;
			for(i=0;i<=3;i++)  //数组清零
			{
				num1[i]=0;
				num2[i]=0;
			}
			OLED_Clear();//清屏
               OLED_ShowString(0,4,(unsigned char *)"U = 00.00 V");
               OLED_ShowString(0,6,(unsigned char *)"I = 0.000 I");
			
		}
     }
     /***********************************************************/
     if(ReadY4State)
     {
          Key_Dealy();
		if(ReadY4State)   //=================
		{  	
               
               while(ReadY4State);
			
			if( num2[3]==0)		//如果输入的是整数
			{
				if(num2[1]==0&&num_n==1)	//如果第二个数是一位整数
				{
					num2[1]=num2[0];//把原来十位的数 赋值给个位
					num2[0]=0;			//赋值完成后把十位置零
				}
			}
               num_n=0;				//数组下标清零
			show_x=0;				//显示下标清零
			num1_result=(float)num1[0]*10+(float)num1[1]+(float)num1[3]*0.1;//把数组中的每个数合并为浮点数XX.X
			num2_result=(float)num2[0]*10+(float)num2[1]+(float)num2[3]*0.1;

               
               OLED_ShowString(56,0,(unsigned char *)"Done");
		
		}
     }

}

