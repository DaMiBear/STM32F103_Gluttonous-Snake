#ifndef _SNAKE_H
#define _SNAKE_H
enum objectiveDirections
{
	NORTH = 0,SOUTH,WEST,EAST,NONE		//��(��)����(��)����(��)����(��) ��(û�з���)
};
typedef struct Node
{
    int x;
    int y;
    struct Node *next;
}Node;

void snakeCreate(void);     //������
void wallCreate(void);      //����ǽ��
void gameDescription(void); //��Ϸ˵��
void snakeMove(void);       //�ߵ��ƶ�
void gameControl(void);     //��Ϸ����
void pauseGame(void);       //��ͣ��Ϸ
void exitGame(void);        //�˳���Ϸ
void isBitSelf(void);       //�Ե��Լ�
void isBitWall(void);       //�Ե�ǽ��
void spawnFood(void);       //����ʳ��
#endif
 
