#include "Struct.h"

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

void Poro::processInput(char input, vector < int >& invalids, int& history_invalids) {
	switch (input) {
	case ENTER: {
		updateResults();
		output();
		break;
	}
	case BACKSPACE: {
		if (search_words.empty()) return;
		search_words.pop_back();
		cout << "\b \b";

		if (invalids.back()) --invalids.back();
		else if (search_trie->pNode == search_trie->root){
			search_trie->partial_results.pop_back();
			invalids.pop_back();
			search_trie->pNode = search_trie->partial_results.back();
		}
		else search_trie->pNode = search_trie->pNode->parent;

		if (history_invalids) --history_invalids;
		else history_trie->pNode = history_trie->pNode->parent;
		break;
	}
	default: {
		search_words.push_back(input);
		cout << input;

		if (input == SPACE){
			if (!invalids.empty() && invalids.back() != 0)
				search_trie->partial_results.push_back(search_trie->pNode);
			search_trie->pNode = search_trie->root;
		}
		else{
			if (search_trie->pNode->children.count(input)) {
				search_trie->pNode = search_trie->pNode->children[input];
			}
			else ++invalids.back();
		}

		if (history_trie->pNode->children.count(input)) {
			history_trie->pNode = history_trie->pNode->children[input];
		}
		else ++history_invalids;
	}
	}
}