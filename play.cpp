#include <fstream>
#include <iostream>

#include "scrabble.h"
#include "dictionary.h"
#include "gfxnew.h"

using namespace std;

Dictionary *global_dictionary;
ScrabbleGame *global_game;

int main() {
  int winwd, winht;
  ifstream inp;
  char c;
  Dictionary d;
  ScrabbleGame game;

  global_dictionary = &d;
  global_game = &game;

  winwd = 660;
  winht = 660;

  gfx_open(winwd, winht, "SCRABBLE");
  gfx_clear();

  inp.open("wordlist.txt");
  d.Read(inp);

  // Create two human players for now
  game.players.push_back(new Player(1));
  game.players.push_back(new Player(2));
  game.FillHands();

  //Draw the board
  game.board.Draw();

  while(! game.Finished()) {
    game.Draw();
    for(int i = 0; i < game.players.size(); i++) {
      game.HumanTurn(i);  // Run turns for all the human players
      game.FillHands();
      game.players[i]->Draw();
    }
    //game.ComputerTurn();
    //game.FillHands();
  }
    
  exit(0);
}
