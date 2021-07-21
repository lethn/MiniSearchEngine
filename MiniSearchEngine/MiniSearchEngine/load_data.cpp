#include "Functions.h"

void Poro::load_data(string indexfile)
{

	ifstream file;
	file.open("source\\" + indexfile);
	string tmp;
	int j = 0;
	while (!file.eof())
	{
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

			string strtmp;
			string str = "";
			fin >> strtmp;
			for (int i = 0; i < strtmp.size(); i++)
			{
				if (special_characters.find(strtmp[i]) != special_characters.end() || (strtmp[i] < 0 && strtmp[i] != -44))
				{
					continue;
				}
				str += tolower(strtmp[i]);
			}
			Poro::search_trie->insert(str, j, index);
			index++;
		}
		j++;
		fin.close();
		cout << endl;
	}
	file.close();
	ifstream fin;
	fin.open("Synonyms.txt");
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
				Node* searchTmp = search_trie->search(strtmp);
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
	fin.open("Stopwords.txt");
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
		Node* searchTmp = search_trie->search(str);
		if (searchTmp != nullptr)
		{
			searchTmp->isStopword = true;
		}
	}
	fin.close();
}

