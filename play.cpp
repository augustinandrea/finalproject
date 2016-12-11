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
  Player *human;
  char c;

  winwd = 1200;
  winht = 1200;

  gfx_open(winwd, winht, "SCRABBLE");
  gfx_clear();

  inp.open("wordlist.txt");
  d.Read(inp);

  human = new Player();
  game.players.push_back(human);

  while(true) {
    game.FillHands();
    game.Draw();

    c = gfx_wait();
  }
    
  exit(0);
}
