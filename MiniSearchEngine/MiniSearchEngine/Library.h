#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <set>
#include <stack>
#include <sstream>
#include <map>
using namespace std;
const int c[] = { '"',',','.','◼',')','(',':',';','“','”','—','_','\'','[',']','{','}'};
const set <int> special_characters(c, c + sizeof(c) / sizeof(int));
const string SOURCE = "source\\";
const string INTITLE = "intitle:";
const string FILETYPE = "filetype:";
const string AND = "AND";
const string OR = "OR";
const int INTITLE_SIZE = INTITLE.size();
const int FILETYPE_SIZE = FILETYPE.size();
const int AND_SIZE = AND.size();
const int OR_SIZE = OR.size();

typedef pair < int, int > ii;

#define CALL_LIMIT 100000
#define NUM_OF_RECOMMENDATIONS 5
#define SEARCH_SIZE_LIMIT 55

#define BACKSPACE 8
#define ENTER 13
#define SPACE 32
#define QUOTATION 34
#define HASHTAG 35
#define DOLLAR 36
#define OPEN_PARENTHESIS 40
#define CLOSE_PARENTHESIS 41
#define ASTERISK 42
#define PLUS 43
#define MINUS 45
#define FULL_STOP 46
#define SWUNG_DASH 126

#define UP 72
#define DOWN 80
#define ESC 27
