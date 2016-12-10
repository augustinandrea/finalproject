#include "scrabble.h"
#include "gfx.h"

vector<Point> Board::triple_word_score = {
    Point(0,0), Point(0,7), Point(0,14), Point(7,0), Point(14,0), Point(14,7), Point(14,14)
};
vector<Point> Board::double_word_score = { // TBD
  Point(1,1)
};
vector<Point> Board::triple_letter_score = { // TBD
    Point(5,1)
};
vector<Point> Board::double_letter_score = { // TBD
    Point(3,0)
};


Square::Square() {
  word_multiplier = 1;
  letter_multiplier = 1;
  color = BIEGE;
}

// Draw the square.  Squares upper left corner is at Point p
void Square::Draw(Point p) {
  gfx_color(color);
  for(int i = p.y; i < p.y+HEIGHT; i++) gfx_line(p.x, p.y+i, p.x+WIDTH, p.y+i);
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
}
