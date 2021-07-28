#include "Functions.h"

void Poro::load_data(string indexfile)
{

	ifstream file;
	file.open("source\\" + indexfile);
	string tmp;
	int j = 0;
	while (!file.eof())
	{
		// load file
		getline(file, tmp);
		cout << "data: " + tmp << endl;
		Poro::file_names.push_back(tmp);
		ifstream fin;
		fin.open("source\\" + tmp);
		if (fin.fail())
		{
			fin.close();
			continue;
		}
		int index = 0;
		while (!fin.eof())
		{
			// load word in file
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
			search_trie->insert(str, j, index);
			index++;
		}
		// load titles and extension
		string title = "", extension = "";
		for (int i = 0; i < tmp.size(); i++)
		{
			if (tmp[i] == '.')
			{
				search_trie->insertTitle(title,j);
				break;
			}
			if (tmp[i] == SPACE)
			{
				search_trie->insertTitle(title,j);
				title = "";
				continue;
			}
			if (special_characters.find(tmp[i]) != special_characters.end() || (tmp[i] < 0 && tmp[i] != -44))
			{
				continue;
			}
			title += tolower(tmp[i]);
		}
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
		search_trie->insertExtension(extension,j);
		j++;
		fin.close();
		cout << endl;
	}
	file.close();
	ifstream fin;
	// load synonyms
	fin.open("source\\Synonyms.txt");
	string str;
	int i = 1;
	while (!fin.eof())
	{
		getline(fin, str, '\n');
		string strtmp = "";
		vector<Node*> newVec;
		for (int j = 0; j < str.size(); j++)
		{
			if (str[j] == ',' || str[j] == '\n')
			{
				Node* searchTmp = Poro::search_trie->search(strtmp);
				if (searchTmp != nullptr)
				{
					searchTmp->synonym_root = i;
					newVec.push_back(searchTmp);
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
		Poro::synonyms.push_back(newVec);
		i++;
	}
	fin.close();
	//load stopword
	fin.open("source\\Stopwords.txt");
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
	cout << "success" << endl;
}

