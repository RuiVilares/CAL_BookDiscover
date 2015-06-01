#pragma once
/** @defgroup Book Book
* @{
* Book Structure
*/
#include <string>

using namespace std;
/**Class that represents a book
*
*/
class Book{
private:
	string name; //name of the book
	string author; //author of the book
	int year; //year of publishing of the book

public:
	/**
	* @brief Book constructor
	* @param name Name of the book
	* @param author Author of the book
	* @param year Year of publishing of the book
	*/
	Book(string name, string author, int year);
	/**
	* @brief Getter
	* @return Returns the book name.
	*/
	string getName();
	/**
	* @brief Getter
	* @return Returns the book author.
	*/
	string getAuthor();
	/**
	* @brief Getter
	* @return Returns the book year of publishing.
	*/
	int getYear();
	/**
	* @brief Overload of the operator <. (Name of the book in alphabetic order)
	* @param book2 Book to be compared
	*/
	bool operator<(Book& book2);
};