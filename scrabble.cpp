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
  letter = NULL;
}

// Draw the square. The squares upper left corner is at Point p
void Square::Draw(Point p) {
  const int BORDER = 2;
  ul = p;
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
  string ssmallfont = "-adobe-helvetica-bold-r-normal--12-*-*-*-*-*-*-*";
  char *csmallfont = new char[ssmallfont.size() + 1];
  strcpy(csmallfont, ssmallfont.c_str());
  string sdouble = "Double";
  char * cdouble = new char[sdouble.size() + 1];
  strcpy(cdouble,sdouble.c_str());
  gfx_changefont(csmallfont);
  gfx_color(WHITE);
  int fheight = gfx_textpixelheight(cdouble, csmallfont);
  int fwidth =  gfx_textpixelwidth(cdouble, csmallfont);
  p.y += (height + BORDER - 2*fheight)/2;
  p.x += (width + BORDER -fwidth)/2;
  if(word_multiplier == 2) {
    // Double word score
    gfx_text(p.x,p.y,"Double");
    p.y += fheight;
    gfx_text(p.x,p.y,"Word");
    p.y += fheight;
    gfx_text(p.x,p.y,"Score");
  } else if(word_multiplier == 3) {
    // Triple word score
    gfx_text(p.x,p.y,"Triple");
    p.y += fheight;
    gfx_text(p.x,p.y,"Word");
    p.y += fheight;
    gfx_text(p.x,p.y,"Score");
  } else if(letter_multiplier == 2) {
    // Double letter score
    gfx_text(p.x,p.y,"Double");
    p.y += fheight;
    gfx_text(p.x,p.y,"Letter");
    p.y += fheight;
    gfx_text(p.x,p.y,"Score");
  } else if(letter_multiplier == 3) {
    // Triple letter score
    gfx_text(p.x,p.y,"Triple");
    p.y += fheight;
    gfx_text(p.x,p.y,"Letter");
    p.y += fheight;
    gfx_text(p.x,p.y,"Score");
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
  Square::height = (gfx_windowheight()*.8 - Player::displayht)/SIZE;
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

  // Draw the players
  height = (gfx_windowheight() - (Square::height/2));
  height = height - Square::height*(Board::SIZE+1.5);
  height = height/players.size();
  width = Square::width*Board::SIZE;
  p1.x = Square::width;
  p1.y = Square::height*(Board::SIZE+1.4);
  for(int i = 0; i < players.size(); i++) {
    p2.x = p1.x + width;
    p2.y = p1.y + height;
    players[i]->Draw(p1,p2);
    p1.y = p1.y + height*1.1;
  }

  // Display count of remaining tiles in the draw pile
  Point p;
  p.x = Square::width*(Board::SIZE+1.5);
  p.y = Square::height*(Board::SIZE+1)/2;
  string ssmallfont = "-adobe-helvetica-bold-r-normal--18-*-*-*-*-*-*-*";
  char *csmallfont = new char[ssmallfont.size() + 1];
  strcpy(csmallfont, ssmallfont.c_str());
  gfx_changefont(csmallfont);

  string s = "Tiles Remaining: " + to_string(pile.size());
  gfx_text(p.x, p.y, s.c_str());

  // Display count of tiles in the computer's hand
  // TBD

  // Draw buttons
  for(int i = 0; i < buttons.size(); i++) {
    p.y = p.y + Square::height;
    buttons[i]->Draw(p);
  }

}

Letter::Letter(char ch, int pts) {
  c = ch;
  points = pts;
  color = DARKBEIGE;
  where = pile;
  selected = false;
}

vector<LD> letterdist = {LD('A',9,1), LD('B',2,3), LD('C',2,3), LD('D',4,4), LD('E',12,1), LD('F',2,4), LD('G',3,2),
			 LD('H',2,4), LD('I',9,1), LD('J',1,8), LD('K',1,5), LD('L',4,1), LD('M',2,1), LD('N',6,1),
			 LD('O',8,1), LD('P',2,1), LD('Q',1,10), LD('R',6,1), LD('S',4,1), LD('T',6,1), LD('U',4,1),
			 LD('V',2,4), LD('W',2,4), LD('X',1,8), LD('Y',2,4), LD('Z',1,10), LD(' ',2,0)};

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

  // Initialize buttons
  buttons.push_back(new Button("End Turn"));
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
  Point tul, tlr;
  int width, height;
  string sbigfont = "-adobe-helvetica-bold-r-normal--28-*-*-*-*-*-*-*";
  string ssmallfont = "-adobe-helvetica-bold-r-normal--14-*-*-*-*-*-*-*";
  char text[2];

  cout << "Drawing " << c << " at " << p.x << endl;
  drawpoint = p;
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
  if(selected) {
    // Draw a yellow boarder if selected
    gfx_flush();
    gfx_color(YELLOW);
    draw_border(ul, lr, 2);
  }

  // Write the letter on the tile
  gfx_changefont(cbigfont);
  gfx_color(WHITE);
  int fwidth = gfx_textpixelwidth(text, cbigfont);
  int fheight = gfx_textpixelheight(text, cbigfont);
  tul.x = ul.x + (width-fwidth)/2;
  tul.y = ul.y + fheight - (height-fheight)/4;
  gfx_text(tul.x, tul.y, text);

  // Write the value on the tile
  gfx_changefont(csmallfont);
  tul.y = tul.y + height/3;
  tul.x = tul.x - (Square::width*0.1);
  string stext = to_string(points);
  char *ctext = new char[stext.size()+1];
  strcpy(ctext, stext.c_str());
  gfx_text(tul.x, tul.y, ctext);
}

