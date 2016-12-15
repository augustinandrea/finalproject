#ifndef BUTTON_H
#define BUTTON_H

#include "polygon.h"
#include <string>
#include <iostream>

class Button {
 public:
  Button(string);
  ~Button() {cout << "Button destrructor called";};
  Point ul, lr;
  Color c;
  string label;
  void Draw(Point);
  bool ison(Point);
};

#endif
