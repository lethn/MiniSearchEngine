#include "Functions.h"

bool CompareFiles(File A, File B) {
	if (A.noExacts != B.noExacts)
		return A.noExacts < B.noExacts;
	if (A.noMatches != B.noMatches)
		return A.noMatches < B.noMatches;
	return A.index < B.index;
}

vector <Data> EXACTMATCHES(vector <Data>& A, vector <Data>& B, int& d) { // chua xong 
	vector <Data> result;
	int n = A.size(), m = B.size(), i = 0, j = 0;
	while (i < n && j < m) {
		if (A[i].index < B[j].index) ++i;
		else if (A[i].index > B[j].index) ++j;
		else {
			result.push_back(Data(A[i].index, AND_INT(A[i].positions, B[i].positions, d)));
			++i;
			++j;
		}
	}
	return result;
}

vector <Data> AND_DATA(vector <Data>& A, vector <Data>& B, int d = 0) {
	vector <Data> result;
	int n = A.size(), m = B.size(), i = 0, j = 0;
	while (i < n && j < m) {
		if (A[i].index < B[j].index) ++i;
		else if (A[i].index > B[j].index) ++j;
		else {
			result.push_back(Data(A[i].index, OR_INT(A[i].positions, B[i].positions)));
			++i;
			++j;
		}
	}
	return result;
}

vector <int>& AND_INT(vector <int>& A, vector <int>& B, int d = 0) {
	vector <int> result;
	int n = A.size(),
		m = B.size(),
		i = 0, j = 0;
	while (i < n && j < m) {
		if (A[i] + d < B[j]) ++i;
		else if (A[i] + d > B[j]) ++j;
		else result.push_back(A[i]), ++i, ++j;
	}
	return result;
}

vector <Data> OR_DATA(vector <Data>& A, vector <Data>& B) {
	// spaghetti
	vector <Data> result;
	int n = A.size(), m = B.size(), i = 0, j = 0;
	while (i < n && j < m) {
		if (A[i].index < B[j].index){
			result.push_back(A[i]);
			++i;
		}
		else if (A[i].index > B[j].index){
			result.push_back(B[j]);
			++j;
		}
		else {
			result.push_back(Data(A[i].index, OR_INT(A[i].positions, B[j].positions)));
			++i;
			++j;
		}
	}
	while(i < n) result.push_back(A[i]), ++i;
	while(j < n) result.push_back(B[i]), ++j;
	return result;
}

vector <int>& OR_INT(vector <int>& A, vector <int>& B) {
	vector <int> result;
	int n = A.size(),
		m = B.size(),
		i = 0, j = 0;
	while (i < n && j < m) {
		if (A[i] < B[j]){
			result.push_back(A[i]);
			++i;
		}
		else if (A[i] > B[j]){
			result.push_back(B[j]);
			++j;
		}
		else result.push_back(A[i]), ++i, ++j;
	}
	while (i < n) result.push_back(A[i]), ++i;
	while (j < m) result.push_back(B[j]), ++j;
	return result;
}

string convertToString(char* a, int size) {
	int i;
	string s = "";
	for (i = 0; i < size; i++)
		s = s + a[i];
	return s;
}

void gotoxy(int x, int y) {
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}