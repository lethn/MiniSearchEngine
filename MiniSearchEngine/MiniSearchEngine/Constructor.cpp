#include "Struct.h"

Poro::Poro() {
	search_trie = new Trie();
	history_trie = new Trie();
	history_invalids = 0;
	openQuotation = false;
	invalids.push_back(0);
}

File::File() {
	index = noExacts = noMatches = 0;
}

File::File(int _index) {
	index = _index;
	noExacts = 0;
	noMatches = 0;
}

File::File(int _index, int _noExacts, int _noMatches) {
	index = _index;
	noExacts = _noExacts;
	noMatches = _noMatches;
}

File::File(Data& A, bool exact) {
	index = A.index;
	noExacts = 0;
	noMatches = A.positions.size();
	if (exact) noExacts = A.positions.size();
}

bool File::operator<(int& _index) {
	return index < _index;
}
bool File::operator> (int& _index) {
	return index > _index;
}
bool File::operator==(int& _index) {
	return index == _index;
}

Data::Data() {
	index = 0;
}

Data::Data(int _index) {
	index = _index;
}

Data::Data(int _index, int _pos){
	index = _index;
	positions.push_back(_pos);
}

Data::Data(int _index, vector < int >& _positions) 
	: positions(_positions) {
	index = _index;
}

Trie::Trie() {
	root = new Node();
	pNode = root;
}

Node::Node(){
	value = 0;
	parent = nullptr;
	synonym_root = -1;
	operator_type = 0;
	isStopword = false;
}

Node::Node(char _value, Node* _parent) {
	value = _value;
	parent = _parent;
	synonym_root = -1;
	operator_type = 0;
	isStopword = false;
}

Node::Node(char _value, Node* _parent, int _synonym_root, int _operator_type, int _isStopword) {
	value = _value;
	parent = _parent;
	synonym_root = _synonym_root;
	operator_type = _operator_type;
	isStopword = _isStopword;
}