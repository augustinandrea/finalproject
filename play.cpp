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
  char c;

  winwd = 1200;
  winht = 1200;

  gfx_open(winwd, winht, "SCRABBLE");
  gfx_clear();

  inp.open("wordlist.txt");
  d.Read(inp);

  // Create two human players for now
  game.players.push_back(new Player());
  game.players.push_back(new Player());
  game.FillHands();

  while(! game.Finished()) {
    game.Draw();
    for(int i = 0; i < game.players.size(); i++) game.HumanTurn(i);  // Run turns for all the human players
    game.FillHands();
    //game.ComputerTurn();
    //game.FillHands();
  }
    
  exit(0);
}
