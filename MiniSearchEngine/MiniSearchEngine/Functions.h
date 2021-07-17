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

// UTILS (namespace)
bool CompareOR(File A, File B);		// dùng cho hàm sort();
bool CompareAND(File A, File B);
vector <Data> AND(vector <Data>& A, vector <Data>& B);
vector <Data> OR(vector <Data>& A, vector <Data>& B);

