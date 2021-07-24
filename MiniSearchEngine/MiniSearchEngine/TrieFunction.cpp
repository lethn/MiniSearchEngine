#include "Functions.h"

void Trie::deallocate(Node*& root) {
	for (auto A : root->children) {
		if (A.second)
			deallocate(A.second);
	}
	delete root;
}

void Trie::insert(string& s, int index, int position) {
	Node* cur = root;
	for (int i = 0; i < s.size(); i++) {
		if (cur->children.find(s[i]) == cur->children.end()) {
			cur->children[s[i]] = new Node(s[i], cur);
		}
		cur = cur->children[s[i]];
	}
	if (!cur->files.empty() && cur->files.back().index == index) {
		cur->files.back().positions.push_back(position);
	}
	else {
		cur->files.push_back(Data(index, position));
	}
}

void Trie::insertTitle(string& title, int index) {
	Node* cur = root;
	for (int i = 0; i < title.size(); i++) {
		if (cur->children.find(title[i]) == cur->children.end()) {
			cur->children[title[i]] = new Node(title[i], cur);
		}
		cur = cur->children[title[i]];
	}
	cur->inTitle.push_back(index);
}

void Trie::insertExtension(string& extension, int index) {
	Node* cur = root;
	for (int i = 0; i < extension.size(); i++) {
		if (cur->children.find(extension[i]) == cur->children.end()) {
			cur->children[extension[i]] = new Node(extension[i], cur);
		}
		cur = cur->children[extension[i]];
	}
	cur->fileType.push_back(index);
}

Node* Trie::newNode(string& s) {
	Node* cur = root;
	for (int i = 0; i < s.size(); i++) {
		if (cur->children.find(s[i]) == cur->children.end()) {
			cur->children[s[i]] = new Node(s[i], cur);
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
	if (!cur->isWord());
		return nullptr;
	return cur;
}

void Node::getString(string& s, Node* root) {
	Node* pCur = this;
	while (pCur != root) {
		s.push_back(pCur->value);
		pCur = pCur->parent;
	}
	for(int l=0, r=s.size()-1; l<r; ++l, --r) swap(s[l], s[r]);
}

bool Node::isWord() {
	return !files.empty();
}