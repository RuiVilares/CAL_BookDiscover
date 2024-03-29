#include "application.h"


Interface *Application::iface = new Interface();

Application::Application(){
	start();
}




void Application::TopMenu(string name)
{
	iface->cleanScr();
	iface->drawString("\n\n\tBook Discover\n");
	iface->drawString("\n\t");
	iface->drawString(name);
	iface->drawString("\n\n\n\n");
}


void Application::start(){
	char command;
	TopMenu("WELCOME");
	loadBooks();
	Sleep(2000);
	main();
}

void Application::main()
{
	while (1){
		char command;
		TopMenu("MAIN MENU");
		iface->drawString("a. Add book\n");
		iface->drawString("b. Remove book\n");
		iface->drawString("c. Show books\n");
		iface->drawString("d. Play\n");
		iface->drawString("q. Quit(!)\n\n");
		iface->drawString("   > ");
		iface->readChar(command);
		if (command == 'a'){
			addBook();
		}
		else if (command == 'b'){
			removeBook();
		}
		else if (command == 'c'){
			showBooks();
		}
		else if (command == 'd') {
			play();
		}
		else if (command == 'q'){
			saveBooks();
			exit(0);
		}
	}
}

void Application::addBook(){
	string title, author;
	int year;
	TopMenu("ADD BOOK");
	iface->drawString("Title: ");
	iface->readLine(title);
	iface->drawString("Author: ");
	iface->readLine(author);
	do {
		iface->drawString("Publication year: ");
		iface->read(year);
	} while (year <= 0 || year > 2015);
	books.push_back(Book(title, author, year));
	std::sort(books.begin(), books.end());
}

void Application::removeBook(){
	unsigned int command;
	while (1){
		TopMenu("REMOVE BOOK");
		for (unsigned int i = 0; i < books.size(); i++){
			iface->drawString(to_string(i + 1) + ". " + books[i].getName());
			iface->newLine();
		}
		iface->drawString("\n0. Return");
		iface->drawString("\n\n   > ");
		iface->read(command);
		if (command == 0)
			return;
		else if (command > 0 && command <= books.size()){
			TopMenu("REMOVE BOOK");
			iface->drawString("\n\n\n" + books[command - 1].getName() + " was sucefully removed!!!\n");
			books.erase(books.begin() + (command - 1));
			iface->getInput();
		}
	}
}

void Application::showBooks(){
	TopMenu("SHOW BOOKS");
	iface->drawHeader("Title","Author","Year");
	iface->drawString("-----------------------------------------------------------------------------\n");
	for (unsigned int i = 0; i < books.size(); i++){
		iface->drawTable(books[i]);
	}
	iface->getInput();
}

void Application::play(){
	int score = 0;
	int round = 1;
	while (round <= 5){
		TopMenu("PLAY");
		string line, word;
		char cmd;
		iface->drawString("Entering words base (singular, male, infinitive) separated by spaces.\nA clue may include, at most, a word missing in the book's title.\nYou have 5 rounds\n\n");
		iface->drawString("Round: " + to_string(round));
		iface->drawString("\nScore: " + to_string(score));
		iface->drawString("\n\nClue: ");
		iface->readLine(line);
		vector<string> guesses;
		stringstream s1(line);
		while (!s1.eof()) {
			s1 >> word;
			guesses.push_back(word);
		}
		vector<pair<int, Book>> res = calculateGuess(calCombinations(guesses));
		unsigned int i = 0;
		for (i; i < res.size(); i++){
			iface->drawString("\n\n");
			iface->drawHeader("Title", "Author", "Year");
			iface->drawString("-----------------------------------------------------------------------------\n");
			iface->drawTable(res[i].second);
			while (1){
				iface->drawString("\n\nThis is the book that you want?\na. Yes\nb. No\n");
				iface->drawString("   > ");
				iface->readChar(cmd);
				if (cmd == 'a'){
					score += 5;
					break;
				}
				else if (cmd == 'b'){
					score -= 1;
					break;
				}
			}
			if (cmd == 'a')
				break;
		}
		if (i < res.size())
			iface->drawString("\n\nBook found");
		else
			iface->drawString("\n\n\nGive up");
		round++;
	}
	iface->drawString("\n\nYour score: " + to_string(score));
	iface->getInput();
	return;

}

