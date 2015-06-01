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
	vector<Book> books; // Books available 

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
	/**
	* @brief Adding a book to the book vector
	*/
	void addBook();
	/**
	* @brief Removing a book to the book vector
	*/
	void removeBook();
	/**
	* @brief Print all books in the book vector
	*/
	void showBooks();
	/**
	* @brief Play the game
	*/
	void play();
	/**
	* @brief Save all books from vector to a .txt file
	*/
	void saveBooks();
	/**
	* @brief Load all books from a .txt file to the books vector
	*/
	void loadBooks();
	/**
	* @brief Calculates the minimum edition to transform a word into to another
	* @param pattern Word that is used as reference
	* @param word Word that is going to be "transformed"
	*/
	int editDistance(string pattern, string word);
	/**
	* @brief Calculates the edit change for each word of a book title
	* @param bookName Name of the book
	* @param toSearch Word that is going to be "transformed"
	* @param numWords Number of words of the book title (calculated in this funtion)
	*/
	int numApproximateStringMatching(string bookName, string toSearch, int &numWords);
	/**
	* @brief Calculates the most probable guesses for the book
	* @param combinations Combinations of words using the clues
	* @return Vector with pairs matching the book to the edit distance
	*/
	vector<pair<int, Book>> calculateGuess(vector<vector<string>> &combinations);
	/**
	* @brief Calculates the possible combination with the clues given
	* @param clues Clues provided by the user
	* @return Vector with the combinations of the clues
	*/
	vector<vector<string>> calCombinations(const vector<string> &clues);
};

/** @} */

