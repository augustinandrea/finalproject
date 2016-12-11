#define LETTER_H
#ifndef LETTER_H

class Square;
class Player;

typedef enum { board, hand, pile } letter_location_t;

class Letter {
 public:
  char c;             // The character
  const int points;   // How many points is this letter worth
  letter_location_t where;  // Where am i?
  Square &square;     // If on the board, what square are we on?
  Player &hand;       // If in someones hand, which one?
  void Draw(Point p); // Draw the letter on the screen
  static Color color; // Color of a letter tile
};

#endif
