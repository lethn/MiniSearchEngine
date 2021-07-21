#include "Functions.h"

void resizeConsole(int width, int height);
void Nocursortype();
void UnNocursortype();
void gotoxy(int x, int y);
void txtColor(int color);

void logo();
void inputBoard();
void input(char wordType[], int& size);

void keywordBoard();
void straightLine();
void backBorder();
string convertToString(char* a, int size);
void subMenu(char wordType[], int size);

void mainMenu(char wordType[], int size);