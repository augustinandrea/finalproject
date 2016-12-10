#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "dictionary.h"
#include <istream>
#include <string>

using namespace std;

// Dictionary stores all the legal scrabble words
class Dictionary {
 public:
  Dictionary(istream &); // Initialize the dictionary reading words from input
  bool isLegal(string &);    // Is the string a legal scrabble word?
};

#endif
