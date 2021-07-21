#include "Library.h"

struct Poro;
struct File;
struct Data;
struct Trie;
struct Node;

struct Poro {	// save global variables
	Trie* search_trie;
	Trie* history_trie;
	list <string> recent_search;
	string search_words;
	vector <int> operators;
	vector <vector <Node*>> synonyms;
	vector <string> file_names;
	vector < string > recommendations;

	void load_data(string indexfile);
	void menu();
	void input();	// real-time input, mỗi ký tự input vào gọi hàm recommend()
	void processInput(char input, vector < int >& invalids, int& history_invalids);
	void updateResults();
	void output();
	void recommend();
	// search history
	// called == 10^5 || found == 5 => return hết;

	Poro();
};

struct File{
	int index;
	int noExacts; 	// number of exact matches
	int noMatches;	// number of matches

	File();
	File(int _index, int _noExacts, int _noMatches);
};

struct Data {
	int index;
	vector <int> positions;

	Data();
	Data(int _index);
	Data(int _index, int pos);
};

struct Trie {
	Node* root;
	vector <File> result;
	vector <Node*>  partial_results; // Vector pointer chỉ vào Node
									 // dùng để tìm exact match
								  	 // “tallest building”, “tallest * in the world“, ...

	Node* pNode; // dùng để recommend
				 // lúc input:
				 // gõ chữ nào đi xuống chữ đấy
				 // nhập vào thì chạy xuống children
				 // backspace thì lên parent
			  	 // backspace về root thì pNode = partial_results.back();
				 // space thì nếu node ko là operator hay stopwords thì
				 // partial_results.push_back(pNode);
				 // nếu là operator thì set cái operator về type đó (somehow?)
				 // enter thì gọi hàm updateResult()
				 // “ thì set exact_match = true, check lúc enter có ”

	void deallocate(Node*& root);
	void insert(string& s, int index, int position);
	Node* newNode(string& s);
	Node* search(string& s);	// run loop

	Trie();
};

struct Node{
	Node* parent;
	vector <Data> files;	//	Data[0..n].first = file nào
							// 	Data[0..n].second[0..n] = vị trí nào trong file
							//	vị trí xài trong cái tìm 8, 9 ấy
	unordered_map <char, Node*> children;
	// History ko có cái này
	int synonym_root;	// 0, 1, 2 … = hàng của từ đó -1;
	bool isOperator;
	bool isStopword;

	Node();
	Node(Node* _parent);
	Node(Node* _parent, int _synonym_root, int _isOperator, int _isStopword);
};



