#include "Struct.h"

bool CompareFiles(File& A, File& B) {
	if (A.noExacts != B.noExacts)
		return A.noExacts > B.noExacts;
	if (A.noMatches != B.noMatches)
		return A.noMatches > B.noMatches;
	return A.index > B.index;
}

vector < Data > AND_Data(vector < Data >& A, vector < Data >& B) {
	vector <Data> result;
	int n = A.size(), m = B.size(), i = 0, j = 0;
	while (i < n && j < m) {
		if (A[i].index < B[j].index) ++i;
		else if (A[i].index > B[j].index) ++j;
		else {
			vector < int > C = OR_int(A[i].positions, B[j].positions);
			result.push_back(
				Data(A[i].index, C)
			);
			++i, ++j;
		}
	}
	return result;
}

vector < int > AND_int(vector < int >& A, vector < int >& B, int d) {
	vector < int > result;
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

vector < Data > OR_Data(vector < Data >& A, vector < Data >& B) {
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
			vector < int > C = OR_int(A[i].positions, B[j].positions);
			result.push_back(
				Data(A[i].index, C)
			);
			++i, ++j;
		}
	}
	while(i < n) result.push_back(A[i]), ++i;
	while(j < m) result.push_back(B[j]), ++j;
	return result;
}

vector < int > OR_int(vector < int >& A, vector < int >& B) {
	vector < int > result;
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

vector < File > OR_File(vector < File >& A, vector < int >& B) {
	vector < File > result;
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
		else{
			result.push_back(File(A[i].index, A[i].noExacts+1, A[i].noMatches+1));
			++i, ++j;
		}
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

void lowerString(string& s) {
	for (int i = 0; i < (int)s.size(); ++i) {
		s[i] = tolower(s[i]);
	}
}

bool isOperation(vector < Data >& V) {
	return (!V.empty() && V.back().index < 0);
}

vector <Data> EXCEPT(vector <Data>& A, vector <Data>& B) { // A: lấy   B: bỏ
	vector <Data> result;
	int n = A.size(), m = B.size(), i = 0, j = 0;
	while (i < n && j < m) {
		if (A[i].index < B[j].index) {
			result.push_back(Data(A[i].index, A[i].positions));
			++i;
		}
		else if (A[i].index == B[j].index) {
			++i;
			++j;
		}
		else ++j;
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
			vector < int > C = AND_int(A[i].positions, B[j].positions, d);
			if (!C.empty()) result.push_back(Data(A[i].index, C));
			++i;
			++j;
		}
	}
	return result;
}

bool isStopword(string& s, Trie& trie) {
	if (s[0] == PLUS) return false;
	Node* cur = trie.search(s);
	if (!cur) return false;
	return cur->isStopword;
}
void cutWord(string& a)
{
	string str = "";
	for (int i = 0; i < a.size(); i++)
	{
		if (special_characters.find(a[i]) != special_characters.end() || (a[i] < 0 && a[i] != -44))
		{
			continue;
		}
		str += tolower(a[i]);
	}
	a = str;
}

bool checkSameWord(vector<string> word, string& str)
{
	for (int i = 0; i < word.size(); i++)
	{
		if (iequals(word[i],str))
			return true;
	}
	return false;
}
bool iequals(const string& a, const string& b)
{
	return std::equal(a.begin(), a.end(),
		b.begin(), b.end(),
		[](char a, char b) {
			return tolower(a) == tolower(b);
		});
}
bool checkRangeNum(pair<int, int>number, string& str)
{
	if (str[0] != '$')
		return false;
	string tmp = "";
	for (int j = 1; j < str.size(); j++)
	{
		tmp += str[j];
	}
	int maxx = 1e8, minx = 0, num = stoi(tmp);
	if (number.first != -1)
		minx = number.first;
	else
		return false;
	if (number.second != -1)
		maxx = number.second;
	else
		maxx = minx;
	return num >= minx && num <= maxx;
}