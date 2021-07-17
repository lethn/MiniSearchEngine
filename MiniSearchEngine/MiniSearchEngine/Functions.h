#include "Class.h"

/*
Normal Search Ranking:
	Exact Match
	AND
	OR
  Exact Match Search Ranking: Sort theo số lần xuất hiện chung của cả 2 trong file
  AND Search Ranking: Sort theo tổng số lần xuất hiện của cả 2 trong file
  OR Search Ranking: Sort theo tổng số lần xuất hiện của cả 2 trong file
*/

// Poro
void Poro::load_data(char* indexfile);
void Poro::menu();
void Poro::input();	// real-time input, mỗi ký tự input vào gọi hàm recommend()
void Poro::updateResults();
void Poro::output();
void Poro::recommend(int& called = 0, int& found = 0);
// search history
// called == 10^5 || found == 5 => return hết;

// Trie
Void Trie::deallocate(Trie trie);
Void Trie::insert(string& s, Data* data, Trie* trie);
Node* Trie::search(string& s); // run loop

// UTILS (namespace)
bool CompareOR(File A, File B);		// dùng cho hàm sort();
bool CompareAND(File A, File B);
vector <Data> AND(vector <Data>& A, vector <Data>& B);
vector <Data> OR(vector <Data>& A, vector <Data>& B);

