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
		if (ch == ENTER && !search_words->empty()) { 
			/*gotoxy(X, Y + 2);
			cout << "                                    ";
			gotoxy(X, Y + 2);
			for (auto file : PoroPoro.search_trie->result) {
				cout << file.index << ' ';
			}
			system("pause");*/
			return;
		}
		
		if (tmp == (int) search_words->size()) continue;
		for (int j = 0; j < (int)recommendations->size(); ++j) {
			gotoxy(X, Y+2+j);
			for (int k = 0; k < SEARCH_SIZE_LIMIT; ++k) {
				cout << ' ';
			}
		}
		PoroPoro.recommend();
		if (recommendations->empty()) {
			gotoxy(X, Y+2);
			for (int k = 0; k < SEARCH_SIZE_LIMIT; ++k) {
				cout << ' ';
			}
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
	for (int i = 23; i < 119; ++i) {
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

void UserInterface::historyBorder() {
	txtColor(15);
	gotoxy(5, 4);
	cout << "HISTORY";

	gotoxy(4, 3);
	cout << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205);
	gotoxy(4, 5);
	cout << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205);

	gotoxy(3, 3);
	cout << char(201);
	gotoxy(3, 5);
	cout << char(200);

	gotoxy(13, 3);
	cout << char(187);
	gotoxy(13, 5);
	cout << char(188);

	gotoxy(3, 4);
	cout << char(186);
	gotoxy(13, 4);
	cout << char(186);

	int num = 1;
	for (int i = 6; i < 11; ++i) {
		gotoxy(2, i);
		cout << num << ".";
		num++;
	}
}

