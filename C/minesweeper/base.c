#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _X_ 0
#define _Y_ 0
#define GotoXY(x,y) CC.X=x,CC.Y=y,SetConsoleCursorPosition(hOut,CC)
#define DoAt(x,y,p) tmpCC=CC,GotoXY(x,y),p,CC=tmpCC,SetConsoleCursorPosition(hOut,CC)
#define SetColor(fc,bc) SetConsoleTextAttribute(hOut, fc|bc)
//#define WHITESKIN //注释掉这一行就是黑色，否则就是白色
#ifndef WHITESKIN
#define F_BLACK 0    //前景黑色
#define F_LBLACK FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE    //前景灰色
#define F_WHITE FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY    //前景白色
#define F_LRED FOREGROUND_RED|FOREGROUND_INTENSITY      //前景浅红
#define F_LBLUE FOREGROUND_BLUE|FOREGROUND_INTENSITY        //前景浅蓝
#define F_LGREEN FOREGROUND_GREEN|FOREGROUND_INTENSITY      //前景浅绿
#define F_LBLUEGREEN FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY      //前景浅蓝绿
#define F_LPURPLE FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY       //前景浅紫
#define F_LYELLOW FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY    //前景浅黄
#define B_BLACK 0    //背景黑色
#define CORORSET
#else
#define F_BLACK FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY     //前景白
#define F_LBLACK FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE    //前景灰色
#define F_WHITE 0    //前景黑色
#define F_LRED FOREGROUND_RED       //前景红
#define F_LBLUE FOREGROUND_BLUE //前景蓝
#define F_LGREEN FOREGROUND_GREEN       //前景绿
#define F_LBLUEGREEN FOREGROUND_BLUE|FOREGROUND_GREEN       //前景蓝绿
#define F_LPURPLE FOREGROUND_RED|FOREGROUND_BLUE        //前景紫
#define F_LYELLOW FOREGROUND_RED|FOREGROUND_GREEN    //前景黄
#define B_BLACK BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY    //背景白
#define CORORSET system("color f0")
#endif

//■□☆★●◎※①②③④⑤⑥⑦⑧⑨⑩┓┛━┗┏┫┣┻┳╋┃
#define UNDIG "■"
#define BLANK "□"
#define MINE "●"
#define MARKED "★"

COORD CC = { 0, 0 };
COORD tmpCC = { 0, 0 };
HANDLE hOut, hIn;
DWORD dwMode, nOER;
INPUT_RECORD inRecord;
SMALL_RECT rc;

struct rfMouse{
    int Button;     //1-left 2-right 3-mid
    COORD position;
} rfmouse;

int level[3][7] = {
    /*
    level[lv][0~1] w h
    level[lv][2] Number of Mine
    level[lv][3~4] RemnantMines (X,Y)
    level[lv][5~6] Restart    Back (X,Y)
    */
    { 8, 8, 10, 4, 12, 4, 14 },
    { 16, 16, 40, 4, 20, 4, 22 },
    { 30, 16, 99, 4, 20, 4, 22 },
};
int drc[8][2] = {
    { -1, 0 }, { 0, -1 }, { 1, 0 }, { 0, 1 },
    { -1, -1 }, { -1, 1 }, { 1, -1 }, { 1, 1 },
};
char *num[10] = {
    BLANK,
    "①", "②", "③", "④", "⑤", "⑥", "⑦", "⑧",
    MINE,
};
int numcolor[10] = {
    /*BLANK*/
    F_LBLACK,
    /*1~3*/
    F_LBLUEGREEN, F_LGREEN, F_LGREEN,
    /*4~6*/
    F_LYELLOW, F_LYELLOW, F_LYELLOW,
    /*7~8*/
    F_LPURPLE, F_LPURPLE,
    /*MINE*/
    F_LRED,
};
int point[30][16][2], rmines, numofundig, lv;
//point[x][y][0]
//0 覆盖状态
//1 打开状态
//2 标记状态
//point[x][y][1]
//0 周围无雷
//1~8 周围有1~8个雷
//9 自身为雷

int dig(int x, int y);
void mark(int x, int y);
void drawmap(int w, int h);
void initialization(void);
int midButtonPress(int x, int y);
void explode(void);
void mouse_(int delay, struct rfMouse *rfm);
void firstblood(void);

