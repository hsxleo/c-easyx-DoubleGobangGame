#include <iostream>
#include <graphics.h>
#include <conio.h>
#pragma comment(lib,"Winmm.lib")  //添加的背景音乐

using namespace std;

int chess[15][15] = { 0 };  //棋盘的数组
int color = 1;  //1 黑棋 2 白棋

//绘制棋盘
void drawChessboard() {   
	initgraph(400, 400);
	setbkcolor(0x708090);
	cleardevice();
	//绘制棋盘线
	setlinecolor(BLACK);
	for (int i = 25; i <= 375; i+=25) {
		line(i, 25, i, 375);
		line(25, i, 375, i);
	}
	//绘制棋盘上的五个点
	setfillcolor(BLACK);
	solidcircle(100, 100, 4);
	solidcircle(100, 300, 4);
	solidcircle(300, 100, 4);
	solidcircle(300, 300, 4);
	solidcircle(200, 200, 4);
}

//绘制棋
void drawChess(int x, int y,int color) {
	switch (color) {
	case 1:
		setfillcolor (BLACK);
		break;
	case 2:
		setfillcolor (WHITE);
		break;
	}
	solidcircle(x*25, y*25, 8);
}


//输出结束
void inputOver(int color) {
	settextcolor(RED);          //设置字体颜色
	settextstyle(30, 0, "华文新魏"); //设置文字样式
	setbkmode(TRANSPARENT);       //文字背景透明
	switch (color) {
	case 1:
		outtextxy(150, 150, "黑棋获胜");
		break;
	case 2:
		outtextxy(150, 150, "白棋获胜");
		break;
	}
	_getch();
}

//判断游戏是否结束
void judgeWin(int x,int y,int color) {
	int count = 0;
	for (int i = x - 4; i <= x + 4; i++) {  //垂直方向
		if (i < 0 || i > 15) continue;
		if (chess[i][y] != color) count = 0;
		else {
			count++;
			if (count == 5)inputOver(color);
		}
	}
	count = 0;
	for (int i = y - 4; i <= y + 4; i++) {  //水平方向
		if (i < 0 || i > 15) continue;
		if (chess[x][i] != color) count = 0;
		else {
			count++;
			if (count == 5) inputOver(color);
		}
	}
	count = 0;
	for (int i = x - 4, j = y - 4; i <= x + 4; i++,j++) {   //正对角线
		if (i < 0 || i > 15 || j < 0 || j > 15) continue;
		if (chess[i][j] != color) count = 0;
		else {
			count++;
			if (count == 5) inputOver(color);
		}
	}
	count = 0;
	for (int i = x - 4, j = y + 4; i <= x + 4; i++, j--) {   //反对角线
		if (i < 0 || i > 15 || j < 0 || j > 15) continue;
		if (chess[i][j] != color) count = 0;
		else {
			count++;
			if (count == 5) inputOver(color);
		}
	}
}


//鼠标点击  
void mouseClick() {
	MOUSEMSG m;
	while (true) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {  //鼠标左键按下
			for (int i = 25; i <= 400; i+=25) {
				for (int j = 25; j <= 400; j += 25) {
					if (m.x >= i - 8 && m.x <= i + 8 && m.y >= j - 8 && m.y <= j + 8 ) {
						if (chess[i / 25][j / 25] != 0) {  //该位置已有棋;
							break;
						}
						int x = i / 25;
						int y = j / 25;
						drawChess(x, y, color);
						switch (color){
						case 1:
							chess[x][y] = 1;
							judgeWin (x, y, color);
							color = 2;
							break;
						case 2:
							chess[x][y] = 2;
							judgeWin (x, y, color);
							color = 1;
							break;
						}
						break;
					}
				}
			}

		}
	}
}



int main() {
	//游戏背景音乐
	mciSendString("open music.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);
	//绘制棋盘
	drawChessboard(); 
	mouseClick();
	_getch();
}