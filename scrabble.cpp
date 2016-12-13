#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "scrabble.h"
#include "gfxnew.h"

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

int Square::width;
int Square::height;

Square::Square() {
  word_multiplier = 1;
  letter_multiplier = 1;
  color = BEIGE;
}

// Draw the square. The squares upper left corner is at Point p
void Square::Draw(Point p) {
  const int BORDER = 2;
  Point lr;
  lr.x = p.x + width;
  lr.y = p.y + height;
  gfx_color(color);
  gfx_fill_rectangle(p,lr);
  // Draw the Borders
  gfx_color(WHITE);
  for(int i = p.y; i <= p.y+BORDER; i++) {
     gfx_line(p.x, i, p.x+width, i);
  }
  for(int i = p.y+height-BORDER; i <= p.y+height; i++) {
     gfx_line(p.x, i, p.x+width, i);
  }
  for(int i = p.x; i <= p.x+BORDER; i++) {
    gfx_line(i, p.y, i, p.y+height);
  }
  for(int i = p.x+width-BORDER; i <= p.x+width; i++) {
    gfx_line(i, p.y, i, p.y+height);
  }
  // Write the text for the multipliers on the square
  if(word_multiplier == 2) {
    // Double word score
  } else if(word_multiplier == 3) {
    // Triple word score
  } else if(letter_multiplier == 2) {
    // Double letter score
  } else if(letter_multiplier == 3) {
    // Triple letter score
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
  Square::height = (gfx_windowheight()*.7 - Player::displayht)/SIZE;
  Square::width = Square::height;
  for(int i = 0; i < SIZE; i++) {
    for(int j = 0; j < SIZE; j++) {
      squares[i][j].Draw(Point(Square::height*(i+1),Square::width*(j+1)));
    }
  }
}

void ScrabbleGame::Draw() {
  Point p1, p2;
  int width, height;

  //Draw the board
  board.Draw();

  // Draw the players
  height = (gfx_windowheight() - (Square::height/2));
  height = height - Square::height*(Board::SIZE+1.5);
  height = height/players.size();
  width = Square::width*Board::SIZE;
  for(int i = 0; i < players.size(); i++) {
    p1.x = Square::width;
    p1.y = Square::height*(Board::SIZE+1.5);
    p2.x = p1.x + width;
    p2.y = p1.y + height;
    players[i]->Draw(p1,p2);
    p1.x = p1.x + height;
  }
}

Letter::Letter(char ch, int pts) {
  c = ch;
  points = pts;
  color = DARKBEIGE;
  where = pile;
}

vector<LD> letterdist = {LD('A',9,1), LD('B',2,3), LD('C',2,3) };

ScrabbleGame::ScrabbleGame() {
  Letter *l;
  // Initialize letters
  for(auto i = letterdist.begin(); i != letterdist.end(); i++) {
    for(int j = 0; j < i->number; j++) {
      l = new Letter(i->c,i->points);
      letters.push_back(l);
      pile.push_back(l);
    }
  }
  cout << "Pile size: " << pile.size() << endl;
}

int Player::displaywd;
int Player::displayht;

Player::Player() {
  displayht = gfx_windowheight()*.1;
  displaywd = gfx_windowwidth()*.5;
}

LD::LD(char ch, int num, int pts) {
  c = ch;
  number = num;
  points = pts;
}

void Letter::Draw(Point p) {
  Point ul, lr;
  int width, height;
  string sbigfont = "-adobe-helvetica-bold-r-normal--28-*-*-*-*-*-*-*";
  string ssmallfont = "-adobe-helvetica-bold-r-normal--14-*-*-*-*-*-*-*";
  char text[2];

  text[0] = c; text[1] = '\0';
  width = Square::width*0.9;
  height = Square::height*0.9;
  char *cbigfont = new char[sbigfont.size() + 1];
  strcpy(cbigfont, sbigfont.c_str());
  char *csmallfont = new char[ssmallfont.size() + 1];
  strcpy(csmallfont, ssmallfont.c_str());

  // Draw the tile
  ul.x = p.x + (Square::width*0.1)/2;
  ul.y = p.y + (Square::height*0.1)/2;
  lr.x = ul.x + width;
  lr.y = ul.y + height;
  gfx_color(color);
  gfx_fill_rectangle(ul, lr);

  // Write the letter on the tile
  gfx_changefont(cbigfont);
  gfx_color(WHITE);
  int fwidth = gfx_textpixelwidth(text, cbigfont);
  int fheight = gfx_textpixelheight(text, cbigfont);
  ul.x = ul.x + (width-fwidth)/2;
  ul.y = ul.y + fheight - (height-fheight)/4;
  gfx_text(ul.x, ul.y, text);

  // Write the value on the tile
  gfx_changefont(csmallfont);
  ul.y = ul.y + height/3;
  ul.x = ul.x - (Square::width*0.1);
  string stext = to_string(points);
  char *ctext = new char[stext.size()+1];
  strcpy(ctext, stext.c_str());
  gfx_text(ul.x, ul.y, ctext);
}

void Player::Draw(Point ul, Point lr) {
  Point p;

  p.x = ul.x + Square::height/2;
  p.y = ul.y + Square::height/2;
  gfx_color(WHITE);
  gfx_rectangle(ul,lr);
  for(int i = 0; i < hand.size(); i++) {
    hand[i]->Draw(p);
    p.x = p.x + (Square::width * 1.5);
  }
}

void ScrabbleGame::FillHands() {
  Letter *l;
  for(int i = 0; i < players.size(); i++) {
    for(int j = players[i]->hand.size(); j < 7; j++) {
      if((l = DrawRandomLetter()) != NULL) {
	l->where = hand;
	l->hand = players[i];
	players[i]->hand.push_back(l);
      } else {
	return; // No more letters to draw
      }
    }
  }	
}

Letter *ScrabbleGame::DrawRandomLetter() {
  if(pile.size() == 0) return NULL;
  int r = rand() % pile.size();
  Letter *l = pile[r];
  Letter *last = pile.back(); 
  pile[r] = last;
  pile.pop_back();
  return l;
}
