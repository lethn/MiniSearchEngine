#include "Struct.h"

void search_recommendations(vector < string >& recommendations, 
	Node* pCur, string& s, int& called, int& found){
	if (pCur == nullptr) return;
	if (pCur->isWord()) {
		recommendations.push_back(s);
		++found;
		if (called > CALL_LIMIT || found > NUM_OF_RECOMMENDATIONS) return;
	}
	for (auto child : pCur->children) {
		s.push_back(child.first);
		search_recommendations(recommendations, child.second, s, ++called, found);
		s.pop_back();
		if (called > CALL_LIMIT || found > NUM_OF_RECOMMENDATIONS) return;
	}
}

void Poro::recommend() {
	int called = 0, found = 0;
	string s = "";
	recommendations.empty();
	if (!history_invalids)
		search_recommendations(recommendations, history_trie->pNode, s, called, found);
	if (called > CALL_LIMIT || found > NUM_OF_RECOMMENDATIONS) return;
	if (!invalids.back())
		search_recommendations(recommendations, search_trie->pNode, s, called, found);
}

void Poro::processInput(char input) {
	switch (input) {
	case ENTER: {
		processOutput();
		history_trie->insertData(search_words, search_trie->result);
		break;
	}
	case BACKSPACE: {
		if (search_words.empty()) return;
		if (search_words.back() == QUOTATION) openQuotation ^= 1;
		search_words.pop_back();
		cout << "\b \b";

		if (invalids.back() > 0) --invalids.back();
		else if (search_trie->pNode == search_trie->root){
			if (invalids.size() > 1)
				invalids.pop_back();
			search_trie->partial_results.pop_back();
			if (search_trie->partial_results.empty())
				search_trie->pNode = search_trie->root;
			else search_trie->pNode = search_trie->partial_results.back();
		}
		else search_trie->pNode = search_trie->pNode->parent;

		if (history_invalids > 0) --history_invalids;
		else history_trie->pNode = history_trie->pNode->parent;
		break;
	}
	default: {
		if (search_words.size() >= SEARCH_SIZE_LIMIT) return;
		search_words.push_back(input);
		cout << input;
		if	(input == SPACE || input == OPEN_PARENTHESIS || 
			input == QUOTATION){
			if (input == QUOTATION) openQuotation ^= 1;
			search_trie->partial_results.push_back(search_trie->pNode);
			search_trie->pNode = search_trie->root;
			invalids.push_back(0);
		}
		else {
			if (search_trie->pNode->children.count(input)) {
				search_trie->pNode = search_trie->pNode->children[input];
			}
			else ++invalids.back();
		}
		if (history_trie->pNode->children.count(input)) {
			history_trie->pNode = history_trie->pNode->children[input];
		}
		else ++history_invalids;
		break;
		}
	}
}

void Poro::resetData(){
	recommendations.clear();
	invalids.clear();
	history_invalids = 0;
	openQuotation = false;
}

void Poro::processOutput() {
	if (search_words.empty()) return;
	int n = search_words.size();
	if (n >= INTITLE_SIZE && search_words.compare(0, INTITLE_SIZE, INTITLE) == 0) {
		search_trie->result = operatorIntitle(
			search_words.substr(INTITLE_SIZE, n - INTITLE_SIZE)
		);
		return;
	}
	if (n >= FILETYPE_SIZE && search_words.compare(0, FILETYPE_SIZE, FILETYPE) == 0) {
		search_trie->result = operatorFiletype(
			search_words.substr(FILETYPE_SIZE, n - FILETYPE_SIZE)
		);
		return;
	}
	search_trie->result = updateResult(processString(search_words));
}

