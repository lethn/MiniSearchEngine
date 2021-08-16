#include "Struct.h"


int main() {
	UserInterface UI;
	Poro PoroPoro;

	UI.resizeConsole(1010, 600);
	UI.loadData(PoroPoro);
	
	/*
	system("cls");
	PoroPoro.search_trie->printData();
	system("pause");
	*/
	/*
	system("cls");
	ifstream fin("test.txt");
	while (!fin.eof()) {
		getline(fin, PoroPoro.search_words);
		auto st = chrono::steady_clock::now();
		PoroPoro.processOutput();
		auto ed = chrono::steady_clock::now();
		cout << chrono::duration<double, milli>(ed-st).count() << '\n';
	}
	fin.close();
	system("pause");
	*/
	UI.mainMenu(PoroPoro);
	return 0;
}