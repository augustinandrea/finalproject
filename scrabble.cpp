#include "scrabble.h"
#include "gfx.h"

vector<Point> Board::triple_word_score = {
    Point(0,0), Point(0,7), Point(0,14), Point(7,0), Point(14,0), Point(14,7), Point(14,14)
};
vector<Point> Board::double_word_score = { // TBD
  Point(1,1), Point(2,2), Point(3,3), Point(4,4),
  Point(13,13), Point(12,12), Point(11,11), Point(10,10),
  Point(13,1), Point(12,2), Point(11,3), Point(10,4),
  Point(1,13), Point(2,12), Point(3,11), Point(4,10),
  Point(7,7),
};
vector<Point> Board::triple_letter_score = { // TBD
  Point(1,5), Point(1,9),
  Point(5,1), Point(5,5), Point(5,9), Point(5,13),
  Point(9,1), Point(9,5), Point(9,9), Point(9,13),
  Point(13,5), Point(13,9)
};
vector<Point> Board::double_letter_score = { // TBD
  Point(0,3), Point(0,11),
  Point(2,6), Point(2,8),
  Point(3,0), Point(3,7), Point(3,14),
  Point(6,2), Point(6,6), Point(6,8), Point(6,12),
  Point(7,3), Point(7,11),
  Point(8,2), Point(8,6), Point(8,8), Point(8,12),
  Point(11,0), Point(11,7), Point(11,14),
  Point(12,6), Point(12,8),
  Point(14,3), Point(14,11)
};


Square::Square() {
  word_multiplier = 1;
  letter_multiplier = 1;
  color = BEIGE;
}

// Draw the square. The squares upper left corner is at Point p
void Square::Draw(Point p) {
  const int BORDER = 2;
  gfx_color(color);
  for(int i = p.y; i < p.y+HEIGHT; i++) {
     gfx_line(p.x, i, p.x+WIDTH, i);
  }
  // Draw the Borders
  gfx_color(WHITE);
  for(int i = p.y; i < p.y+BORDER; i++) {
     gfx_line(p.x, i, p.x+WIDTH, i);
  }
  for(int i = p.y+HEIGHT-BORDER; i < p.y+HEIGHT; i++) {
     gfx_line(p.x, i, p.x+WIDTH, i);
  }
  for(int i = p.x; i < p.x+BORDER; i++) {
    gfx_line(i, p.y, i, p.y+HEIGHT);
  }
  for(int i = p.x+WIDTH-BORDER; i < p.x+WIDTH; i++) {
    gfx_line(i, p.y, i, p.y+HEIGHT);
  }
}

void Square::SetWordMultiplier(int m) {
  word_multiplier = m;
  switch(m) {
  case 2:
    color = PINK;
    break;
  case 3:
    color = RED;
    break;
  };
}

void Square::SetLetterMultiplier(int m) {
  letter_multiplier = m;
  switch(m) {
  case 2:
    color = LIGHTBLUE;
    break;
  case 3:
    color = DARKBLUE;
    break;
  };
}

Board::Board() {
  // Create the squares
  // Square 0,0 is the upper left hand corner, square SIZE,SIZE is the lower right hand corner
  for(int i = 0; i < double_word_score.size(); i++)
    squares[double_word_score[i].x][double_word_score[i].y].SetWordMultiplier(2);
  for(int i = 0; i < triple_word_score.size(); i++)
    squares[triple_word_score[i].x][triple_word_score[i].y].SetWordMultiplier(3);
  for(int i = 0; i < double_letter_score.size(); i++)
    squares[double_letter_score[i].x][double_letter_score[i].y].SetLetterMultiplier(2);
  for(int i = 0; i < triple_letter_score.size(); i++)
    squares[triple_letter_score[i].x][triple_letter_score[i].y].SetLetterMultiplier(3);
}

void Board::Draw() {
  // Draw the squares
  for(int i = 0; i < SIZE; i++) {
    for(int j = 0; j < SIZE; j++) {
      squares[i][j].Draw(Point(Square::WIDTH*(i+1),Square::HEIGHT*(j+1)));
    }
  }
}
