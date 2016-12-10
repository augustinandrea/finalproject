#ifndef SCRABBLE_H
#define SCRABBLE_H

#include <vector>
#include <string>
#include "polygon.h"

using namespace std;

typedef enum { board, hand, pile } letter_location_t;

class Player;

class Square {
 public:
  Square();
  void SetWordMultiplier(int);
  void SetLetterMultiplier(int);
  int word_multiplier;
  int letter_multiplier;
  static const int HEIGHT = 50;
  static const int WIDTH = 50;
  Color color;
  void Draw(Point p);
};

class Letter {
 public:
  char c;           // The character
  const int points; // How many points is this letter worth
  letter_location_t where;  // Where am i?
  Square &square;    // If on the board, what square are we on?
  Player &hand;      // If in someones hand, which one?
  void Draw(Point p); // Draw the letter on the screen
};

class Word {
 public:
  vector<Letter*> letters; // the letters in the word
  vector<Square*> squares; // the squares on the board used by this word
  string GetString(); // c++ string for the word
  bool Legal();       // Is this a legal scrabble word ?
  Word();
 private:
  string word; // c++ string for the word
};

class Player {
 public:
  Player();
  void Draw(Point p);  // Draw the player record on the screen
  vector<Letter *> hand;  // The letters in the players hand
  vector<Word *> words;   // Words on the board played by the player
  int score;  // Players current score
  
};

class Board {
 public:
  static const int SIZE = 15;
  static vector<Point> triple_word_score;
  static vector<Point> double_word_score;
  static vector<Point> triple_letter_score;
  static vector<Point> double_letter_score;
  Square squares[SIZE][SIZE];
  Board();
  void Draw();
};

// A complete state of a Scrabble game
class ScrabbleGame {
  ScrabbleGame();
  
  vector<Letter> letters;  // All of the letters
  vector<Letter> pile;     // Letter draw pile
  Board board;             // the board
  vector<Player> players;  // All of the players
  
};

#endif
