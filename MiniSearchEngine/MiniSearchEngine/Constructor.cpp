#include "Struct.h"

Poro::Poro() {
	search_trie = new Trie();
	history_trie = new Trie();
}

File::File() {
	index = noExacts = noMatches = 0;
}

File::File(int _index, int _noExacts, int _noMatches) {
	index = _index;
	noExacts = _noExacts;
	noMatches = _noMatches;
}

Data::Data() {
	index = 0;
}

Data::Data(int _index) {
	index = _index;
}

Data::Data(int _index, int pos){
	index = _index;
	positions.push_back(pos);
}

Trie::Trie() {
	root = new Node();
	pNode = root;
}

Node::Node(){
	parent = nullptr;
	synonym_root = -1;
	isOperator = false;
	isStopword = false;
}

Node::Node(Node* _parent) {
	parent = _parent;
	synonym_root = -1;
	isOperator = false;
	isStopword = false;
}

Node::Node(Node* _parent, int _synonym_root, int _isOperator, int _isStopword) {
	parent = _parent;
	synonym_root = _synonym_root;
	isOperator = _isOperator;
	isStopword = _isStopword;
}