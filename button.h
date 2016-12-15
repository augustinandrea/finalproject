#ifndef BUTTON_H
#define BUTTON_H

#include "polygon.h"
#include <string>

class Button {
 public:
  Button(string);
  Point ul, lr;
  Color c;
  string label;
  void Draw(Point);
  bool ison(Point);
};

#endif
