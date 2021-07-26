﻿#pragma once
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
#include <map>
using namespace std;
const int c[13] = { '"',',','.','◼',')','(',':',';','“','”','—','_','\'' };
const set <int> special_characters(c, c + sizeof(c) / sizeof(int));
#define CALL_LIMIT 100000
#define NUM_OF_RECOMMENDATIONS 5
#define SEARCH_SIZE_LIMIT 55

#define BACKSPACE 8
#define ENTER 13
#define SPACE 32
#define QUOTATION 34
#define HASHTAG 35
#define DOLLAR 36
#define PLUS 43
#define MINUS 45

#define UP 72
#define DOWN 80
#define ESC 27