vector < File > Poro::updateResult(vector < vector < Data > > V) {
	vector < File > result;
	vector < vector < Data > > preProcess = processOperations(V);
	if (preProcess.empty()) return result;
	int n = preProcess.size();
	vector < Data > exact_match = preProcess[0];
	vector < Data > matches = preProcess[0];
	int d = 1;
	for(int i = 1; i < n; ++i, ++d){
		exact_match = EXACT_MATCHES(exact_match, preProcess[i], d);
	}
	unordered_map < int, File > Map;
	for (auto& files : exact_match) {
		File A(files, true);
		Map.insert(make_pair(files.index, A));
	}
	for (int i = 1; i < n; ++i) {
		matches = AND_Data(matches, preProcess[i]);
	}
	for (auto& files : matches) {
		auto itr = Map.find(files.index);
		if (itr == Map.end()) {
			File A(files, false);
			Map.insert(make_pair(files.index, A));
		}
		else {
			itr->second.noMatches = files.positions.size();
		}
	}
	for (auto& files : Map) {
		result.push_back(files.second);
	}
	sort(result.begin(), result.end(), CompareFiles);
	return result;
}

vector < File > Poro::operatorIntitle(string s) {
	stringstream ss(s);
	vector < File > result;
	string word;
	while (ss >> word) {
		lowerString(word);
		Node* node = search_trie->search(word);
		if (!node) continue;
		result = OR_File(result, node->inTitle);
	}
	return result;
}

vector < File > Poro::operatorFiletype(string s) {
	stringstream ss(s);
	vector < File > result;
	string word;
	while (ss >> word) {
		if (word.empty()) continue;
		lowerString(word);
		Node* node = search_trie->search(word);
		if (!node) continue;
		result = OR_File(result, node->fileType);
	}
	return result;
}

vector < vector < Data > > Poro::processString(string s) {
	if (s.empty()) return vector < vector < Data > > ();
	vector < ii > parenthesis = findParenthesis(s);
	vector < ii > quotations = findQuotation(s);
	vector < vector < Data > > result;
	string word;
	int k = 0, h = 0;
	int N = s.size();
	int n = parenthesis.size();
	int m = quotations.size();
	for (int i = 0; i < N; ++i) {
		if (s[i] == SPACE || s[i] == FULL_STOP) {
			if (!word.empty()){
				result.push_back(StringtoData(word));
				word.clear();
			}
		}
		else if (s[i] == OPEN_PARENTHESIS &&  k < n && parenthesis[k].first == i) {
			if (!word.empty()){
				result.push_back(StringtoData(word));
				word.clear();
			}
			result.push_back(processParenthesis(
				s.substr(i+1, getDistance(parenthesis[k])-1))
			);
			i = parenthesis[k].second; // jump to the close
			++k;
		}
		else if (s[i] == QUOTATION && h < m && quotations[h].first == i){
			if (!word.empty()){
				result.push_back(StringtoData(word));
				word.clear();
			}
			result.push_back(processExactmatch(
				s.substr(i+1, getDistance(quotations[h])-1))
			);
			i = quotations[h].second; // jump to the close
			++h;
		}
		else if (s[i] == MINUS && word.empty() && i + 1 < N && s[i + 1] != SPACE) {
			if (!result.empty() && (result.back().empty() || result.back().back().index >= 0)){
				result.push_back(vector < Data > (1, Data(-3)));
			}
		}
		else if (s[i] == DOLLAR && word.empty()) {
			string number_string;
			int j = i + 1;
			for (; j < N && s[j] >= '0' && s[j] <= '9'; ++j) {
				number_string.push_back(s[j]);
			}
			if (number_string.empty()) {
				word.push_back(s[i]);
				continue;
			}
			int number1 = stoi(number_string);
			int number2 = -1;
			if (j < N && j + 1 < N && j + 2 < N &&
				s[j] == FULL_STOP && s[j + 1] == FULL_STOP && s[j + 2] == DOLLAR) {
				j = j + 3;
				number_string.clear();
				for (; j < N && s[j] >= '0' && s[j] <= '9'; ++j) {
					number_string.push_back(s[j]);
				}
				if (number_string.empty()) {
					word.push_back(s[i]);
					continue;
				}
				number2 = stoi(number_string);
			}
			if (number2 == -1) {
				result.push_back(searchSingleNumber(number1));
			}
			else result.push_back(searchRangeNumber(number1, number2));
			i = j - 1;
		}
		else{
			word.push_back(s[i]);
		}
	}
	return result;
}

vector <Data> Poro::searchSingleNumber(int number) {
	vector<Data> result;
	if (search_trie->numbers.count(number))
		result = search_trie->numbers[number];
	return result;
}

