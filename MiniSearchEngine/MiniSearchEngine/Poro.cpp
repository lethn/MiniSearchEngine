#include "Class.h"

void search_recommendations(vector < string >& recommendations, 
	Node* pCur, string& s, int& called, int& found){
	if (pCur == nullptr) return;
	if (pCur->files.size() != 0) {
		recommendations.push_back(s);
		++found;
		if (called > CALL_LIMIT || found > NUM_OF_RECOMMENDATION) return;
	}
	for (auto child : pCur->children) {
		s.push_back(child.first);
		search_recommendations(recommendations, child.second, s, ++called, found);
		s.pop_back();
		if (called > CALL_LIMIT || found > NUM_OF_RECOMMENDATION) return;
	}
}

void Poro::recommend() {
	int called = 0, found = 0;
	string s = search_words;
	recommendations.empty();
	search_recommendations(recommendations, history_trie->pNode, s, called, found);
	if (called > CALL_LIMIT || found > NUM_OF_RECOMMENDATION) return;
	search_recommendations(recommendations, search_trie->pNode, s, called, found);
}