#include "snack_def.h"
#include "snack_fc.h"

int main(void)
{
    drawMap();
	while (true)
	{
		keyDown();
		if (!snakeStatus())
			break;
		createFood();
		Sleep(snake.speed);
	}
 
	gotoxy(MAPWIDTH / 2, MAPHEIGHT / 2);
	printf("Game Over!\n");
	gotoxy(MAPWIDTH / 2, MAPHEIGHT / 2 + 1);
	printf("Your source is:%d\n", sorce);
	Sleep(5000);
    
	return 0;
}