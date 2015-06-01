#ifndef _INTERFACE_H_
#define _INTERFACE_H_

/** @defgroup Interface Interface
* @{
* Functions for controlling console appearance
*/

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "book.h"

#ifdef _WIN32
#include <stdlib.h>
#endif

/**Class with terminal configurations
*
*/
class Interface{
public:

	/**Interface constructor 
	*
	*/
	Interface();

	/**Interface destructor
	*
	*/
	~Interface();

	/**Waits a key pressed by user
	*
	*/
	void getInput();

	/**Reads a char given by user
	*
	*/
	template<typename Type>
	void readChar(Type &var);

	/**Reads a line given by user
	*@param STRING string reference that save a line given by user.
	*/
	void readLine(std::string &STRING);

	/**Reads a input given by user
	*@param var Type reference that save a input given by user.
	*/
	template<typename Type>
	void read(Type &var);

	/**Prints a char in command line
	*
	*/
	void drawChar(char CHAR);

	/**Print every variables in command line
	*
	*/
	template<typename Type>
	void drawString(Type STRING);

	/**Adds a new line in command line
	*
	*/
	void newLine();

	/**Cleans every command line
	*
	*/
	void cleanScr();
	/** Prints formated information of a book
	*@param book book to print
	*/
	void drawTable(Book book);
	/** Prints formated header for the book table
	*@param header1 first column
	*@param header2 second column
	*@param header3 third column
	*/
	void drawHeader(string header1, string header2, string header3);
};

template<typename Type>
void Interface::readChar(Type &var){
	std::cin >> var;
	std::cin.ignore(1000, '\n');
	if (std::cin.fail())
		std::cin.clear();
}

template<typename Type>
void Interface::read(Type &var){
	std::cin >> var;
	std::cin.ignore(1000, '\n');
	if (std::cin.fail())
		std::cin.clear();
}

template<typename Type>
void Interface::drawString(Type STRING){
	std::cout << STRING;
}

/** @} */

#endif