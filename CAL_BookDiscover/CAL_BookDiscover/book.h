#include <string>

using namespace std;

class Book{
private:
	string name;
	string author;
	int year;

public:
	Book(string name, string author, int year);
	string getName();
	string getAuthor();
	int getYear();
	bool operator<(Book& book2);
};