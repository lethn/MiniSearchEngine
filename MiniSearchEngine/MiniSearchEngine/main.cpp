#include "Functions.h"


int main() {
	UserInterface UI;
	Poro PoroPoro;
	PoroPoro.load_data("index.txt");
	UI.resizeConsole(1010, 600);
	UI.mainMenu(PoroPoro);
	return 0;
}