void Application::saveBooks(){
	string file;
	ofstream myfile;
	file = "Livros.txt";
	myfile.open(file);
	for (int i = 0; i < books.size(); i++){
		myfile << books[i].getName() << endl << books[i].getAuthor() << endl << books[i].getYear();
		if (i != books.size() - 1)
			myfile << endl;
	}
	myfile.close();
}

void Application::loadBooks(){
	string file;
	ifstream myfile;
	file = "Livros.txt";
	if (myfile.is_open())
		exit(0);
	myfile.open(file);
	stringstream ss;
	string line,author,title;
	int year;
	while (!myfile.eof())
	{
		ss.clear();
		getline(myfile, line);
		title = line;
		getline(myfile, line);
		author = line;
		getline(myfile, line);
		ss << line;
		ss >> year;
		books.push_back(Book(title,author, year));
	}
}

int Application::editDistance(string pattern, string word){
	transform(pattern.begin(), pattern.end(), pattern.begin(), toupper);
	transform(word.begin(), word.end(), word.begin(), toupper);
	int n = word.length();
	vector<int> d(n + 1);
	int old, neww;
	for (int j = 0; j <= n; j++)
		d[j] = j;
	int m = pattern.length();
	for (int i = 1; i <= m; i++) {
		old = d[0];
		d[0] = i;
		for (int j = 1; j <= n; j++) {
			if (pattern[i - 1] == word[j - 1]) neww = old;
			else {
				neww = min(old, d[j]);
				neww = min(neww, d[j - 1]);
				neww = neww + 1;
			}
			old = d[j];
			d[j] = neww;
		}
	}
	return d[n];
}

int Application::numApproximateStringMatching(string bookName, string toSearch, int &numWords)
{
	string line1, word1;
	int num = 0;

	int min = 20;

	stringstream s1(bookName);
	while (!s1.eof()) {
		s1 >> word1;
		numWords++;
		num = editDistance(toSearch, word1);
		if (num < min){
			min = num;
		}
	}
	return min;
}

bool pairCompare(pair<int, Book> firstElem, pair<int, Book> secondElem) {
	return firstElem.first < secondElem.first;
}

vector<pair<int,Book>> Application::calculateGuess(vector<vector<string>> &combinations){
	vector<pair<int, Book>> res;
	int total;
	int min;
	int numWords;
	for (int i = 0; i < books.size(); i++){
		min = INT_MAX;
		for (size_t j = 0; j < combinations.size(); j++)
		{
			total = 0;
			for (size_t k = 0; k < combinations[j].size(); k++)
			{
				numWords = 0;
				total += numApproximateStringMatching(books[i].getName(), combinations[j][k], numWords);
				if (numWords < combinations[0].size() - 1)
					total += 100;
			}
			if (total < min)
				min = total;
		}
		res.push_back(pair<int,Book>(min, books[i]));
	}
	sort(res.begin(), res.end(), pairCompare);
	int numOptions = 5;
	res.erase(res.begin() + numOptions, res.end());
	return res;
}


// http://stackoverflow.com/questions/9430568/generating-combinations-in-c

vector<vector<string>> Application::calCombinations(const vector<string> &clues){
	int n = clues.size();
	int r = clues.size() - 1;

	vector<vector<string>> res;
	res.push_back(clues);

	if (n > 1){
		vector<bool> v(n);
		fill(v.begin() + n - r, v.end(), true);

		do {
			vector<string> aux;
			for (int i = 0; i < n; ++i) {
				if (v[i]) {
					aux.push_back(clues[i]);
				}
			}
			res.push_back(aux);
		} while (next_permutation(v.begin(), v.end()));
	}
	return res;
}