#include "Functions.h"
void createUniqMap(unordered_map<int, bool> mapU)
{
	int c[14] = { '"',',','.','◼',')','(',':',';','“','”','—','-','_','\'' };
	for (int i = 0; i < 14; i++)
	{
		mapU[c[i]] = true;
	}
}
void Poro::load_data(string indexfile)
{
	unordered_map<int, bool> mapU;
	createUniqMap(mapU);
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
		int index = 1;
		while (!fin.eof())
		{

			string strtmp;
			string str = "";
			fin >> strtmp;
			for (int i = 0; i < strtmp.size(); i++)
			{
				if (mapU[strtmp[i]] || (strtmp[i] < 0 && strtmp[i] != -44))
				{
					continue;
				}
				str += tolower(strtmp[i]);
			}
			//insert(str, j, index);//j index file,index position
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
			if (mapU[strtmp[i]])
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

