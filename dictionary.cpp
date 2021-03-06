#include <algorithm>
#include "dictionary.h"

using namespace std;

Dictionary::Dictionary() {
}

// Read the words in and create the dictionary
void Dictionary::Read(istream &inp) {
  string s;
  while(!inp.eof()) {
    getline(inp,s);
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    words.insert(s);
  }
}

bool Dictionary::isLegal(string &s) {
  return words.find(s) == words.end() ? false : true;
}
