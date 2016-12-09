#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "dictionary.h"
#include <istream.h>
#include <string>

// Dictionary stores all the legal scrabble words
class Dictionary {
 public:
  Dictionary(istream *input);
  bool isLegal(string& s);    // Is the string a legal scrabble word?
};

#endif
