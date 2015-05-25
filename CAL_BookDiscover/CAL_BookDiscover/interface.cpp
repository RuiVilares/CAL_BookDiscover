#include "interface.h"


using std::string;

//IOSTREAM
Interface::Interface(){
}

Interface::~Interface(){
}

void Interface::getInput(){
	std::cin.get();
}

void Interface::drawChar(char CHAR){
	std::cout << CHAR;
}

void Interface::readLine(std::string &STRING){
	getline(std::cin, STRING);
}

void Interface::cleanScr(){
#ifdef _WIN32 // Windows: Console command (alternative: Windows API)
	system("cls");
#else // UNIX: ANSI escape codes
	std::cout << "\x1B[2J\x1B[H";
#endif
}
void Interface::newLine(){
	std::cout << std::endl;
}

void Interface::drawTable(Book book){
	std::cout << left << setw(40) << book.getName() << setw(30) << "|  " + book.getAuthor() << setw(7) << "|  " + to_string(book.getYear()) << std::endl;
}

void Interface::drawHeader(string header1, string header2, string header3){
	std::cout << left << setw(40) << header1 << setw(30) << "|  " + header2 << setw(7) << "|  " + header3 << std::endl;
}