vector <Data> Poro::searchRangeNumber(int number1, int number2) {
	vector<Data> result;
	for (auto A = search_trie->numbers.lower_bound(number1); A != search_trie->numbers.upper_bound(number2); A++) {
		if (result.empty())
			result = A->second;
		else {
			result = OR_Data(result, A->second);
		}
	}
	return result;
}

vector < Data > Poro::StringtoData(string& s) {
	lowerString(s);
	if (s == AND) {
		return vector < Data > (1, Data(-1));
	}
	if (s == OR) {
		return vector < Data > (1, Data(-2));
	}
	if (s[0] == PLUS) {
		string thisString = s.substr(1,s.size()-1);
		Node* node = search_trie->search(thisString);
		if (!node) return vector < Data > ();
		return node->files;
	}
	if (s[0] == SWUNG_DASH) {
		string thisString = s.substr(1,s.size()-1);
		Node* node = search_trie->search(thisString);
		if (!node) return vector < Data > ();
		if (node->synonym_root == -1) return node->files;
		else return synonyms[node->synonym_root];
	}
	Node* node = search_trie->search(s);
	if (!node || node->isStopword) return vector < Data > ();
	return node->files;
}

vector < Data > Poro::processExactmatch(string s) {
	int n = s.size();
	vector < vector < Data > > V;
	vector < Data > result;
	bool init = false;
	string word;
	int d = 1;
	stringstream ss(s);
	while (ss >> word) {
		if (word.empty()) continue;
		if (word.size() == 1 && word[0] == ASTERISK && init) {
			++d;
			continue;
		}
		if (!init) {
			result = StringtoData(word);
			init = true;
		}
		else {
			vector < Data > thisData = StringtoData(word);
			result = EXACT_MATCHES(result, thisData, d);
			++d;
		}
	}
	return result;
}

vector < Data > Poro::processParenthesis(string s) {
	vector < vector < Data > > V = processString(s);
	return combineData(V);
}

vector < vector < Data > > Poro::processOperations(vector < vector < Data > >& V) {
	vector < vector < Data > > result;
	int n = V.size();
	for (int i = 0; i < n; ++i) {
		if (i + 1 >= n || !isOperation(V[i + 1])){
			result.push_back(V[i]);
		}
		else {
			vector < Data > tmp = V[i];
			bool thisbreak = false;
			for(++i; i + 1 < n; i += 2) {
				if (!isOperation(V[i])) {
					break;
				}
				int operation = -V[i].back().index;
				if (operation == 1) {
					tmp = AND_Data(tmp, V[i + 1]);
				}
				else if (operation == 2) {
					if (!isOperation(V[i + 1]))
						tmp = OR_Data(tmp, V[i + 1]);
				}
				else if (operation == 3) {
					if (!isOperation(V[i + 1]))
						tmp = EXCEPT(tmp, V[i + 1]);
				}
				else break;
			}
			result.push_back(tmp);
			--i;
		}
	}
	return result;
}

vector < Data > Poro::combineData(vector < vector < Data > >& V) {
	// spaghetti
	vector < Data > result;
	vector < vector < Data > > preProcess = processOperations(V);
	if (preProcess.empty()) return result;
	result = preProcess[0];
	for (int i = 1; i < (int)preProcess.size(); ++i) {
		result = AND_Data(result, preProcess[i]);
	}
	return result;
}

int getDistance(ii& A) {
	return A.second - A.first;
}

vector < ii > findParenthesis(string& s) {
	stack < int > S;
	vector < ii > result;
	for (int i = 0; i < (int) s.size(); ++i) {
		if (s[i] == OPEN_PARENTHESIS) {
			S.push(s[i]);
		}
		else if (s[i] == CLOSE_PARENTHESIS && !S.empty()) {
			result.push_back(make_pair(S.top(), i));
			S.pop();
		}
	}
	sort(result.begin(), result.end());
	return result;
}

vector < ii > findQuotation(string& s) {
	bool open = false;
	int x = -1;
	vector < ii > result;
	for (int i = 0; i < (int) s.size(); ++i) {
		if (s[i] == QUOTATION) {
			if (!open) {
				open = true;
				x = i;
			}
			else {
				open = false;
				result.push_back(make_pair(x, i));
			}
		}
	}
	return result;
}