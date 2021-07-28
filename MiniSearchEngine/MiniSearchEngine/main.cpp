#include "Struct.h"


int main() {
	UserInterface UI;
	Poro PoroPoro;

	UI.resizeConsole(1010, 600);
	UI.loadData(PoroPoro);
	system("cls");
	PoroPoro.search_trie->printData();
	system("pause");
	system("cls");
	UI.mainMenu(PoroPoro);

	return 0;
}