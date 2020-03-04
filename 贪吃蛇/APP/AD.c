#include "AD.h"
unsigned char AD_a,AD_b,AD_c,AD_d;
unsigned char AD2_a,AD2_b,AD2_c,AD2_d;
int  AD_Result=0;
int  AD2_Result=0;
float  VRatio = 13;   //��ѹ��
static void BubbleSort(int *arr, int n)
{
     int i=0,j=0;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
        {
            //���ǰ������Ⱥ���󣬽��н���
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
  //ADC��������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;             //����Ϊģ������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         
  GPIO_InitStructure.GPIO_Pin = AD1;
  GPIO_Init(AD_GPIO,&GPIO_InitStructure);
  
  ADC_DeInit(ADC1);                                       //������ADCx��ȫ���Ĵ�������ΪĬ��ֵ
  ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;         //ADC�����ڶ���ģʽ
  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;     //�Ҷ���
  ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;        //����ģʽ
  ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//���崥����ʽ���˴�Ϊ�������
  ADC_InitStruct.ADC_NbrOfChannel = 1;                    //����ADC���й���ת����ADCͨ����Ŀ
  ADC_InitStruct.ADC_ScanConvMode = DISABLE;              //��ͨ��
  ADC_Init(ADC1,&ADC_InitStruct);
  
  
  //********************************************
  //����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
  //ʹ��ADCx   ģ��ͨ��y  ������� ����ʱ��
  //********************************************
  ADC_RegularChannelConfig(ADC1,AD_Channel,1,ADC_SampleTime_239Cycles5);

   ADC_Cmd(ADC1,ENABLE);                                 //ADCʹ��
   ADC_ResetCalibration (ADC1);                         //����ָ����ADC1��У׼�Ĵ���
   while(ADC_GetResetCalibrationStatus(ADC1));          //��ȡADC1����У׼�Ĵ�����״̬��ֱ��У׼�Ĵ����������
   ADC_StartCalibration(ADC1);                          //��ʼָ��ADC��У׼״̬
   while(ADC_GetCalibrationStatus(ADC1));               //��ȡָ��ADC��У׼����ֱ��У׼���
   ADC_SoftwareStartConvCmd(ADC1,ENABLE);                //ʹ��ADCx�����ת����������
}
void ADC2_Init()
{
  ADC_InitTypeDef ADC_InitStruct;
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);
  //ADC��������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;             //����Ϊģ������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         
  GPIO_InitStructure.GPIO_Pin = AD2;
  GPIO_Init(AD_GPIO,&GPIO_InitStructure);
  
  ADC_DeInit(ADC2);                                       //������ADCx��ȫ���Ĵ�������ΪĬ��ֵ
  ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;         //ADC�����ڶ���ģʽ
  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;     //�Ҷ���
  ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;        //����ģʽ
  ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//���崥����ʽ���˴�Ϊ�������
  ADC_InitStruct.ADC_NbrOfChannel = 1;                    //����ADC���й���ת����ADCͨ����Ŀ
  ADC_InitStruct.ADC_ScanConvMode = DISABLE;              //��ͨ��
  ADC_Init(ADC2,&ADC_InitStruct);
  
  
  //********************************************
  //����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
  //ʹ��ADCx   ģ��ͨ��y  ������� ����ʱ��
  //********************************************
  ADC_RegularChannelConfig(ADC2,AD2_Channel,1,ADC_SampleTime_239Cycles5);

   ADC_Cmd(ADC2,ENABLE);                                 //ADCʹ��
   ADC_ResetCalibration (ADC2);                         //����ָ����ADC1��У׼�Ĵ���
   while(ADC_GetResetCalibrationStatus(ADC2));          //��ȡADC1����У׼�Ĵ�����״̬��ֱ��У׼�Ĵ����������
   ADC_StartCalibration(ADC2);                          //��ʼָ��ADC��У׼״̬
   while(ADC_GetCalibrationStatus(ADC2));               //��ȡָ��ADC��У׼����ֱ��У׼���
   ADC_SoftwareStartConvCmd(ADC2,ENABLE);                //ʹ��ADCx�����ת����������
}

//��ȡ�ɼ�����ADC����
void read_ADC()
{
       static int count = 0 ;      //������һ��ֵ�� ��ƽ��ֵ,���      
       uchar i;
       int result=0;
       int result2=0;
       unsigned short id,id2;
       for(i=0;i<8;i++)
       {
          ADC_SoftwareStartConvCmd(ADC1,ENABLE);             //����ADCת��
          ADC_SoftwareStartConvCmd(ADC2,ENABLE);
         do
         {
           id = ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC);        //��ȡת����־
           id2 = ADC_GetFlagStatus(ADC2,ADC_FLAG_EOC);
         }while((!id)&&(!id2));
         
         result +=ADC_GetConversionValue(ADC1);
         result2 +=ADC_GetConversionValue(ADC2);
       }
         result = result >>3;                              //ȡ8�β�����ƽ��ֵ
         result2 = result2 >>3;                              //ȡ8�β�����ƽ��ֵ
         result = (unsigned int)(((unsigned long)result)*3300>>12);//�Ѳɼ�������ֵת���ɵ�ѹ����
         result2 = (unsigned int)(((unsigned long)result2)*3300>>12);//�Ѳɼ�������ֵת���ɵ�ѹ����
       
       //AD1���ݴ���
         AD_Result =  result*VRatio; //���ڷ��� ת����LOAD�˵�ѹֵ
         result = result*VRatio;     //������ʾ
         AD_a = result/10000;                //ab.cd
         AD_b = (result/1000)%10;
         AD_c = (result/100)%10;
         AD_d = (result/10)%10;
       
       //AD2���ݴ���
         result2 = (((float)(result2 - 2528))/95)*1000;    //ת���ɵ���ֵ
          //�������ڸ�����ʾ�ͷ���
          AD2_Result = result2;
          AD2_a = result2/1000;                //a.bcd
          AD2_b = (result2-AD2_a*1000)/100;
          AD2_c = (result2-AD2_a*1000-AD2_b*100)/10;
          AD2_d = result2%10;
         

}
