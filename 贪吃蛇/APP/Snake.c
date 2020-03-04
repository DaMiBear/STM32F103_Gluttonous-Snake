#include "Snake.h"
#include "LCD12864.h"
#include "stdlib.h"
#include "stdio.h"
#include "AD_DMA.h"
#include "delay.h"
static Node *head,*food = NULL,*index;  //蛇头,食物,游标      没有分配地址时 初地址为NULL
static  int score = 0,  //得分
        add = 10,    //加分
        deathType, //死亡类型
        speed = 1; //前进速度
enum objectiveDirections snakeDirection = WEST; //蛇行走的方向

void snakeCreate()     //生成蛇
{
    Node * tail;    //创建蛇尾
    int i;
    tail = (Node *)malloc(sizeof(Node));    //为tail开辟内存空间
    tail->x = 2;    //设定蛇尾的初始坐标
    tail->y = 61;
    tail->next = NULL;  //判断蛇尾的依据: next 为NULL
    //每次循环开辟新的地址存放结构体信息，新的结构体的next指向之前的结构体地址
    for(i = 1 ; i <= 4 ; i++)
    {
        head = (Node*)malloc(sizeof(Node));     //malloc每次回返回不同的地址来开辟新的蛇头
        head->next = tail;      //新的蛇头指向已经存在的关节
        head->x = 2;
        head->y = 61 - i;
        tail = head;        //tail用来存放上面开辟的关节
    }
    while(tail != NULL)     //从头到尾 输出蛇身
    {
        LCD_DrawPoint(tail->x,tail->y,1);
        tail = tail->next;
    }
    
}
void wallCreate()     //生成墙壁
{
    int i;
    //打印上下边框
    for(i = 0 ; i <= 70 ; i++)
    {
        LCD_DrawPoint(i,0,1);
        LCD_DrawPoint(i,63,1);
    }
    //打印左右边框
    for(i = 1 ; i <= 62 ; i++)
    {
        LCD_DrawPoint(0,i,1);
        LCD_DrawPoint(70,i,1);
    }
    //显示分数
    LCD_ShowString(5,0,(unsigned char *)"Score");   //4行8列  可以显示8个中文或者16个英文字母
    //显示当前蛇的速度
    LCD_ShowString(5,2,(unsigned char *)"Speed");
}
void spawnFood()       //生成食物
{
    Node *food_1;
    if(food != NULL)    //避免失误重新生成
    {
        return;
    }
    food_1 = (Node *)malloc(sizeof(Node));    //为"准食物"开辟内存空间
    food_1->x = rand()%69 + 1;      //随机生成食物且避免失误超出范围 x(1--69)
    food_1->y = rand()%62 + 1;      //y(1--62)
    //避免食物出现在蛇的身上
    index = head;
    while(index != NULL)
    {
        if((food_1->x == index->x) && (food_1->y == index->y))  //如果食物位置与蛇身重合，就重新生成食物
        {
            free(food_1);       //释放之前重合的食物内存
            spawnFood();        //重新生成食物
            break;              //不然就相当于递归，下面会GG
        }
        index = index->next;   //开始下一节蛇身的判断
    }
    food = food_1;
    LCD_DrawPoint(food->x,food->y,1);       //生成食物  
    
}
void gameDescription() //游戏说明
{
    LCD_ShowString(0,0,(unsigned char *)"控制摇杆来控制蛇"); 
    LCD_ShowString(0,1,(unsigned char*)"的移动");
    LCD_ShowString(0,2,(unsigned char*)"垂直按下暂停");
}
void snakeMove()      //蛇的移动
{
    Node *nextHead = (Node *)malloc(sizeof(Node));  //移动后头的位置
    isBitWall();    //检查是否撞墙
    
    //根据方向来移动
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
    nextHead->next = head;      //新的头指向旧的头
    head = nextHead;        //把头"名正言顺"
    index = head;
    isBitSelf();        //检查是否咬到自己
    //有没有吃到食物,如果吃到食物就增加一节
    if((nextHead->x == food->x) && (nextHead->y == food->y))
    {
        while(index != NULL)
        {
            LCD_DrawPoint(index->x,index->y,1);     //进行绘制
            index = index->next;
        }
        score +=add;
        free(food);
        food = NULL;    //把食物指针赋空
        spawnFood();    //产生食物
    }
    else    //否则就向前进 在头部增加关节消除尾部
    {
        while(index->next->next != NULL)        //到蛇尾的前一个关节 这个地方蛇新的尾巴并没有打印出来，而是用的之前打印的
        {
            LCD_DrawPoint(index->x,index->y,1);
            index = index->next;
        }
        LCD_DrawPoint(index->next->x,index->next->y,0);     //消除尾部
        free(index->next);
        index->next = NULL;
    }
    
}
void gameControl()     //游戏控制
{
    char scoAndSpeStr[4] = "    ";       //储存字符串
    snakeDirection = NORTH;     //给蛇一个初始方向
    while(1)
    {
        //显示分数
        sprintf(scoAndSpeStr,"%d",score);
        LCD_ShowString(5,1,(unsigned char *)scoAndSpeStr);
        //显示速度
        sprintf(scoAndSpeStr,"%d",speed);
        LCD_ShowString(5,3,(unsigned char *)scoAndSpeStr);
        //方向控制
        if((read_ADC_DMA() == NORTH) && (snakeDirection != SOUTH))  //防止蛇回头咬到自己
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
        //暂停控制
        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0)    //摇杆z方向时否被按下
        {
            delay_ms(20);
            if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0)
            {
                while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0);
                pauseGame();
            }
            
        }
        //速度和分数控制
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
void pauseGame()       //暂停游戏
{
    while(1)
    {
        delay_ms(1000);
        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0)    //摇杆z方向时否被按下
        {
            break;
        }
    }
}
void isBitSelf()       //吃到自己
{
    Node *self = head->next;    //拿头部以外的关节对比
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
void isBitWall()       //吃到墙壁
{
    if(head->x == 0 || head->x == 70 || head->y ==0 || head->y == 63)
    {
        deathType = 1;
        exitGame();
    }
}
void exitGame()         //退出游戏
{
    char str[5];
    LCD_Cls();      //清屏
    switch(deathType){
        case 1: LCD_ShowString(0,0,(unsigned char *)"你脑袋撞墙了GG");break;
        case 2: LCD_ShowString(0,0,(unsigned char *)"你吃了自己GG");break;
        
    }
    sprintf(str,"Score:%d",score);       //转字符串输出
    LCD_ShowString(0,1,(unsigned char *)str);
    while(1);       //卡在这里
}

