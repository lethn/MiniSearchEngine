#include "Struct.h"

void UserInterface::resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void UserInterface::Nocursortype() {
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void UserInterface::UnNocursortype() {
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void UserInterface::txtColor(int color) {
	HANDLE hConsoleColor;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void UserInterface::logo() {
	txtColor(15);
	gotoxy(48, 4);	cout << " _______  _______  ______    _______ " << endl;
	gotoxy(48, 5);	cout << "|       ||       ||    _ |  |       |" << endl;
	gotoxy(48, 6);	cout << "|    _  ||   _   ||   | ||  |   _   |" << endl;
	gotoxy(48, 7);	cout << "|   |_| ||  | |  ||   |_||_ |  | |  |" << endl;
	gotoxy(48, 8);	cout << "|    ___||  |_|  ||    __  ||  |_|  |" << endl;
	gotoxy(48, 9);	cout << "|   |    |       ||   |  | ||       |" << endl;
	gotoxy(48, 10);	cout << "|___|    |_______||___|  |_||_______|" << endl;

	gotoxy(40, 2);
	for (int i = 0; i < 53; ++i)
		cout << char(220);
	gotoxy(43, 3);
	for (int i = 0; i < 48; ++i)
		cout << char(205);
	gotoxy(43, 12);
	for (int i = 0; i < 48; ++i)
		cout << char(205);
	gotoxy(40, 13);
	for (int i = 0; i < 53; ++i)
		cout << char(223);

	gotoxy(42, 3);
	cout << char(201);
	gotoxy(42, 12);
	cout << char(200);

	gotoxy(90, 3);
	cout << char(187);
	gotoxy(90, 12);
	cout << char(188);

	for (int i = 4; i < 12; ++i)
	{
		gotoxy(42, i);
		cout << char(186);
	}
	for (int i = 4; i < 12; ++i)
	{
		gotoxy(90, i);
		cout << char(186);
	}
	for (int i = 3; i < 13; ++i)
	{
		gotoxy(40, i);
		cout << char(219);
	}
	for (int i = 3; i < 13; ++i)
	{
		gotoxy(92, i);
		cout << char(219);
	}
}

void UserInterface::inputBoard() {
	txtColor(15);
	// Search Board
	gotoxy(34, 19);
	cout << "Type here: ";
	gotoxy(34, 21);
	cout << "Recommend: ";
	gotoxy(33, 18);
	for (int i = 0; i < 68; ++i)
		cout << char(205);

	gotoxy(33, 20);
	for (int i = 0; i < 68; ++i)
		cout << char(205);

	gotoxy(32, 18);
	cout << char(201);
	gotoxy(32, 20);
	cout << char(200);

	gotoxy(101, 18);
	cout << char(187);
	gotoxy(101, 20);
	cout << char(188);

	gotoxy(32, 19);
	cout << char(186);
	gotoxy(101, 19);
	cout << char(186);

	// Poro Search Board
	gotoxy(61, 16);
	cout << "PORO SEARCH";
	gotoxy(60, 15);
	for (int i = 0; i < 13; ++i)
		cout << char(205);

	gotoxy(60, 17);
	for (int i = 0; i < 13; ++i)
		cout << char(205);

	gotoxy(59, 15);
	cout << char(201);
	gotoxy(59, 17);
	cout << char(200);

	gotoxy(73, 15);
	cout << char(187);
	gotoxy(73, 17);
	cout << char(188);

	gotoxy(59, 16);
	cout << char(186);
	gotoxy(73, 16);
	cout << char(186);
}

void UserInterface::input(Poro& PoroPoro) {
	char ch;
	const int X = 45, Y = 19;
	PoroPoro.resetData();
	PoroPoro.search_trie->root->value = 'R';
	string* search_words = &PoroPoro.search_words;
	vector < string >* recommendations = &PoroPoro.recommendations;
	gotoxy(X, Y);
	int i = 0;
	while (true) {
		i = 1;
		gotoxy(X + search_words->size(), Y);
		ch = _getch();
		if (ch == ESC){
			exit(0);
		}
		int tmp = search_words->size();
		PoroPoro.processInput(ch);
		if (ch == ENTER) { 
			gotoxy(X, Y+2);
			cout << "                                    ";
			for (auto file : PoroPoro.search_trie->result) {
				gotoxy(X, Y+2);
				cout << file.index << ' ';
			}
			system("pause");
			return;
		}
		
		if (tmp == (int) search_words->size()) continue;
		for (int j = 0; j < (int)recommendations->size(); ++j) {
			gotoxy(X, Y+2+j);
			cout << "                                        ";
		}
		PoroPoro.recommend();
		if (recommendations->empty()) {
			gotoxy(X, Y+2);
			cout << (*search_words);
		}
		for (int j = 0; j < (int) recommendations->size(); ++j) {			
			gotoxy(X, Y+2+j);
			cout << (*search_words);
			cout << (*recommendations)[j];
		}
	}
}

void UserInterface::keywordBoard() {
	txtColor(15);
	gotoxy(34, 3);
	cout << "Keyword:";

	gotoxy(33, 2);
	for (int i = 0; i < 68; ++i)
		cout << char(205);

	gotoxy(33, 4);
	for (int i = 0; i < 68; ++i)
		cout << char(205);

	gotoxy(32, 2);
	cout << char(201);
	gotoxy(32, 4);
	cout << char(200);

	gotoxy(101, 2);
	cout << char(187);
	gotoxy(101, 4);
	cout << char(188);

	gotoxy(32, 3);
	cout << char(186);
	gotoxy(101, 3);
	cout << char(186);
}

void UserInterface::straightLine() {
	txtColor(15);
	for (int i = 6; i < 30; ++i) {
		gotoxy(15, i);
		cout << char(219);
	}
	for (int i = 23; i < 112; ++i) {
		gotoxy(i, 32);
		cout << char(220);
	}
}

void UserInterface::backBorder() {
	txtColor(15);
	gotoxy(14, 32);
	cout << "BACK";

	gotoxy(13, 31);
	cout << char(205) << char(205) << char(205) << char(205) << char(205) << char(205);
	gotoxy(13, 33);
	cout << char(205) << char(205) << char(205) << char(205) << char(205) << char(205);

	gotoxy(12, 31);
	cout << char(201);
	gotoxy(12, 33);
	cout << char(200);

	gotoxy(19, 31);
	cout << char(187);
	gotoxy(19, 33);
	cout << char(188);

	gotoxy(12, 32);
	cout << char(186);
	gotoxy(19, 32);
	cout << char(186);
}

void UserInterface::subMenu(Poro& PoroPoro) {
	system("cls");
	Nocursortype();
	keywordBoard();
	string keyword = PoroPoro.search_words;
	gotoxy(43, 3); cout << keyword;
	straightLine();
	backBorder();

	txtColor(15);
	gotoxy(22, 6); cout << " Data 1 ";
	gotoxy(22, 11); cout << " Data 2 ";
	gotoxy(22, 16); cout << " Data 3 ";
	gotoxy(22, 21); cout << " Data 4 ";
	gotoxy(22, 26); cout << " Data 5 ";
	gotoxy(13, 32); cout << " BACK ";

	int cnt = 0;
	while (true) {
		char choice = _getch();
		txtColor(15);
		gotoxy(22, 6); cout << " Data 1 ";
		gotoxy(22, 11); cout << " Data 2 ";
		gotoxy(22, 16); cout << " Data 3 ";
		gotoxy(22, 21); cout << " Data 4 ";
		gotoxy(22, 26); cout << " Data 5 ";
		gotoxy(13, 32); cout << " BACK ";

		if (choice == DOWN) {

		}

		if (choice == UP) {

		}

		if (choice == ESC) {
			system("cls");
			exit(0);
		}

		if (cnt == 1) {
			txtColor(240);
			gotoxy(22, 6); cout << " Data 1 ";
			if (choice == ENTER)
			{

			}
		}
		if (cnt == 2) {
			txtColor(240);
			gotoxy(22, 11); cout << " Data 2 ";
			if (choice == ENTER)
			{

			}
		}
		if (cnt == 3) {
			txtColor(240);
			gotoxy(22, 16); cout << " Data 3 ";
			if (choice == ENTER)
			{
			}
		}
		if (cnt == 4) {
			txtColor(240);
			gotoxy(22, 21); cout << " Data 4 ";
			if (choice == ENTER)
			{

			}
		}
		if (cnt == 5) {
			txtColor(240);
			gotoxy(22, 26); cout << " Data 5 ";
			if (choice == ENTER) {

			}
		}
		if (cnt == 6) {
			txtColor(240);
			gotoxy(13, 32); cout << " BACK ";
			if (choice == ENTER) {
				mainMenu(PoroPoro);
			}
		}
	}

}

void UserInterface::mainMenu(Poro& PoroPoro) {
	txtColor(15);
	system("cls");
	UnNocursortype();
	logo();
	inputBoard();
	input(PoroPoro);
	subMenu(PoroPoro);
}

void UserInterface::loadData(Poro& PoroPoro) {
	Nocursortype();
	txtColor(15);
	gotoxy(43, 11);
	for (int i = 0; i < 47; ++i)
		cout << char(205);

	gotoxy(43, 19);
	for (int i = 0; i < 47; ++i)
		cout << char(205);

	gotoxy(42, 11);
	cout << char(201);
	gotoxy(42, 19);
	cout << char(200);

	gotoxy(90, 11);
	cout << char(187);
	gotoxy(90, 19);
	cout << char(188);

	for (int i = 12; i < 19; ++i) {
		gotoxy(42, i);
		cout << char(186);
		gotoxy(90, i);
		cout << char(186);
	}

	gotoxy(51, 13);
	cout << ">>  L O A D I N G   D A T A  <<";
	gotoxy(60, 15);
	cout << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254) << "  " << char(254);

	clock_t begin, end;
	begin = clock();
	PoroPoro.load_data("index.txt");
	end = clock();

	gotoxy(57, 15);
	cout << "Loading time: ";
	gotoxy(71, 15);
	cout << (float)(end - begin) / CLOCKS_PER_SEC << "s" << endl;
	gotoxy(52, 17);
	cout << "Press any key to continue ...";
	_getch();
}