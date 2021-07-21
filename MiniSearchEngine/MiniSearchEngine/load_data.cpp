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
	Poro poro;
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
		poro.file_names.push_back(tmp);
		ifstream fout;
		fout.open("source\\" + tmp);
		if (fout.fail())
		{
			fout.close();
			continue;
		}
		int i = 1;
		while (!fout.eof())
		{

			string strtmp;
			string str = "";
			fout >> strtmp;
			for (int i = 0; i < strtmp.size(); i++)
			{
				if (mapU[strtmp[i]] || (strtmp[i] < 0 && strtmp[i] != -44))
				{
					continue;
				}
				str += towlower(strtmp[i]);
			}
			//insert(str, j, i);/j index file,i//position
			i++;
		}
		j++;
		fout.close();
		cout << endl;
	}
	file.close();
	ifstream fout;
	fout.open("Synonyms.txt");
	string str;
	int i = 1;
	cout << i << " ";
	while (!fout.eof())
	{
		getline(fout, str, '\n');
		string strtmp = "";
		for (int j = 0; j < str.size(); j++)
		{
			if (str[j] == ',' || str[j] == '\n')
			{
				//Node* searchTmp = search_trie->root.search(strtmp);
				//if (searchTmp != nullptr)
				//{
				//	searchTmp->synonym_root = i;
				//	synonyms[i].push_back(searchTmp);
				//}
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
		i++;
	}
	fout.close();
	fout.open("Stopwords.txt");
	string strtmp;
	while (!fout.eof())
	{
		fout >> strtmp;
		string str = "";
		for (int i = 0; i < strtmp.size(); i++)
		{
			if (mapU[strtmp[i]])
				continue;
			else
				str += strtmp[i];
		}
		//Node* searchTmp = search_trie->root.search(str);
			//if (searchTmp != nullptr)
			//{
			//	searchTmp->isStopWord = true;
			//}
	}
	fout.close();
}
