#include "Struct.h"

void Poro::load_data(string indexfile)
{
	string synonyms = "Synonyms.txt", stopword = "Stopwords.txt";
	load_oldData("search_trie.bin");
	load_file(indexfile);
	load_synonyms(synonyms);
	load_stopWord(stopword);
}

void Poro::load_oldData(string filename) {
	ifstream fin(filename, ios::binary);
	if (!fin.is_open()) return;
	system("cls");
	int n;
	fin.read((char *) &n, 4);
	string s;
	for (int i = 0; i < n; ++i) {
		int m;
		fin.read((char *) &m, 4);
		s.resize(m);
		fin.read((char *) &s[0], m);
		s.pop_back();
		file_names.push_back(s);
	}
	while (true) {
		int m;
		fin.read((char *) &m, 4);
		if (fin.eof()) break;
		s.resize(m);
		fin.read((char *) &s[0], m);
		s.pop_back();
		Node* node = search_trie->newNode(s);
		fin.read((char *) &node->synonym_root, 4);
		fin.read((char *) &node->isStopword, sizeof(bool));
		fin.read((char *) &n, 4);
		for (int i = 0; i < n; ++i) {
			int index, num_occur;
			fin.read((char *) &index, 4);
			fin.read((char *) &num_occur, 4);
			node->files.push_back(Data(index));
			node->files.back().positions.resize(num_occur);
			if (num_occur) fin.read((char *) &node->files.back().positions[0], num_occur<<2);
		}
		fin.read((char *) &n, 4);
		node->inTitle.resize(n);
		if (n) fin.read((char *) &node->inTitle[0], n<<2);
		fin.read((char *) &n, 4);
		node->fileType.resize(n);
		if (n) fin.read((char *) &node->fileType[0], n<<2);
	}
	fin.close();
}

void Poro::load_file(string indexfile)
{
	ifstream file;
	file.open(SOURCE + indexfile);
	string tmp;
	int j = 0;
	bool newfile = false;
	while (!file.eof())
	{
		// load file
		getline(file, tmp);
		if (j < file_names.size()) {
			++j;
			continue;
		}
		newfile = true;
		file_names.push_back(tmp);
		ifstream fin;
		fin.open(SOURCE + tmp);
		if (fin.fail())
		{
			fin.close();
			j++;
			continue;
		}
		int index = 0;
		// load titles and extension
		string title = "", extension = "";
		for (int i = 0; i < tmp.size(); i++)
		{
			if (tmp[i] == SPACE || tmp[i] == '.')
			{
				search_trie->insertTitle(title, j);
				title = "";
				if (tmp[i] == '.')
					break;
				continue;
			}
			if (special_characters.find(tmp[i]) != special_characters.end() || (tmp[i] < 0 && tmp[i] != -44))
			{
				continue;
			}
			title += tolower(tmp[i]);
		}
		/*string tmptitle;
		getline(fin, tmptitle);
		for (int i = 0; i < tmptitle.size(); i++)
		{
			if (tmptitle[i] == SPACE)
			{
				search_trie->insertTitle(title, j);
				title = "";
				continue;
			}
			if (special_characters.find(tmptitle[i]) != special_characters.end() || (tmptitle[i] < 0 && tmptitle[i] != -44))
			{
				continue;
			}
			title += tolower(tmptitle[i]);
		}*/
		search_trie->insertTitle(title, j);
		for (int i = tmp.size() - 1; i > -1; i--)
		{
			if (tmp[i] == '.')
				break;
			extension += tolower(tmp[i]);
		}
		for (int i = 0; i < extension.size() / 2; i++)
		{
			swap(extension[i], extension[extension.size() - 1 - i]);
		}
		search_trie->insertExtension(extension, j);
		while (!fin.eof())
		{
			string strtmp;
			string str = "";
			string num = "";
			fin >> strtmp;
			for (int i = 0; i < strtmp.size(); i++)
			{
				if (special_characters.find(strtmp[i]) != special_characters.end() || (strtmp[i] < 0 && strtmp[i] != -44))
				{
					continue;
				}
				if (strtmp[i] >= '0' && strtmp[i] <= '9')
					num += strtmp[i];
				str += tolower(strtmp[i]);
			}
			if (num != "") search_trie->insertNumber(stoi(num), j, index);
			if (str != "") search_trie->insert(str, j, index);
			index++;
		}
		j++;
		fin.close();
	}
	if (newfile) exportData("search_trie.bin");
	file.close();
}
void Poro::load_synonyms(string indexfile)
{
	ifstream fin;
	fin.open(SOURCE + indexfile);
	string str;
	int i = 0;
	while (!fin.eof())
	{
		getline(fin, str, '\n');
		string strtmp = "";
		vector<Data> newVec;
		for (int j = 0; j < str.size(); j++)
		{
			if (str[j] == ',' || str[j] == '\n')
			{
				Node* searchTmp = search_trie->search(strtmp);
				if (searchTmp != nullptr)
				{
					searchTmp->synonym_root = i;
					newVec = OR_Data(newVec, searchTmp->files);
				}
				j++;
				strtmp = "";
			}
			else if (str[j] == ' ')
			{
				continue;
			}
			else
			{
				strtmp += str[j];
			}
		}
		synonyms.push_back(newVec);
		i++;
	}
	fin.close();
}

void Poro::load_stopWord(string indexfile)
{
	ifstream fin;
	fin.open(SOURCE + indexfile);
	string strtmp;
	while (!fin.eof())
	{
		fin >> strtmp;
		string str = "";
		for (int i = 0; i < strtmp.size(); i++)
		{
			if (special_characters.find(strtmp[i]) != special_characters.end())
				continue;
			else
				str += strtmp[i];
		}
		Node* searchTmp = Poro::search_trie->search(str);
		if (searchTmp != nullptr)
		{
			searchTmp->isStopword = true;
		}
	}
	fin.close();
}