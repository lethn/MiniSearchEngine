#include "Struct.h"

void Trie::deallocate(Node*& root) {
	for (auto A : root->children) {
		if (A.second)
			deallocate(A.second);
	}
	delete root;
}

void Trie::insert(string& s, int index, int position) {
	Node* cur = newNode(s);
	if (!cur->files.empty() && cur->files.back().index == index) {
		cur->files.back().positions.push_back(position);
	}
	else {
		cur->files.push_back(Data(index, position));
	}
}

void Trie::insertTitle(string& title, int index) {
	Node* cur = newNode(title);
	cur->inTitle.push_back(index);
}

void Trie::insertExtension(string& extension, int index) {
	Node* cur = newNode(extension);
	cur->fileType.push_back(index);
}

void Trie::insertNumber(int num, int index, int position)
{
	if (numbers.find(num) == numbers.end())
	{
		vector<Data> newData;
		newData.push_back(Data(index, position));
		numbers[num] = newData;
		return;
	}
	if (!numbers[num].empty() && numbers[num].back().index == index)
	{
		numbers[num].back().positions.push_back(position);
	}
	else
	{
		numbers[num].push_back(Data(index, position));
	}
}

void Trie::insertData(string& s, vector < File >& V) {
	Node* cur = newNode(s);
	vector < Data > result;
	for (auto& files : V) {
		result.push_back(files.index);
	}
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

void Trie::printData() {
	for(auto &child: root->children){
		dfs(child.second, root);
	}
}

void dfs(Node* u, Node* root) {
	if (u->isWord()) {
		cout << u->getString(root) << ' ';
		for (Data& data : u->files) {
			cout << data.index << ' ';
		}
		cout << '\n';
	}
	for (auto& child : u->children) {
		dfs(child.second, root);
	}
}

string Node::getString(Node* root) {
	string s;
	Node* pCur = this;
	while (pCur != root) {
		s.push_back(pCur->value);
		pCur = pCur->parent;
	}
	for(int l=0, r=s.size()-1; l<r; ++l, --r) swap(s[l], s[r]);
	return s;
}

bool Node::isWord() {
	return !files.empty();
}