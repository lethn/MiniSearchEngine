#include "Library.h"

/*
Normal Search Ranking:
	Exact Match
	AND
	OR
  Exact Match Search Ranking: Sort theo số lần xuất hiện chung của cả 2 trong file
  AND Search Ranking: Sort theo tổng số lần xuất hiện của cả 2 trong file
  OR Search Ranking: Sort theo tổng số lần xuất hiện của cả 2 trong file
*/

struct Data {
	int index;
	vector <int> positions;

	Data();
	Data(int _index);
	Data(int _index, int _pos);
	Data(int _index, vector < int >& _positions);
};

struct File{
	int index;
	int noExacts; 	// number of exact matches
	int noMatches;	// number of matches

	File();
	File(int _index);
	File(int _index, int _noExacts, int _noMatches);
	File(Data& A, bool exact);

	bool operator< (int& _index);
	bool operator> (int& _index);
	bool operator==(int& _index);
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

	string getString(Node* root);

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
	void insertData(string& s, vector < File >& V);
	void insertTitle(string& title, int index);
	void insertExtension(string& extension, int index);
	void insertNumber(int num, int index, int position);
	Node* newNode(string& s);
	Node* search(string& s);	// run loop
	Node* protected_search(string& s);
	void printData();
	// debugging purposes

	Trie();
};

struct Poro {	// save global variables
	Trie* search_trie;
	Trie* history_trie;

	vector < vector < Data > > synonyms;
	vector < string > file_names;
	vector < string > recommendations;
	unordered_map<int, vector<int>> posData;
	list < string > recent_search;
	string search_words;
	vector < int > invalids;
	int history_invalids;

	bool openQuotation;

	void resetData();
	void load_data(string indexfile);
	void load_file(string indexfile);
	void load_synonyms(string indexfile);
	void load_stopWord(string indexfile);
	void processInput(char input);
	void processOutput();
	void recommend();
	// search history
	// called == 10^5 || found == 5 => return hết;

	vector < File > operatorIntitle(string s);
	vector < File > operatorFiletype(string s);
	vector < vector < Data > > processString(string s);
	vector < Data > StringtoData(string& s);
	vector < Data > processParenthesis(string s);
	vector < Data > processExactmatch(string s);
	vector < vector < Data > > processOperations(vector < vector < Data > >& V);
	vector < Data > searchSingleNumber(int number);
	vector < Data > searchRangeNumber(int number1, int number2);
	vector < Data > combineData(vector < vector < Data > >& V);
	vector < File > updateResult(vector < vector < Data > > V);
	Poro();
	~Poro();
};

struct UserInterface {
	void resizeConsole(int width, int height);
	void Nocursortype();
	void UnNocursortype();
	void txtColor(int color);
	void logo();
	void inputBoard();
	void input(Poro& PoroPoro);	// real-time input, mỗi ký tự input vào gọi hàm recommend()
	void output(Poro& PoroPoro, string& keyword);
	void outputDetail(Poro& PoroPoro, int index, string keyword);
	void outputFileType(Poro& PoroPoro);
	void borderOutput(int size);
	void keywordBoard();
	void straightLine();
	void backBorder();
	void historyBorder();
	void showHistory(Poro& PoroPoro);
	void subMenu(Poro& PoroPoro);
	void mainMenu(Poro& PoroPoro);
	void loadData(Poro& PoroPoro);
};

bool CompareFiles(File& A, File& B);		// dùng cho hàm sort();
vector < File > CombineDatatoFile(vector < Data >& A, vector < Data >& B);
vector < Data > AND_Data(vector < Data >& A, vector < Data >& B);
vector < Data > OR_Data(vector < Data >& A, vector < Data >& B);
vector < int > AND_int(vector < int >& A, vector < int >& B, int d);
vector < int > OR_int(vector < int >& A, vector < int >& B);
vector < Data > EXACT_MATCHES(vector < Data >& A, vector < Data >& B, int d);
vector < Data > EXCEPT(vector < Data >& A, vector < Data >& B);
vector < File > OR_File(vector < File >& A, vector < int >& B);
void search_recommendations(vector < string >& recommendations, Node* pCur, string& s, int& called, int& found);
void gotoxy(int x, int y);
string convertToString(char* a, int size);
int getDistance(ii& A);
vector < ii > findParenthesis(string& s);
vector < ii > findQuotation(string& s);
void lowerString(string& s);
bool isOperation(vector < Data >& V);
void dfs(Node* u, Node* root);
bool isStopword(string& s, Trie& trie);
vector<string> words(string& keyWord);
bool checkSameWord(vector<string> word, string& str);
bool iequals(const string& a, const string& b);
void cutWord(string& a);


