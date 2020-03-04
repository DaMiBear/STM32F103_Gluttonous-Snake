#include "Snake.h"
#include "LCD12864.h"
#include "stdlib.h"
#include "stdio.h"
#include "AD_DMA.h"
#include "delay.h"
static Node *head,*food = NULL,*index;  //��ͷ,ʳ��,�α�      û�з����ַʱ ����ַΪNULL
static  int score = 0,  //�÷�
        add = 10,    //�ӷ�
        deathType, //��������
        speed = 1; //ǰ���ٶ�
enum objectiveDirections snakeDirection = WEST; //�����ߵķ���

void snakeCreate()     //������
{
    Node * tail;    //������β
    int i;
    tail = (Node *)malloc(sizeof(Node));    //Ϊtail�����ڴ�ռ�
    tail->x = 2;    //�趨��β�ĳ�ʼ����
    tail->y = 61;
    tail->next = NULL;  //�ж���β������: next ΪNULL
    //ÿ��ѭ�������µĵ�ַ��Žṹ����Ϣ���µĽṹ���nextָ��֮ǰ�Ľṹ���ַ
    for(i = 1 ; i <= 4 ; i++)
    {
        head = (Node*)malloc(sizeof(Node));     //mallocÿ�λط��ز�ͬ�ĵ�ַ�������µ���ͷ
        head->next = tail;      //�µ���ͷָ���Ѿ����ڵĹؽ�
        head->x = 2;
        head->y = 61 - i;
        tail = head;        //tail����������濪�ٵĹؽ�
    }
    while(tail != NULL)     //��ͷ��β �������
    {
        LCD_DrawPoint(tail->x,tail->y,1);
        tail = tail->next;
    }
    
}
void wallCreate()     //����ǽ��
{
    int i;
    //��ӡ���±߿�
    for(i = 0 ; i <= 70 ; i++)
    {
        LCD_DrawPoint(i,0,1);
        LCD_DrawPoint(i,63,1);
    }
    //��ӡ���ұ߿�
    for(i = 1 ; i <= 62 ; i++)
    {
        LCD_DrawPoint(0,i,1);
        LCD_DrawPoint(70,i,1);
    }
    //��ʾ����
    LCD_ShowString(5,0,(unsigned char *)"Score");   //4��8��  ������ʾ8�����Ļ���16��Ӣ����ĸ
    //��ʾ��ǰ�ߵ��ٶ�
    LCD_ShowString(5,2,(unsigned char *)"Speed");
}
void spawnFood()       //����ʳ��
{
    Node *food_1;
    if(food != NULL)    //����ʧ����������
    {
        return;
    }
    food_1 = (Node *)malloc(sizeof(Node));    //Ϊ"׼ʳ��"�����ڴ�ռ�
    food_1->x = rand()%69 + 1;      //�������ʳ���ұ���ʧ�󳬳���Χ x(1--69)
    food_1->y = rand()%62 + 1;      //y(1--62)
    //����ʳ��������ߵ�����
    index = head;
    while(index != NULL)
    {
        if((food_1->x == index->x) && (food_1->y == index->y))  //���ʳ��λ���������غϣ�����������ʳ��
        {
            free(food_1);       //�ͷ�֮ǰ�غϵ�ʳ���ڴ�
            spawnFood();        //��������ʳ��
            break;              //��Ȼ���൱�ڵݹ飬�����GG
        }
        index = index->next;   //��ʼ��һ��������ж�
    }
    food = food_1;
    LCD_DrawPoint(food->x,food->y,1);       //����ʳ��  
    
}
void gameDescription() //��Ϸ˵��
{
    LCD_ShowString(0,0,(unsigned char *)"����ҡ����������"); 
    LCD_ShowString(0,1,(unsigned char*)"���ƶ�");
    LCD_ShowString(0,2,(unsigned char*)"��ֱ������ͣ");
}
void snakeMove()      //�ߵ��ƶ�
{
    Node *nextHead = (Node *)malloc(sizeof(Node));  //�ƶ���ͷ��λ��
    isBitWall();    //����Ƿ�ײǽ
    
    //���ݷ������ƶ�
    if(snakeDirection == NORTH)
    {
        nextHead->x = head->x;
        nextHead->y = head->y - 1;
    }
    else if(snakeDirection == SOUTH)
    {
        nextHead->x = head->x;
        nextHead->y = head->y + 1;
    }
    else if(snakeDirection == WEST)
    {
        nextHead->x = head->x - 1;
        nextHead->y = head->y;
    }
    else if(snakeDirection == EAST)
    {
        nextHead->x = head->x + 1;
        nextHead->y = head->y;
    }
    nextHead->next = head;      //�µ�ͷָ��ɵ�ͷ
    head = nextHead;        //��ͷ"������˳"
    index = head;
    isBitSelf();        //����Ƿ�ҧ���Լ�
    //��û�гԵ�ʳ��,����Ե�ʳ�������һ��
    if((nextHead->x == food->x) && (nextHead->y == food->y))
    {
        while(index != NULL)
        {
            LCD_DrawPoint(index->x,index->y,1);     //���л���
            index = index->next;
        }
        score +=add;
        free(food);
        food = NULL;    //��ʳ��ָ�븳��
        spawnFood();    //����ʳ��
    }
    else    //�������ǰ�� ��ͷ�����ӹؽ�����β��
    {
        while(index->next->next != NULL)        //����β��ǰһ���ؽ� ����ط����µ�β�Ͳ�û�д�ӡ�����������õ�֮ǰ��ӡ��
        {
            LCD_DrawPoint(index->x,index->y,1);
            index = index->next;
        }
        LCD_DrawPoint(index->next->x,index->next->y,0);     //����β��
        free(index->next);
        index->next = NULL;
    }
    
}
void gameControl()     //��Ϸ����
{
    char scoAndSpeStr[4] = "    ";       //�����ַ���
    snakeDirection = NORTH;     //����һ����ʼ����
    while(1)
    {
        //��ʾ����
        sprintf(scoAndSpeStr,"%d",score);
        LCD_ShowString(5,1,(unsigned char *)scoAndSpeStr);
        //��ʾ�ٶ�
        sprintf(scoAndSpeStr,"%d",speed);
        LCD_ShowString(5,3,(unsigned char *)scoAndSpeStr);
        //�������
        if((read_ADC_DMA() == NORTH) && (snakeDirection != SOUTH))  //��ֹ�߻�ͷҧ���Լ�
        {
            snakeDirection = NORTH;
        }
        else if((read_ADC_DMA() == SOUTH) && (snakeDirection != NORTH))
        {
            snakeDirection = SOUTH;
        }
        else if((read_ADC_DMA() == WEST) && (snakeDirection != EAST))
        {
            snakeDirection = WEST;
        }
        else if((read_ADC_DMA() == EAST) && (snakeDirection != WEST))
        {
            snakeDirection = EAST;
        }
        //��ͣ����
        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0)    //ҡ��z����ʱ�񱻰���
        {
            delay_ms(20);
            if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0)
            {
                while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0);
                pauseGame();
            }
            
        }
        //�ٶȺͷ�������
        if(score >= 0 && score < 5)
        {
            add = 1;
            speed = 5;
        }
        else if(score >=5 && score <15)
        {
            add = 2;
            speed = 4;
        }
        else if(score >=15 && score <30)
        {
            add = 4;
            speed = 3;
        }
        else if(score >=30 && score < 60)
        {
            add = 8;
            speed = 2;
        }
        else if(score >= 60)
        {
            add = 16;
            speed = 1;
        }
        
        delay_ms(speed*200);
        snakeMove();
    }
}
void pauseGame()       //��ͣ��Ϸ
{
    while(1)
    {
        delay_ms(1000);
        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0)    //ҡ��z����ʱ�񱻰���
        {
            break;
        }
    }
}
void isBitSelf()       //�Ե��Լ�
{
    Node *self = head->next;    //��ͷ������ĹؽڶԱ�
    while(self != NULL)
    {
        if((self->x == head->x) && (self->y == head->y))
        {
            deathType = 2;
            exitGame();
        }
        self = self->next;
    }
}
void isBitWall()       //�Ե�ǽ��
{
    if(head->x == 0 || head->x == 70 || head->y ==0 || head->y == 63)
    {
        deathType = 1;
        exitGame();
    }
}
void exitGame()         //�˳���Ϸ
{
    char str[5];
    LCD_Cls();      //����
    switch(deathType){
        case 1: LCD_ShowString(0,0,(unsigned char *)"���Դ�ײǽ��GG");break;
        case 2: LCD_ShowString(0,0,(unsigned char *)"������Լ�GG");break;
        
    }
    sprintf(str,"Score:%d",score);       //ת�ַ������
    LCD_ShowString(0,1,(unsigned char *)str);
    while(1);       //��������
}