// Is Point p on the Letter? Used to check if a click on the screen clicks on a Letter
bool Letter::ison(Point p) {
  return ((p.x >= ul.x) && (p.x <= lr.x) && (p.y >= ul.y) && (p.y <= lr.y));
}

bool Square::ison(Point p) {
  return ((p.x >= ul.x) && (p.x <= lr.x) && (p.y >= ul.y) && (p.y <= lr.y));
}

void Player::Draw(Point ulp, Point lrp) {
  Point p;

  ul = ulp;
  lr = lrp;

  p.x = ul.x + Square::height/2;
  p.y = ul.y + Square::height/2;
  gfx_color(WHITE);
  gfx_rectangle(ul,lr);
  for(int i = 0; i < hand.size(); i++) {
    hand[i]->Draw(p);
    p.x = p.x + (Square::width * 1.5);
  }

  p.x = ul.x + Square::height * 1.5 * 7.5;
  string ssmallfont = "-adobe-helvetica-bold-r-normal--14-*-*-*-*-*-*-*";
  char *csmallfont = new char[ssmallfont.size() + 1];
  strcpy(csmallfont, ssmallfont.c_str());
  gfx_changefont(csmallfont);
  gfx_color(WHITE);
  for(int i = 0; i < words.size(); i++) {
    string s = to_string(words[i]->score) + "  " + words[i]->GetString();
    gfx_text(p.x, p.y, s.c_str());
    p.y = p.y+16;
  }
  
}

void Player::Draw() {
  gfx_color(BLACK);
  gfx_fill_rectangle(ul,lr);
  gfx_flush();
  Draw(ul,lr);
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

void ScrabbleGame::HumanTurn(int pn) {
  Point click;
  char c;
  while(true) {
    if((c = gfx_wait()) == '\001') {
      gfx_wait();
      click.x = gfx_xpos();
      click.y = gfx_ypos();
      cout << "Mouse click at: (" << click.x << "," << click.y << ")" << endl;
      // Things we could click on:
      // 1. Tile in our hand.  If it is selected, deselected it.
      //    If it is not selected, select it and deselect any other tiles in our hand.
      // 2. Square on the board.  If it is empty, and a tile in our hand is selected, put the tile on that square.
      //    If the square is occupied, ignore it.
      // 3. Button.  If "End Turn" the run the end of turn code.

      // Check tiles in players hand
      bool found = false;
      for(int i = 0; i != players[pn]->hand.size(); i++) {
	if(players[pn]->hand[i]->ison(click)) {
	  found = true;
	  players[pn]->hand[i]->Select();
	  players[pn]->hand[i]->Draw();
	  for(int j = 0; j != players[pn]->hand.size(); j++) {
	    if(j != i) {
	      if(players[pn]->hand[j]->selected) {
		players[pn]->hand[j]->DeSelect();
		players[pn]->hand[j]->Draw();
	      }
	    }
	  }
	}
      }

      if(found == false) {
	// Did not click on a tile in the players hand
	// Try squares on the board
	// TBD
	for(int i = 0; i < Board::SIZE; i++) {
	  for(int j = 0; j < Board::SIZE; j++) {
	    if(board.squares[i][j].ison(click)) {
	      found = true;
	      cout << "Square [" << i << "][" << j << "] clicked" << endl;
	      // If a tile in the players had is selected, put it on this square
	      for(int k = 0; k < players[pn]->hand.size(); k++) {
		if(players[pn]->hand[k]->selected) {
		  Letter *l =  players[pn]->hand[k];
		  
		  // Put letter on the board
		  l->where = letter_location_t::board;
		  l->square = &(board.squares[i][j]);
		  l->DeSelect();
		  l->Draw(board.squares[i][j].ul);
		  
		  // Remove letter from the players hand
		  if(k < (players[pn]->hand.size() - 1)) {
		    for (int a = k; a < players[pn]->hand.size(); a++) {
		      players[pn]->hand[a] = players[pn]->hand[a+1];
		    }
		  }
		  players[pn]->hand.pop_back();
		  players[pn]->Draw();

		  // Add letter to a word being built
		  if(players[pn]->current_word == NULL) {
		    players[pn]->current_word = new Word();
		  }
		  players[pn]->current_word->AddLetter(l);
		}
	      }
	    }
	  }
	}
      }

      if(found == false) {
	// Did not click on a tile in the players hand, and
	// Did not click on a tile on the board
	// Try buttons
	for(int i = 0; i < buttons.size(); i++) {
	  if (buttons[i]->ison(click)) {
	    if(buttons[i]->label == "End Turn") {
	      if(players[pn]->current_word != NULL) {
		players[pn]->current_word->score = 0;
		int word_mult = 1;
		for(int j = 0; j < players[pn]->current_word->letters.size(); j++) {
		  Letter *l = players[pn]->current_word->letters[j];
		  players[pn]->current_word->score += l->points * l->square->letter_multiplier;
		  word_mult = word_mult * l->square->word_multiplier;
		}
		players[pn]->current_word->score = players[pn]->current_word->score * word_mult;
		players[pn]->words.push_back(players[pn]->current_word);
	      }
	      players[pn]->current_word = NULL;
	      return;
	    } else if (buttons[i]->label == "Redraw") {
	    }
	  }
	}
      }
      
    }
  }
}

void ScrabbleGame::ComputerTurn() {
}

bool ScrabbleGame::Finished() {
  return false;
}

Word::Word() {
  direction = unknown;
}

void Word::AddLetter(Letter *l) {
  letters.push_back(l);
  word.push_back(l->c);
}

string Word::GetString() {
  return word;
}
