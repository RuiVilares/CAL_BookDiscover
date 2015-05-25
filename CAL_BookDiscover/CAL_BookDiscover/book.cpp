#include "book.h"

Book::Book(string name, string author, int year):name(name), author(author), year(year){}

string Book::getName(){ return name; }

string Book::getAuthor(){ return author; }

int Book::getYear(){ return year; }

bool Book::operator<(Book& book2){
	if (name < book2.getName())
		return true;
	return false;
}