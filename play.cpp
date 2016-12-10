#include "scrabble.h"
#include "gfxnew.h"

int main() {
  ScrabbleGame game;
  Board board;
  int winwd, winht;

  winwd = 1200;
  winht = 1200;

  gfx_open(winwd, winht, "SCRABBLE");
  gfx_clear();
  
  // Testing.  Draw the full screen
  game.Draw();

  gfx_wait();

  exit(0);
}
