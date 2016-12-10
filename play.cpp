#include "scrabble.h"
#include "gfx.h"

const int SCREENWD = Square::WIDTH*(Board::SIZE + 2);
const int SCREENHT = Square::HEIGHT*(Board::SIZE + 2);

int main() {
  Board board;

  gfx_open(SCREENWD, SCREENHT, "SCRABBLE");
  gfx_clear();
  
  // Testing.  Draw the board.
  board.Draw();

  gfx_wait();

  exit(0);
}
