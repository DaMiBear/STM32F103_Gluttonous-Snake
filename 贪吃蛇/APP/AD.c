#include "AD.h"
unsigned char AD_a,AD_b,AD_c,AD_d;
unsigned char AD2_a,AD2_b,AD2_c,AD2_d;
int  AD_Result=0;
int  AD2_Result=0;
float  VRatio = 13;   //分压比
static void BubbleSort(int *arr, int n)
{
     int i=0,j=0;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
        {
            //如果前面的数比后面大，进行交换
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
}

void ADC1_Init()
{
  ADC_InitTypeDef ADC_InitStruct;
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
  //ADC输入引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;             //配置为模拟输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         
  GPIO_InitStructure.GPIO_Pin = AD1;
  GPIO_Init(AD_GPIO,&GPIO_InitStructure);
  
  ADC_DeInit(ADC1);                                       //将外设ADCx的全部寄存器重设为默认值
  ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;         //ADC工作在独立模式
  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;     //右对齐
  ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;        //单次模式
  ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//定义触发方式，此处为软件触发
  ADC_InitStruct.ADC_NbrOfChannel = 1;                    //设置ADC进行规则转换的ADC通道数目
  ADC_InitStruct.ADC_ScanConvMode = DISABLE;              //单通道
  ADC_Init(ADC1,&ADC_InitStruct);
  
  
  //********************************************
  //设置指定ADC的规则组通道，设置他们的转换顺序和采样时间
  //使用ADCx   模拟通道y  采样序号 采样时间
  //********************************************
  ADC_RegularChannelConfig(ADC1,AD_Channel,1,ADC_SampleTime_239Cycles5);

   ADC_Cmd(ADC1,ENABLE);                                 //ADC使能
   ADC_ResetCalibration (ADC1);                         //重置指定的ADC1的校准寄存器
   while(ADC_GetResetCalibrationStatus(ADC1));          //获取ADC1重置校准寄存器的状态，直到校准寄存器重设完成
   ADC_StartCalibration(ADC1);                          //开始指定ADC的校准状态
   while(ADC_GetCalibrationStatus(ADC1));               //获取指定ADC的校准程序，直到校准完成
   ADC_SoftwareStartConvCmd(ADC1,ENABLE);                //使能ADCx的软件转换启动功能
}
void ADC2_Init()
{
  ADC_InitTypeDef ADC_InitStruct;
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);
  //ADC输入引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;             //配置为模拟输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         
  GPIO_InitStructure.GPIO_Pin = AD2;
  GPIO_Init(AD_GPIO,&GPIO_InitStructure);
  
  ADC_DeInit(ADC2);                                       //将外设ADCx的全部寄存器重设为默认值
  ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;         //ADC工作在独立模式
  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;     //右对齐
  ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;        //单次模式
  ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//定义触发方式，此处为软件触发
  ADC_InitStruct.ADC_NbrOfChannel = 1;                    //设置ADC进行规则转换的ADC通道数目
  ADC_InitStruct.ADC_ScanConvMode = DISABLE;              //单通道
  ADC_Init(ADC2,&ADC_InitStruct);
  
  
  //********************************************
  //设置指定ADC的规则组通道，设置他们的转换顺序和采样时间
  //使用ADCx   模拟通道y  采样序号 采样时间
  //********************************************
  ADC_RegularChannelConfig(ADC2,AD2_Channel,1,ADC_SampleTime_239Cycles5);

   ADC_Cmd(ADC2,ENABLE);                                 //ADC使能
   ADC_ResetCalibration (ADC2);                         //重置指定的ADC1的校准寄存器
   while(ADC_GetResetCalibrationStatus(ADC2));          //获取ADC1重置校准寄存器的状态，直到校准寄存器重设完成
   ADC_StartCalibration(ADC2);                          //开始指定ADC的校准状态
   while(ADC_GetCalibrationStatus(ADC2));               //获取指定ADC的校准程序，直到校准完成
   ADC_SoftwareStartConvCmd(ADC2,ENABLE);                //使能ADCx的软件转换启动功能
}

//读取采集到的ADC数据
void read_ADC()
{
       static int count = 0 ;      //计数到一定值后 求平均值,求和      
       uchar i;
       int result=0;
       int result2=0;
       unsigned short id,id2;
       for(i=0;i<8;i++)
       {
          ADC_SoftwareStartConvCmd(ADC1,ENABLE);             //启动ADC转换
          ADC_SoftwareStartConvCmd(ADC2,ENABLE);
         do
         {
           id = ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC);        //读取转换标志
           id2 = ADC_GetFlagStatus(ADC2,ADC_FLAG_EOC);
         }while((!id)&&(!id2));
         
         result +=ADC_GetConversionValue(ADC1);
         result2 +=ADC_GetConversionValue(ADC2);
       }
         result = result >>3;                              //取8次采样的平均值
         result2 = result2 >>3;                              //取8次采样的平均值
         result = (unsigned int)(((unsigned long)result)*3300>>12);//把采集到的数值转换成电压数据
         result2 = (unsigned int)(((unsigned long)result2)*3300>>12);//把采集到的数值转换成电压数据
       
       //AD1数据处理
         AD_Result =  result*VRatio; //用于反馈 转换成LOAD端电压值
         result = result*VRatio;     //用于显示
         AD_a = result/10000;                //ab.cd
         AD_b = (result/1000)%10;
         AD_c = (result/100)%10;
         AD_d = (result/10)%10;
       
       //AD2数据处理
         result2 = (((float)(result2 - 2528))/95)*1000;    //转换成电流值
          //以下用于更新显示和反馈
          AD2_Result = result2;
          AD2_a = result2/1000;                //a.bcd
          AD2_b = (result2-AD2_a*1000)/100;
          AD2_c = (result2-AD2_a*1000-AD2_b*100)/10;
          AD2_d = result2%10;
         

}