int main(void){
    int x, y;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    hIn = GetStdHandle(STD_INPUT_HANDLE);
    CONSOLE_CURSOR_INFO CCI = { 100, 1 };
    SetConsoleCursorInfo(hOut, &CCI);
    SetConsoleTitle("MineSweeping V1.0 By BlackKitty");
    CORORSET;
back:;
    lv = -1;
    system("mode con cols=34 lines=20");
    GetConsoleMode(hIn, &dwMode);
    dwMode |= ENABLE_MOUSE_INPUT;
    SetConsoleMode(hIn, dwMode);
    SetColor(F_WHITE, B_BLACK); DoAt(5, 2, printf("MineSweeper Version 1.0"));
    SetColor(F_LBLACK, B_BLACK); DoAt(17, 4, printf("By BlackKitty"));
    SetColor(F_LBLUEGREEN, B_BLACK); DoAt(11, 8, printf("- Beginner -"));
    SetColor(F_LYELLOW, B_BLACK); DoAt(9, 10, printf("- Intermediate -"));
    SetColor(F_LPURPLE, B_BLACK); DoAt(12, 12, printf("- Expert -"));
    SetColor(F_LBLACK, B_BLACK); DoAt(14, 17, printf("Control By Mouse"));
    while (lv < 0){
        mouse_(23, &rfmouse);
        if (rfmouse.Button == 1){
            if (rfmouse.position.Y == 8 && rfmouse.position.X > 12 && rfmouse.position.X < 21) lv = 0;
            else if (rfmouse.position.Y == 10 && rfmouse.position.X > 10 && rfmouse.position.X < 23) lv = 1;
            else if (rfmouse.position.Y == 12 && rfmouse.position.X > 13 && rfmouse.position.X < 20) lv = 2;
        }
    }
    Sleep(300);     //防止过慢单击点穿菜单
    switch (lv){
        case 0:system("mode con cols=24 lines=16"); break;
        case 1:system("mode con cols=40 lines=24"); break;
        case 2:system("mode con cols=68 lines=24"); break;
    }
    GetConsoleMode(hIn, &dwMode);
    dwMode |= ENABLE_MOUSE_INPUT;
    SetConsoleMode(hIn, dwMode);
restart:;
    initialization();
    while (1){
        if (numofundig == level[lv][2]){
            SetColor(F_LRED, B_BLACK); DoAt(level[lv][3], level[lv][4], printf("   - YOU WIN -     "));
            SetColor(F_LRED, B_BLACK);
            for (x = 0; x < level[lv][0]; x++)
                for (y = 0; y < level[lv][1]; (point[x][y][0] != 1 && (point[x][y][0] = 1, DoAt(2 * x + 4, y + 2, printf

                    (MARKED)))), y++);
            numofundig = -1;
        }
        mouse_(11, &rfmouse);
        if (rfmouse.Button == 1){
            if (rfmouse.position.Y == level[lv][6] && rfmouse.position.X >= level[lv][5] && rfmouse.position.X <= level[lv][5]

                + 6) goto restart;
            if (rfmouse.position.Y == level[lv][6] && rfmouse.position.X >= level[lv][5] + 12 && rfmouse.position.X <= level

                [lv][5] + 15) goto back;
            if (numofundig + 1 && dig(rfmouse.position.X / 2 - 2, rfmouse.position.Y - 2)) explode();
        }
        if (rfmouse.Button == 2) mark(rfmouse.position.X / 2 - 2, rfmouse.position.Y - 2);
        if (rfmouse.Button == 3) if (midButtonPress(rfmouse.position.X / 2 - 2, rfmouse.position.Y - 2)) explode();
    }
    _getch();
    return 0;
}

void mouse_(int delay, struct rfMouse *rfm){
    /*响应鼠标操作*/
    while (1){
        Sleep(delay);      //短暂延时
        ReadConsoleInput(hIn, &inRecord, 100, &nOER);
        GotoXY(inRecord.Event.MouseEvent.dwMousePosition.X + _X_, inRecord.Event.MouseEvent.dwMousePosition.Y + _Y_);   //光标


        rfm->position.X = inRecord.Event.MouseEvent.dwMousePosition.X + _X_;
        rfm->position.Y = inRecord.Event.MouseEvent.dwMousePosition.Y + _Y_;
        if (inRecord.EventType == MOUSE_EVENT)
            switch (inRecord.Event.MouseEvent.dwButtonState){
                case FROM_LEFT_1ST_BUTTON_PRESSED:rfm->Button = 1; return;    //左键按下
                case RIGHTMOST_BUTTON_PRESSED:rfm->Button = 2; return;    //右键按下
                case FROM_LEFT_2ND_BUTTON_PRESSED:rfm->Button = 3; return;    //左数第2个键(一般为中键)按下
                default:break;
        }
    }
}

