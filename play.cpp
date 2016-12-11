#include <fstream>
#include <iostream>

#include "scrabble.h"
#include "dictionary.h"
#include "gfxnew.h"

using namespace std;

int main() {
  ScrabbleGame game;
  Board board;
  int winwd, winht;
  Dictionary d;
  ifstream inp;

  inp.open("wordlist.txt");
  d.Read(inp);
  // Test the Dictionary
  cout << "Number of words in Dictionary: " << d.words.size() << endl;
  string s = "zymogram";
  if (d.isLegal(s)) {
    cout << "Word \"" << s << "\" is in the dictionary" << endl;
  }

  winwd = 1200;
  winht = 1200;

  gfx_open(winwd, winht, "SCRABBLE");
  gfx_clear();
  
  // Testing.  Draw the full screen
  game.Draw();

  gfx_wait();

  exit(0);
}
