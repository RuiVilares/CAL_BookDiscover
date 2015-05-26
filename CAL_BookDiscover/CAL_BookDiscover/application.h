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

	void play();

	void saveBooks();

	void loadBooks();

	int editDistance(string pattern, string word);

	int numApproximateStringMatching(string bookName, string toSearch, int &numWords);

	vector<pair<int, Book>> calculateGuess(vector<vector<string>> &combinations);

	vector<vector<string>> calCombinations(const vector<string> &clues);
};

/** @} */