int dig(int x, int y){
    int i;
    if (x >= 0 && x<level[lv][0] && y >= 0 && y<level[lv][1] && !point[x][y][0]){
        numofundig--;
        point[x][y][0] = 1;
        if (point[x][y][1] == 9) {
            if (numofundig + 1 == level[lv][0] * level[lv][1]){
                do{ initialization(); } while (point[x][y][1] == 9);
                numofundig--;
            }
            else {
                SetColor(numcolor[point[x][y][1]], B_BLACK); DoAt((x + 2) * 2, y + 2, printf(num[point[x][y][1]]));
                return 1;
            }
        }
        SetColor(numcolor[point[x][y][1]], B_BLACK); DoAt((x + 2) * 2, y + 2, printf(num[point[x][y][1]]));
        if (point[x][y][1] == 0)
            for (i = 0; i < 8; i++)
                dig(x + drc[i][0], y + drc[i][1]);
    }
    return 0;
}

void mark(int x, int y){
    if (x >= 0 && x < level[lv][0] && y >= 0 && y < level[lv][1]){
        if (!point[x][y][0]){
            SetColor(F_WHITE, B_BLACK); DoAt((x + 2) * 2, y + 2, printf(MARKED));
            point[x][y][0] = 2;
            DoAt(level[lv][3], level[lv][4], printf("RemnantMines: %d  ", --rmines));
        }
        else if (point[x][y][0] == 2){
            SetColor(F_LBLACK, B_BLACK); DoAt((x + 2) * 2, y + 2, printf(UNDIG));
            point[x][y][0] = 0;
            SetColor(F_WHITE, B_BLACK); DoAt(level[lv][3], level[lv][4], printf("RemnantMines: %d  ", ++rmines));
        }
    }
    return;
}

void drawmap(int w, int h){
    int ww, hh;
    for (printf("┏"), ww = 0; ww < w; printf("━"), ww++); printf("┓");
    for (hh = 1; hh <= h; printf("┃"), hh++)
        for (GotoXY(CC.X, CC.Y + 1), printf("┃"), ww = 0; ww < w; printf(UNDIG), ww++);
    for (GotoXY(CC.X, CC.Y + 1), printf("┗"), ww = 0; ww < w; printf("━"), ww++); printf("┛");
    return;
}

void initialization(void){
    int xx, yy, i;
    rmines = level[lv][2];
    numofundig = level[lv][0] * level[lv][1];
    srand((unsigned int)time(NULL) + rand());
    SetColor(F_LBLACK, B_BLACK); DoAt(2, 1, drawmap(level[lv][0], level[lv][1]));
    SetColor(F_WHITE, B_BLACK);
    DoAt(level[lv][3], level[lv][4], printf("RemnantMines: %d  ", rmines));
    DoAt(level[lv][5], level[lv][6], printf("Restart     Back"));
    for (xx = 0; xx < level[lv][0]; xx++)
        for (yy = 0; yy < level[lv][1]; point[xx][yy][0] = point[xx][yy][1] = 0, yy++);
    for (i = 0; i < level[lv][2];){
        xx = rand() % level[lv][0];
        yy = rand() % level[lv][1];
        if (point[xx][yy][1] == 0){
            point[xx][yy][1] = 9;
            i++;
        }
    }
    for (xx = 0; xx < level[lv][0]; xx++)
        for (yy = 0; yy < level[lv][1]; yy++)
            if (point[xx][yy][1] != 9)
                for (i = 0; i < 8; i++)
                    if (xx + drc[i][0] < level[lv][0] && xx + drc[i][0] >= 0 &&
                        yy + drc[i][1] < level[lv][1] && yy + drc[i][1] >= 0 &&
                        point[xx + drc[i][0]][yy + drc[i][1]][1] == 9) point[xx][yy][1]++;
    return;
}

int midButtonPress(int x, int y){
    int i, tmp = 0;
    if (x >= 0 && x < level[lv][0] && y >= 0 && y < level[lv][1] &&
        point[x][y][0] == 1 && point[x][y][1] > 0 && point[x][y][1] < 9)
        for (i = 0, tmp = 0; i < 8; i++)
            if (x + drc[i][0] < level[lv][0] && x + drc[i][0] >= 0 &&
                y + drc[i][1] < level[lv][1] && y + drc[i][1] >= 0 &&
                point[x + drc[i][0]][y + drc[i][1]][0] == 2)tmp++;
    if (tmp == point[x][y][1])for (i = 0, tmp = 0; i < 8; tmp += dig(x + drc[i][0], y + drc[i][1]), i++);
    else tmp = 0;
    return (tmp) ? (1) : (0);
}

void explode(void){
    int x, y;
    for (x = 0; x < level[lv][0]; x++)
        for (y = 0; y < level[lv][1]; point[x][y][0] = 0, dig(x, y), y++);
    SetColor(F_LRED, B_BLACK); DoAt(level[lv][3], level[lv][4], printf(" - GAME  OVER -   "));
    return;
}