﻿#include "Functions.h"

bool CompareFiles(File A, File B) {
	if (A.noExacts != B.noExacts)
		return A.noExacts < B.noExacts;
	if (A.noMatches != B.noMatches)
		return A.noMatches < B.noMatches;
	return A.index < B.index;
}

vector <Data> AND_DATA(vector <Data>& A, vector <Data>& B) {
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

vector <int>& AND_INT(vector <int>& A, vector <int>& B, int d) { // d = 0;
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

vector <Data> EXCEPT(vector <Data>& A, vector <Data>& B) { // A: lấy   B: bỏ
	vector <Data> result;
	int n = A.size(), m = B.size(), i = 0, j = 0;
	while (i < n && j < m) {
		if (A[i].index != B[j].index)
			result.push_back(Data(A[i].index, A[i].positions));
		else {
			i++;
			j++;
		}
	}
	while (i < n) {
		result.push_back(Data(A[i].index, A[i].positions));
		++i;
	}
	return result;
}

vector <Data> EXACT_MATCHES(vector <Data>& A, vector <Data>& B, int d) {
	vector <Data> result;
	int n = A.size(), m = B.size(), i = 0, j = 0;
	while (i < n && j < m) {
		if (A[i].index < B[j].index) ++i;
		else if (A[i].index > B[j].index) ++j;
		else {
			result.push_back(Data(A[i].index, AND_INT(A[i].positions, B[i].positions, d + 1)));
			++i;
			++j;
		}
	}
	return result;
}


vector <Data> Poro::searchSingleNumber(int number) {
	vector<Data> result;
	for (auto A : search_trie->numbers) {
		if (A.first == number)
			result = A.second;
	}
	return result;
}

vector <Data> Poro::searchRangeNumber(int number1, int number2) {
	vector<Data> result;
	for (auto A : search_trie->numbers) {
		if (A.first >= number1 && A.first <= number2) {
			if (result.empty())
				result = A.second;
			else {
				while (!A.second.empty()) {
					result.push_back(A.second.back());
					A.second.pop_back();
				}
			}
		}
	}
	return result;
}