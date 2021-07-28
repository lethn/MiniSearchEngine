#include "Library.h"

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
	Data(int _index, int _pos);
	Data(int _index, vector < int >& _positions);
};

struct Node{
	char value;				//	Node lưu chữ gì
	Node* parent;
	vector <Data> files;	//	Data[0..n].first = file nào
							// 	Data[0..n].second[0..n] = vị trí nào trong file
							//	Vị trí xài trong cái tìm 8, 9 ấy
	vector < int > inTitle; //  chứa index của file;
	vector < int > fileType;//	chứa index của file;
	unordered_map <char, Node*> children;
	// History ko có cái này
	int synonym_root;	// 0, 1, 2 … = hàng của từ đó -1;
	int operator_type;
	bool isStopword;

	void getString(string& s, Node* root);

	Node();
	Node(char _value, Node* _parent);
	Node(char _value, Node* _parent, int _synonym_root, int _operator_type, int _isStopword);

	bool isWord();
};


struct Trie {
	Node* root;
	vector < File > result;
	vector < Node* >  partial_results; 
	map <int, vector < Data >> numbers;
	// Vector pointer chỉ vào Node
	// dùng để tìm exact match
	// “tallest building”, “tallest * in the world“, ...
	Node* pNode;
	// dùng để recommend
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
	void insertTitle(string& title, int index);
	void insertExtension(string& extension, int index);
	void insertNumber(int num, int index, int position);
	Node* newNode(string& s);
	Node* search(string& s);	// run loop

	Trie();
};

struct Poro {	// save global variables
	Trie* search_trie;
	Trie* history_trie;

	vector < vector < Node* > > synonyms;
	vector < string > file_names;
	vector < string > recommendations;

	list < string > recent_search;
	string search_words;
	vector < int > invalids;
	int history_invalids;

	bool openQuotation;

	void resetData();
	void load_data(string indexfile);
	void processInput(char input);
	void processOutput();
	void recommend();
	// search history
	// called == 10^5 || found == 5 => return hết;

	Poro();

	vector <Data> searchSingleNumber(int number);
	vector <Data> searchRangeNumber(int number1, int number2);
};

struct UserInterface {
	void resizeConsole(int width, int height);
	void Nocursortype();
	void UnNocursortype();
	void txtColor(int color);
	void logo();
	void inputBoard();
	void input(Poro& PoroPoro);	// real-time input, mỗi ký tự input vào gọi hàm recommend()
	void keywordBoard();
	void straightLine();
	void backBorder();
	void subMenu(Poro& PoroPoro);
	void mainMenu(Poro& PoroPoro);
};