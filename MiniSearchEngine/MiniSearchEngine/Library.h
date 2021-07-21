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
using namespace std;

#define CALL_LIMIT 100000
#define NUM_OF_RECOMMENDATIONS 5
#define SEARCH_SIZE_LIMIT 55
#define BACKSPACE 8
#define ENTER 13
#define SPACE 32
#define UP 72
#define DOWN 80
#define ESC 27

const int c[14] = { '"',',','.','◼',')','(',':',';','“','”','—','-','_','\'' };
const set <int> special_characters(c, c+sizeof(c)/sizeof(int));