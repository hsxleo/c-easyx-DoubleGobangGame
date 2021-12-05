#include <iostream>
#include <graphics.h>
#include <conio.h>
#pragma comment(lib,"Winmm.lib")  //��ӵı�������

using namespace std;

int chess[15][15] = { 0 };  //���̵�����
int color = 1;  //1 ���� 2 ����

//��������
void drawChessboard() {   
	initgraph(400, 400);
	setbkcolor(0x708090);
	cleardevice();
	//����������
	setlinecolor(BLACK);
	for (int i = 25; i <= 375; i+=25) {
		line(i, 25, i, 375);
		line(25, i, 375, i);
	}
	//���������ϵ������
	setfillcolor(BLACK);
	solidcircle(100, 100, 4);
	solidcircle(100, 300, 4);
	solidcircle(300, 100, 4);
	solidcircle(300, 300, 4);
	solidcircle(200, 200, 4);
}

//������
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


//�������
void inputOver(int color) {
	settextcolor(RED);          //����������ɫ
	settextstyle(30, 0, "������κ"); //����������ʽ
	setbkmode(TRANSPARENT);       //���ֱ���͸��
	switch (color) {
	case 1:
		outtextxy(150, 150, "�����ʤ");
		break;
	case 2:
		outtextxy(150, 150, "�����ʤ");
		break;
	}
	_getch();
}

//�ж���Ϸ�Ƿ����
void judgeWin(int x,int y,int color) {
	int count = 0;
	for (int i = x - 4; i <= x + 4; i++) {  //��ֱ����
		if (i < 0 || i > 15) continue;
		if (chess[i][y] != color) count = 0;
		else {
			count++;
			if (count == 5)inputOver(color);
		}
	}
	count = 0;
	for (int i = y - 4; i <= y + 4; i++) {  //ˮƽ����
		if (i < 0 || i > 15) continue;
		if (chess[x][i] != color) count = 0;
		else {
			count++;
			if (count == 5) inputOver(color);
		}
	}
	count = 0;
	for (int i = x - 4, j = y - 4; i <= x + 4; i++,j++) {   //���Խ���
		if (i < 0 || i > 15 || j < 0 || j > 15) continue;
		if (chess[i][j] != color) count = 0;
		else {
			count++;
			if (count == 5) inputOver(color);
		}
	}
	count = 0;
	for (int i = x - 4, j = y + 4; i <= x + 4; i++, j--) {   //���Խ���
		if (i < 0 || i > 15 || j < 0 || j > 15) continue;
		if (chess[i][j] != color) count = 0;
		else {
			count++;
			if (count == 5) inputOver(color);
		}
	}
}


//�����  
void mouseClick() {
	MOUSEMSG m;
	while (true) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {  //����������
			for (int i = 25; i <= 400; i+=25) {
				for (int j = 25; j <= 400; j += 25) {
					if (m.x >= i - 8 && m.x <= i + 8 && m.y >= j - 8 && m.y <= j + 8 ) {
						if (chess[i / 25][j / 25] != 0) {  //��λ��������;
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
	//��Ϸ��������
	mciSendString("open music.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);
	//��������
	drawChessboard(); 
	mouseClick();
	_getch();
}