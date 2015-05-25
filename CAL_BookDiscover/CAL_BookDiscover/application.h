#pragma once

/** @defgroup Application Application
* @{
* Functions for main application
*/

#include <sstream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <Windows.h>
#include "interface.h"

using namespace std;

/**Represents main program
*
*/
class Application{
private:
	vector<Book> books;

public:
	
	/**
	* @brief Interface used on application
	*/
	static Interface *iface;
	
	/**
	* @brief Application constructor
	*/
	Application();

	/**
	* @brief Top Menu configuration 
	*
	* @param name Top Menu name
	*/
	void TopMenu(string name);

	/**
	* @brief Start menu
	*/
	void start();

	/**
	* @brief Main menu
	*/
	void main();

	void addBook();

	void removeBook();

	void showBooks();

	void saveBooks();

	void loadBooks();

	int editDistance(string pattern, string word);

	float numApproximateStringMatching(string bookName, string toSearch);

	void calculateGuess(vector<string> &clues);
};

/** @} */