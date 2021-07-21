#include "Menu.h"


int main() {
	resizeConsole(1010, 600);
	int called = 0;
	int found = 0;
	char wordType[55];
	int size = 0;

	mainMenu(wordType, size);

	return 0;
}