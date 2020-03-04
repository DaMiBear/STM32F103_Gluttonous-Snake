#include "AD_DMA.h"
#include "Snake.h"
/*�����������ADC_ConvertedValue[4],�ֱ��AD1ͨ��5��3ת��������*/
__IO uint16_t ADC_ConvertedValue[4];


//unsigned char AD4_a,AD4_b,AD4_c;
/*�趨ȫ�ֱ������ڷ�������  */
int AD_DMA_Result1=0;
int AD_DMA_Result2 = 0;

//int AD_DMA_Result3_Arr[50]={0};   //�����������λ��
/*ð���㷨*/
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
/*
* ��������ADC1_GPIO_Config
* ���� ��ʹ��ADC1��DMA1��ʱ��,���ö˿�Ϊģ������
* ���� : ��
* ��� ����
* ���� ���ڲ�����
*/
void ADC1_GPIO_Config(void)
{
     GPIO_InitTypeDef  GPIO_InitStructure;
	/* Enable DMA clock */
     RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
     /* Enable ADC1 and GPIOC & GPIOA clock */
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA ,ENABLE);
     //X Yƫ������������
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 |GPIO_Pin_3;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
     
     //Z���򰴼�����
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;      //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/* ��������ADC1_Mode_Config
* ���� ������ADC1�Ĺ���ģʽΪDMAģʽ
* ���� : ��
* ��� ����
* ���� ���ڲ�����
*/
void ADC1_Mode_Config(void)
{
      DMA_InitTypeDef  DMA_InitStructure;
      ADC_InitTypeDef  ADC_InitStructure;
      /* DMA channel1 configuration */
      DMA_DeInit(DMA1_Channel1);
      /*����DMA�������ַ,��Ϊ���ת������ļĴ���*/
      DMA_InitStructure.DMA_PeripheralBaseAddr =ADC1_DR_Address;
      /*�����ڴ����ַ*/
      DMA_InitStructure.DMA_MemoryBaseAddr =(u32)&ADC_ConvertedValue;
      /*����AD������Ϊ���ݴ������Դ*/
      DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
      /*ָ��DMAͨ����DMA����Ĵ�С,����Ҫ���ټ����ڴ�ռ䣬��ʵ����x��ת��ͨ�������Կ���x��*/
      DMA_InitStructure.DMA_BufferSize = 2;
      /*�趨�Ĵ�����ַ�̶�*/
      DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
      /*�趨�ڴ��ַ�ݼӣ���ÿ��DMA���ǽ�������Ĵ����е�ֵ����2���ڴ�ռ���*/
      DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
      /*�趨�������ݿ��*/	
      DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
      /*�趨�ڴ�ĵĿ��*/
      DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
      /*�趨DMA������ѭ������ģʽ*/
      DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
      /*�趨DMAѡ����ͨ��������ȼ�*/
      DMA_InitStructure.DMA_Priority = DMA_Priority_High;
      DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
      DMA_Init(DMA1_Channel1, &DMA_InitStructure);
      /* Enable DMA channel1 */
       DMA_Cmd(DMA1_Channel1, ENABLE);
	
	// ADC_DeInit(ADC1);//��ʼ��ADC1
	/*����ADC�����ڶ���ģʽ*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
     /*�涨ADת��������ɨ��ģʽ�����Զ��ͨ������*/	
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ;
	/*�趨ADת��������ģʽ*/
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	/*��ʹ���ⲿ�ٷ�ת��*/
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	/*�ɼ��������ڼĴ��������Ҷ���ķ�ʽ���*/
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	/*�趨Ҫת����ADͨ����Ŀ*/
	ADC_InitStructure.ADC_NbrOfChannel = 2;
	ADC_Init(ADC1, &ADC_InitStructure);
	/*����ADCʱ�ӣ�ΪPCLK2��8��Ƶ����9MHz*/
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
     /*����ADC1��ͨ����ת���Ⱥ�˳���Լ�����ʱ��ΪΪ239.5���������� */
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 2, ADC_SampleTime_239Cycles5);
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 3, ADC_SampleTime_239Cycles5);
	//ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 4, ADC_SampleTime_13Cycles5);
	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	/*��λУ׼�Ĵ��� */
	ADC_ResetCalibration(ADC1);
	/*�ȴ�У׼�Ĵ�����λ��� */
	while(ADC_GetResetCalibrationStatus(ADC1));
	/* ADCУ׼ */
	ADC_StartCalibration(ADC1);
	/* �ȴ�У׼���*/
	while(ADC_GetCalibrationStatus(ADC1));
	/* ����û�в����ⲿ����������ʹ���������ADCת�� */
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

	
enum objectiveDirections read_ADC_DMA()
{
  unsigned char i;
     //���ն�ȡֵ ����3.3VΪ3300
  unsigned int result1 = 0;     //
  unsigned int result2 = 0;   //
  enum objectiveDirections Direction = NONE;     //����
  for(i=0;i<4;i++)
  {
     result1 +=ADC_ConvertedValue[0];
     result2 +=ADC_ConvertedValue[1];
		
  }
    result1 = result1 >>2;            //ȡ4�β�����ƽ��ֵ
    result2 = result2 >>2;
		
  /***************************
  *       result1 ���ݴ��� 
  *       
  ****************************/
     /*����ƫ���������ط���*/
     //Xƫ����
    if(result1 > 2300 )
        Direction = EAST;
    else if(result1 < 1860)
        Direction = WEST;
  /***************************
  *       result2 ���ݴ���     
  ****************************/
     //Yƫ����
    if(result2 > 2300)
        Direction = SOUTH;
    else if(result2 < 1860)
        Direction = NORTH;
   
    return Direction;       //�з���ʱ���ط���û�з���ʱ����NONE 
    
}

