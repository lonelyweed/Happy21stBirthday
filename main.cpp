#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#ifdef _WIN32
#include <tchar.h>
#include <windows.h>
#define COLORS 16
#endif

#ifdef unix
#include <ncurses.h>
#include <unistd.h>
#define COLORS 8
#endif

const int ROW = 7;
const int COL = 13;

using namespace std;

using ASCII_CHAR = vector<vector<int>>;

map<int, int (*)[2]> Coordinate;

#ifdef _WIN32
#define sleep(n) Sleep(n)
#define print(s) (cout<<s)

void refresh()
{}

void goto_xy(short x, short y)
{
  HANDLE hOut;
  hOut      = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos = {y, x};
  SetConsoleCursorPosition(hOut, pos);
}

void set_color(unsigned short ForeColor = 7, unsigned short BackGroundColor = 0)
{
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);
}

void move_window()
{
#if defined(_MSC_VER)
	char title[100];
#elif defined(__GNUC__)
  LPSTR title;
#endif
  HWND   hwnd;
  GetConsoleTitle(title, 100);
  hwnd = FindWindow(NULL, title);
  MoveWindow(hwnd, 100, 100, 300, 300, TRUE);
}

void hide_cur()
{
  HANDLE              handle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO CursorInfo;
  GetConsoleCursorInfo(handle, &CursorInfo);
  CursorInfo.bVisible = false;
  SetConsoleCursorInfo(handle, &CursorInfo);
}

void init()
{
  move_window();
  system("cls");
  system("title Loading...");
  system("mode con cols=96");
  system("mode con lines=32");
}
#endif

#ifdef unix
#define sleep(n) usleep(n*1000)
#define print(s) printw(s)
void goto_xy(short x, short y)
{
  move(x, y);
}

void set_color(unsigned short ForeColor = 7, unsigned short BackGroundColor = 0)
{
  attron(COLOR_PAIR(ForeColor));
}

void hide_cur()
{
  curs_set(0);
}

void init()
{
  initscr();
  noecho();
  cbreak();
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_CYAN, COLOR_BLACK);
  init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(5, COLOR_YELLOW, COLOR_BLACK);
  init_pair(6, COLOR_RED, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
  //init_pair(8, COLOR_WHITE, COLOR_BLACK);
}
#endif

ASCII_CHAR LetterA      = {{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
                      {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
                      {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                      {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}};
ASCII_CHAR LetterB      = {{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                      {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                      {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0}};
ASCII_CHAR LetterD      = {{1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                      {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}};
ASCII_CHAR LetterH      = {{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}};
ASCII_CHAR LetterI      = {{1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}};
ASCII_CHAR LetterP      = {{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                      {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
ASCII_CHAR LetterR      = {{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
                      {1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
                      {1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
                      {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
                      {1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
                      {1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
                      {1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}};
ASCII_CHAR LetterLowerS = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                           {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
ASCII_CHAR LetterT      = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
};
ASCII_CHAR LetterLowerT = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                           {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}};
ASCII_CHAR LetterY      = {{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                      {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                      {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}};

ASCII_CHAR Number2 = {{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                      {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0}};

ASCII_CHAR Number1 = {{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

vector<ASCII_CHAR> orders = {
    LetterH, LetterA,      LetterP,      LetterP, LetterY, Number2,
    Number1, LetterLowerS, LetterLowerT, LetterB, LetterI, LetterR,
    LetterT, LetterH,      LetterD,      LetterA, LetterY};

int coordinates[17][2] = {{2, 19},  {2, 31},  {2, 46},  {2, 57},  {2, 68},
                          {11, 32}, {11, 44}, {11, 48}, {11, 55}, {20, 2},
                          {20, 14}, {20, 21}, {20, 33}, {20, 45}, {20, 57},
                          {20, 69}, {20, 84}};

void draw_left_to_right(int x, int y, ASCII_CHAR l, bool twinking = false,
                        int color = 0)
{
  for (int i = 0; i < ROW; ++i) {
    goto_xy(x + i, y);
    for (int j = 0; j < COL; ++j) {
      if (l[i][j]) {
        if (twinking) {
          set_color(color);
        } else {
          sleep(30);
        }
        print("*");
        set_color();
      } else {
        print(" ");
      }
      refresh();
    }
  }
}
void draw_up_to_down(int x, int y, ASCII_CHAR l, bool twinking = false,
                     int color = 0)
{
  for (int j = 0; j < COL; ++j) {
    for (int i = 0; i < ROW; ++i) {
      goto_xy(x + i, y + j);
      if (l[i][j]) {
        if (twinking) {
          set_color(color);
        } else {
          sleep(40);
        }
        print("*");
        set_color();
      } else
        print(" ");
      refresh();
    }
  }
}

int main(int arc, const char **argv)
{
  /*
   *        A   B   D  H  I  P  R  s    T   t  Y   2   1
   *      13  10  10 10  5  9  9  5   10   5  9  10   2
   *
   */
  init();
  srand(time(0));
  // getchar();
  // Sleep(5000);
  // draw_up_to_down(0, 2, Number1);
  for (int i = 0; i < 17; ++i) {
    Coordinate.insert(pair<int, int(*)[2]>(i, &coordinates[i]));
  }

  draw_left_to_right(2, 19, LetterH);         // H
  draw_up_to_down(2, 31, LetterA);            // A
  draw_left_to_right(2, 46, LetterP);         // P
  draw_up_to_down(2, 57, LetterP);            // P
  draw_left_to_right(2, 68, LetterY);         // Y
                                              //
  draw_up_to_down(11, 32, Number2);           // 2
  draw_left_to_right(11, 44, Number1);        // 1
  draw_up_to_down(11, 48, LetterLowerS);      // s
  draw_left_to_right(11, 55, LetterLowerT);   // t
                                              //
  draw_up_to_down(20, 2, LetterB);            // B
  draw_left_to_right(20, 14, LetterI);        // I
  draw_up_to_down(20, 21, LetterR);           // R
  draw_left_to_right(20, 33, LetterT);        // T
  draw_up_to_down(20, 45, LetterH);           // H
  draw_left_to_right(20, 57, LetterD);        // D
  draw_up_to_down(20, 69, LetterA);           // A
  draw_left_to_right(20, 84, LetterY);        // Y

  hide_cur();
  #ifdef _WIN32
  system("title Happy ~");
  #endif
  while (true) {
    for (int i = 0; i < 17; ++i) {
      int color = rand() % COLORS;
      draw_left_to_right((*Coordinate[i])[0], (*Coordinate[i])[1], orders[i],
                         true, color);
    }
  }
  #ifdef _WIN32
  cout << endl;
  #endif
  return 0;
}