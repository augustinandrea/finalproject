#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "dictionary.h"
#include <istream>
#include <string>
#include <set>

using namespace std;

// Dictionary stores all the legal scrabble words
class Dictionary {
 public:
  Dictionary();
  void Read(istream &);  // Initialize the dictionary reading words from input
  bool isLegal(string &);    // Is the string a legal scrabble word?
  set<string> words;     // the word themselves
};

#endif
