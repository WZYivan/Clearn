#ifndef SNACK_DEF_H_
#define SNACK_DEF_H_ 1

#include <stdbool.h>

#define SNAKESIZE 100//蛇的身体最大节数
#define MAPWIDTH 118 //宽度
#define MAPHEIGHT 29//高度

//食物的坐标
struct {
	int x;
	int y;
}food;
 
//蛇的相关属性
struct {
	int speed;//蛇移动的速度
	int len;//蛇的长度
	int x[SNAKESIZE];//组成蛇身的每一个小方块中x的坐标
	int y[SNAKESIZE];//组成蛇身的每一个小方块中y的坐标
}snake;

int key = 72;//表示蛇移动的方向，72为按下“↑”所代表的数字
int changeFlag = 0;//用来判断蛇是否吃掉了食物，这一步很重要，涉及到是否会有蛇身移动的效果以及蛇身增长的效果
int sorce = 0;//记录玩家的得分

//从控制台移动光标
void gotoxy(int x, int y);
//绘制游戏边框
void drawMap(void);
//随机生成食物
void createFood(void);
//按键操作
void keyDown(void);
//蛇的状态
bool snakeStatus(void);
#endif