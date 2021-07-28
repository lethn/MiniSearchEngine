#include "Functions.h"


int main() {
	UserInterface UI;
	Poro PoroPoro;

	UI.resizeConsole(1010, 600);
	UI.loadData(PoroPoro);
	UI.mainMenu(PoroPoro);

	return 0;
}