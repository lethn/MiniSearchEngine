#include "Functions.h"

bool CompareFiles(File A, File B) {
	if (A.noExacts != B.noExacts)
		return A.noExacts < B.noExacts;
	if (A.noMatches != B.noMatches)
		return A.noMatches < B.noMatches;
	return A.index < B.index;
}

vector <Data> AND(vector <Data>& A, vector <Data>& B) {
	// spaghetti
	vector <Data> result;
	int n = A.size(), m = B.size(), i = 0, j = 0;
	while (i < n && j < m) {
		if (A[i].index < B[j].index) ++i;
		else if (A[i].index > B[j].index) ++j;
		else {
			result.push_back(Data(A[i].index));
			vector < int >* X = &A[i].positions,* Y = &B[j].positions;
			vector < int >* V = &result.back().positions;
			int N = (*X).size(),
				M = (*Y).size(),
				x = 0, y = 0;
			while (x < N && y < M) {
				if ((*X)[x] < (*Y)[y]) ++x;
				else if ((*X)[x] > (*Y)[y]) ++y;
				else (*V).push_back((*X)[x]), ++x, ++y;
			}
			++i, ++j;
		}
	}
	return result;
}

vector <Data> OR(vector <Data>& A, vector <Data>& B) {
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
			result.push_back(Data(A[i].index));
			vector < int >* X = &A[i].positions,* Y = &B[j].positions;
			vector < int >* V = &result.back().positions;
			int N = (*X).size(),
				M = (*Y).size(),
				x = 0, y = 0;
			while (x < N && y < M) {
				if ((*X)[x] < (*Y)[y]){
					(*V).push_back((*X)[x]);
					++x;
				}
				else if ((*X)[x] > (*Y)[y]){
					(*V).push_back((*Y)[y]);
					++y;
				}
				else (*V).push_back((*X)[x]), ++x, ++y;
			}
			++i, ++j;
		}
	}
	return result;
}