#include "Functions.h"

void Trie::deallocate(Node*& root) {
	for (auto A : root->children) {
		if (A.second)
			deallocate(A.second);
	}
	delete root;
}

void Trie::insert(string& s, Data data) {
	Node* cur = root;
	for (int i = 0; i < s.size(); i++) {
		if (cur->children.find(s[i]) == cur->children.end()) {
			cur->children[s[i]] = new Node;
			cur->children[s[i]]->parent = cur;
		}
		cur = cur->children[s[i]];
	}
	cur->files.push_back(data);
}

Node* Trie::newNode(string& s) {
	Node* cur = root;
	for (int i = 0; i < s.size(); i++) {
		if (cur->children.find(s[i]) == cur->children.end()) {
			cur->children[s[i]] = new Node;
			cur->children[s[i]]->parent = cur;
		}
		cur = cur->children[s[i]];
	}
	return cur;
}

Node* Trie::search(string& s) {
	Node* cur = root;
	for (int i = 0; i < s.size(); i++) {
		if (cur->children.find(s[i]) == cur->children.end())
			return nullptr;
		cur = cur->children[s[i]];
	}
	if (cur->files.empty())
		return nullptr;
	return cur;
}