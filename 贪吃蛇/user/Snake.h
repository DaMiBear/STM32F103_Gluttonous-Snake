#ifndef _SNAKE_H
#define _SNAKE_H
enum objectiveDirections
{
	NORTH = 0,SOUTH,WEST,EAST,NONE		//上(北)，下(南)，左(西)，右(东) 无(没有方向)
};
typedef struct Node
{
    int x;
    int y;
    struct Node *next;
}Node;

void snakeCreate(void);     //生成蛇
void wallCreate(void);      //生成墙壁
void gameDescription(void); //游戏说明
void snakeMove(void);       //蛇的移动
void gameControl(void);     //游戏控制
void pauseGame(void);       //暂停游戏
void exitGame(void);        //退出游戏
void isBitSelf(void);       //吃到自己
void isBitWall(void);       //吃到墙壁
void spawnFood(void);       //生成食物
#endif
 
