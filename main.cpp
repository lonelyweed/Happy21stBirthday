#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <windows.h>

const int ROW = 7;
const int COL = 13;

using namespace std;

using ASCII_CHAR = vector<vector<int>>;

map<int, int(*)[2]> Coordinate;

void goto_xy(short x, short y) {
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { y, x };
	SetConsoleCursorPosition(hOut, pos);
}

void set_color(unsigned short ForeColor = 7,
	unsigned short BackGroundColor = 0) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);  //获取当前窗口句柄
	SetConsoleTextAttribute(handle,
		ForeColor + BackGroundColor * 0x10);  //设置颜色
}

void move_window()
{
	char title[100];
	HWND hwnd;
	GetConsoleTitle(title, 100);
	hwnd = FindWindow(NULL, title);
	MoveWindow(hwnd, 100, 100, 300, 300, TRUE);
}

void hide_cur() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);  //获取控制台光标信息
	CursorInfo.bVisible = false;                //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);  //设置控制台光标状态
}
ASCII_CHAR LetterA = { {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
					  {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
					  {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
					  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
					  {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
					  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1} };
ASCII_CHAR LetterB = { {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
					  {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
					  {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0} };
ASCII_CHAR LetterD = { {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
					  {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0} };
ASCII_CHAR LetterH = { {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
					  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} };
ASCII_CHAR LetterI = { {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
					  {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					  {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					  {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					  {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					  {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					  {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0} };
ASCII_CHAR LetterP = { {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
					  {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };
ASCII_CHAR LetterR = { {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
					  {1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
					  {1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
					  {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
					  {1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
					  {1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
					  {1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0} };
ASCII_CHAR LetterLowerS = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						   {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						   {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						   {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						   {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
						   {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };
ASCII_CHAR LetterT = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
};
ASCII_CHAR LetterLowerT = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						   {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						   {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						   {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
						   {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
						   {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0} };
ASCII_CHAR LetterY = { {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
					  {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
					  {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
					  {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
					  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
					  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
					  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0} };

ASCII_CHAR Number2 = { {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
					  {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
					  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
					  {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
					  {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
					  {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
					  {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0} };

ASCII_CHAR Number1 = { {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					  {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					  {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					  {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					  {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					  {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					  {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };

vector<ASCII_CHAR> orders = {
	LetterH, LetterA,      LetterP,      LetterP, LetterY, Number2,
	Number1, LetterLowerS, LetterLowerT, LetterB, LetterI, LetterR,
	LetterT, LetterH,      LetterD,      LetterA, LetterY };

int coordinates[17][2] = { {2, 19},  {2, 31},  {2, 46},  {2, 57},  {2, 68},
						  {11, 32}, {11, 44}, {11, 48}, {11, 55}, {20, 2},
						  {20, 14}, {20, 21}, {20, 33}, {20, 45}, {20, 57},
						  {20, 69}, {20, 84} };

void draw_left_to_right(int x, int y, ASCII_CHAR l, bool twinking = false,
	int color = 0) {
	for (int i = 0; i < ROW; ++i) {
		goto_xy(x + i, y);
		for (int j = 0; j < COL; ++j) {
			if (l[i][j]) {
				if (twinking) {
					set_color(color);
				}
				else {
					Sleep(30);
				}
				cout << "*";
				set_color();
			}
			else {
				cout << " ";
			}
		}
	}
}
void draw_up_to_down(int x, int y, ASCII_CHAR l, bool twinking = false,
	int color = 0) {
	for (int j = 0; j < COL; ++j) {
		for (int i = 0; i < ROW; ++i) {
			goto_xy(x + i, y + j);
			if (l[i][j]) {
				if (twinking) {
					set_color(color);
				}
				else {
					Sleep(40);
				}
				cout << "*";
				set_color();
			}
			else
				cout << " ";
		}
	}
}

int main(int arc, const char **argv) {
	/*
	 *        A   B   D  H  I  P  R  s    T   t  Y   2   1
	 *宽度    13  10  10 10  5  9  9  5   10   5  9  10   2
	 *
	 */
	 /*

   对应的颜色码表：

   1. 0 = 黑色       8 = 灰色

   1 = 蓝色       9 = 淡蓝色

   2 = 绿色       10 = 淡绿色

   3 = 浅绿色     11 = 淡浅绿色

   4 = 红色       12 = 淡红色

   5 = 紫色       13 = 淡紫色

   6 = 黄色       14 = 淡黄色

   7 = 白色       15 = 亮白色

   */
	move_window();
	system("cls");
	system("title Loading...");
	system("mode con cols=96");
	system("mode con lines=32");
	srand(time(0));
	//getchar();
	//Sleep(5000);
	// draw_up_to_down(0, 2, Number1);
	for (int i = 0; i < 17; ++i) {
		Coordinate.insert(pair<int, int(*)[2]>(i, &coordinates[i]));
	}

	draw_left_to_right(2, 19, LetterH);        // H
	draw_up_to_down(2, 31, LetterA);           // A
	draw_left_to_right(2, 46, LetterP);        // P
	draw_up_to_down(2, 57, LetterP);           // P
	draw_left_to_right(2, 68, LetterY);        // Y
											   //
	draw_up_to_down(11, 32, Number2);          // 2
	draw_left_to_right(11, 44, Number1);       // 1
	draw_up_to_down(11, 48, LetterLowerS);     // s
	draw_left_to_right(11, 55, LetterLowerT);  // t
											   //
	draw_up_to_down(20, 2, LetterB);           // B
	draw_left_to_right(20, 14, LetterI);       // I
	draw_up_to_down(20, 21, LetterR);          // R
	draw_left_to_right(20, 33, LetterT);       // T
	draw_up_to_down(20, 45, LetterH);          // H
	draw_left_to_right(20, 57, LetterD);       // D
	draw_up_to_down(20, 69, LetterA);          // A
	draw_left_to_right(20, 84, LetterY);       // Y

	hide_cur();
	system("title 祝慧姐生日快乐~");
	while (true) {
		for (int i = 0; i < 17; ++i) {
			int color = rand() % 16;
			draw_left_to_right((*Coordinate[i])[0], (*Coordinate[i])[1], orders[i],
				true, color);
		}
	}
	cout << endl;
	return 0;
}