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
			vector<string> guesses = { "cidade", "serra", "praia" };
			calculateGuess(guesses);
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

float Application::numApproximateStringMatching(string bookName, string toSearch)
{
	string line1, word1;
	int num = 0, nwords = 0;

	stringstream s1(bookName);
	while (!s1.eof()) {
		s1 >> word1;
		num  = editDistance(toSearch, word1);
		if (editDistance(toSearch, word1) < 4){
			return num;
		}
	}
	return INT_MAX;
}

void Application::calculateGuess(vector<string> &clues){
	float total = 0;
	float temp;
	for (int i = 0; i < books.size(); i++){
		for (size_t j = 0; j < clues.size(); j++)
		{
			temp = numApproximateStringMatching(books[i].getName(), clues[j]);
			if (temp < 5){
				total += temp;
			}
			else{
				total +=  100;
			}
		}
		cout << books[i].getName() << "  " << total << endl;
		total = 0;
	}
	iface->getInput();
}