void UserInterface::showHistory(Poro& PoroPoro) {
	int x = 5, y = 6;
	for (auto itr : PoroPoro.recent_search) {
		gotoxy(x, y);
		if (itr.size() > 34) {
			for (int i = 0; i < 31; ++i)
				cout << itr[i];
			cout << "...";
		}
		else
			cout << itr;
		y++;
	}
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
	gotoxy(22, 06); cout << " Data 1 ";
	gotoxy(22, 11); cout << " Data 2 ";
	gotoxy(22, 16); cout << " Data 3 ";
	gotoxy(22, 21); cout << " Data 4 ";
	gotoxy(22, 26); cout << " Data 5 ";
	gotoxy(13, 32); cout << " BACK ";
	output(PoroPoro, keyword);

	int cnt = 0;
	while (true) {
		char choice = _getch();
		txtColor(15);
		gotoxy(22, 06); cout << " Data 1 ";
		gotoxy(22, 11); cout << " Data 2 ";
		gotoxy(22, 16); cout << " Data 3 ";
		gotoxy(22, 21); cout << " Data 4 ";
		gotoxy(22, 26); cout << " Data 5 ";
		gotoxy(13, 32); cout << " BACK ";

		if (choice == DOWN) {
			cnt++;
			if (cnt > 6)
				cnt = 1;
		}

		if (choice == UP) {
			cnt--;
			if (cnt < 1)
				cnt = 6;
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
				outputDetail(PoroPoro, cnt, keyword);
			}
		}
		if (cnt == 2) {
			txtColor(240);
			gotoxy(22, 11); cout << " Data 2 ";
			if (choice == ENTER)
			{
				outputDetail(PoroPoro, cnt, keyword);
			}
		}
		if (cnt == 3) {
			txtColor(240);
			gotoxy(22, 16); cout << " Data 3 ";
			if (choice == ENTER)
			{
				outputDetail(PoroPoro, cnt, keyword);
			}
		}
		if (cnt == 4) {
			txtColor(240);
			gotoxy(22, 21); cout << " Data 4 ";
			if (choice == ENTER)
			{
				outputDetail(PoroPoro, cnt, keyword);
			}
		}
		if (cnt == 5) {
			txtColor(240);
			gotoxy(22, 26); cout << " Data 5 ";
			if (choice == ENTER) {
				outputDetail(PoroPoro, cnt, keyword);
			}
		}
		if (cnt == 6) {
			txtColor(240);
			gotoxy(13, 32); cout << " BACK ";
			if (choice == ENTER) {
				PoroPoro.search_trie->result.clear();
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
	historyBorder();
	inputBoard();
	showHistory(PoroPoro);
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
//gotoxy(22, 06); cout << " Data 1 ";
void UserInterface::outputFileType(Poro&PoroPoro, vector< string > word)
{
	int index = 0;
	vector< string > fileName = PoroPoro.file_names;
	vector< File > result = PoroPoro.search_trie->result;
	int n = result.size();
	if (n > 5)
		n = 5;
	while (index < n)
	{
		int size = 0;
		gotoxy(32, 06 + 5 * index);
		txtColor(3);
		cout << fileName[result[index].index];
		txtColor(15);
		string str;
		fstream fout;
		fout.open((SOURCE + fileName[result[index].index]));
		gotoxy(23, 06 + 5 * index + 1);
		while (!fout.eof())
		{
			fout >> str;
			if (size / 100 == 3)
			{
				cout << "...";
				break;
			}
			if (size % 100 <= 20 && size > 20)
			{
				gotoxy(23, 06 + 5 * index + size / 100 + 1);
			}

			cout << str << " ";
			size += str.size() + 1;
		}
		fout.close();
		index++;
	}
	txtColor(3);
	while (index < 5)
	{
		gotoxy(32, 06 + 5 * index);
		cout << "CANNOT FIND " << word[0];
		index++;
	}
	txtColor(15);
}
void UserInterface::output(Poro& PoroPoro, string& keyword)
{
	UINT oldcp = GetConsoleOutputCP();
	// Set console code page to UTF-8 so console known how to interpret string data
	SetConsoleOutputCP(65001);
	int index = 0;
	set<int> syno_index;
	pair<int, int> num = { -1,-1 };
	vector< string > word = PoroPoro.words(keyword, syno_index, num);
	if (!word.empty() && (iequals(word[0], "filetype") || iequals(word[0], "intitle")))
	{
		outputFileType(PoroPoro,word);
	}
	else
	{
		vector< File > result = PoroPoro.search_trie->result;
		vector< string > fileName = PoroPoro.file_names;
		queue < string > q;
		int n = result.size();
		if (n > 5)
			n = 5;
		while (index < n)
		{
			int size = 3, line = 1;
			bool outputL = false;
			gotoxy(32, 06 + 5 * index);
			txtColor(3);
			cout << fileName[result[index].index];
			txtColor(15);
			gotoxy(23, 06 + 5 * index + 1); cout << "...";
			string str, tmpstr;
			fstream fout;
			fout.open((SOURCE + fileName[result[index].index]));

			while (!fout.eof())
			{
				fout >> str;
				if ((str.size() + size ) >= line * 95)
				{
					line++;
					if (line == 4)
					{
						cout << "...";
						break;
					}
					gotoxy(23, 06 + 5 * index + line);				
				}

				tmpstr = str;
				cutWord(tmpstr);
				if (checkSameWord(word, tmpstr) || PoroPoro.checkSynonyms(tmpstr,syno_index) || checkRangeNum(num,tmpstr))
				{
					if (!outputL)
					{
						outputL = true;
						while (q.size() > 5)
						{
							q.pop();
						}
						while (!q.empty())
						{
							cout << q.front() << " ";
							size += q.front().size();
							q.pop();
						}
					}
					txtColor(4);
				}
				if (!outputL)
					q.push(str);
				if (outputL)
					cout << str;
				if (checkSameWord(word, tmpstr) || PoroPoro.checkSynonyms(tmpstr, syno_index) || checkRangeNum(num, tmpstr))
				{
					txtColor(15);
				}
				if (outputL)
				{
					cout << " ";
					size += str.size() + 1;
				}

			}
			fout.close();
			index++;
		}
		txtColor(3);
		while (index < 5)
		{
			gotoxy(32, 06 + 5 * index);
			cout << "CANNOT FIND " << keyword;
			index++;
		}
		txtColor(15);
	}
	SetConsoleOutputCP(oldcp);
}

void UserInterface::outputDetail(Poro& PoroPoro, int index, string keyword)
{
	txtColor(0);
	system("cls");
	UINT oldcp = GetConsoleOutputCP();
	// Set console code page to UTF-8 so console known how to interpret string data	
	vector< File > result = PoroPoro.search_trie->result;
	vector< string > fileName = PoroPoro.file_names;
	int n = result.size();
	if (n > 5)
		n = 5;
	if (index <= n)
	{
		SetConsoleOutputCP(65001);
		int size = 0;
		gotoxy(13, 1);
		txtColor(3);
		cout << "DATA " << index << " : " << fileName[result[index - 1].index] << "   |   SEARCH: " << keyword << endl;
		txtColor(15);
		string str;
		fstream fout;
		fout.open((SOURCE + fileName[result[index - 1].index]));
		gotoxy(8, 04 + size / 110);
		while (!fout.eof())
		{
			getline(fout, str);
			if (str.size() <= 110)
			{
				cout << str;
				size += 110;
				gotoxy(8, 04 + size / 110);
			}
			else
			{
				int i = 0, tmp = str.size();
				while (i < tmp)
				{
					cout << str[i];

					i++;
					size++;
					if (i % 110 == 0)
					{	
						while (i < tmp && str[i] != SPACE)
						{
							cout << str[i];
							i++;
							size++;
						}
						i++;
						gotoxy(8, 04 + size / 110);
					}
				}
			}
		}
		fout.close();
		SetConsoleOutputCP(oldcp);
		borderOutput(size);
		
	}
	else
	{
		txtColor(3);
		gotoxy(15, 1);
		cout << "DATA NOT EXIST";
		txtColor(15);
		borderOutput(3);
		cout << endl;
	}
	gotoxy(0, 0);
	_getch();
	subMenu(PoroPoro);
}
void UserInterface::borderOutput(int size)
{
	int left = 5,right = 129;
	for (int i = 0; i <= size / 110 + 7; i++)
	{
		gotoxy(left, i);
		if (i == 3)
		{
			cout << char(204);
		}
		else
		{
			cout << char(186);
		}
		gotoxy(right, i);
		if (i == 3)
		{
			cout << char(185);
		}
		else
		{
			cout << char(186);
		}
	}
	gotoxy(left + 1, 03);
	for (int i = 0; i < right - left - 1; i++)
		cout << char(205);
	gotoxy(left, 3);
	gotoxy(left, 07 + size / 110);
	cout << char(200);
	gotoxy(left + 1, 07 + size / 110);
	for (int i = 0; i < right - left - 1; i++)
		cout << char(205);
	cout << char(188);


	gotoxy(13, 8 + size / 110);
	cout << char(205) << char(205) << char(205) << char(205) << char(205) << char(205);
	gotoxy(13, 10 + size / 110);
	cout << char(205) << char(205) << char(205) << char(205) << char(205) << char(205);

	gotoxy(12, 8 + size / 110);
	cout << char(201);
	gotoxy(12, 10 + size / 110);
	cout << char(200);

	gotoxy(19, 8 + size / 110);
	cout << char(187);
	gotoxy(19, 10 + size / 110);
	cout << char(188);

	gotoxy(12, 9 + size / 110);
	cout << char(186);
	gotoxy(19, 9 + size / 110);
	cout << char(186);
	txtColor(240);
	gotoxy(14, 9 + size / 110);
	cout << "BACK";
	txtColor(15);
}