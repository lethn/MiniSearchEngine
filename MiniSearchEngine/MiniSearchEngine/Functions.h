#include "Struct.h"
/*
Normal Search Ranking:
	Exact Match
	AND
	OR
  Exact Match Search Ranking: Sort theo số lần xuất hiện chung của cả 2 trong file
  AND Search Ranking: Sort theo tổng số lần xuất hiện của cả 2 trong file
  OR Search Ranking: Sort theo tổng số lần xuất hiện của cả 2 trong file
*/

// Utility Functions
bool CompareFiles(File A, File B);		// dùng cho hàm sort();
void search_recommendations(vector < string >& recommendations, Node* pCur, string& s, int& called, int& found);
void gotoxy(int x, int y);
string convertToString(char* a, int size);

vector <Data> AND_DATA(vector <Data>& A, vector <Data>& B);
vector <int>& AND_INT(vector <int>& A, vector <int>& B, int d);
vector <Data> OR_DATA(vector <Data>& A, vector <Data>& B);
vector <int>& OR_INT(vector <int>& A, vector <int>& B);
vector <Data> EXCEPT(vector <Data>& A, vector <Data>& B);
vector <Data> EXACT_MATCHES(vector <Data>& A, vector <Data>& B, int d);
