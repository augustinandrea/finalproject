#include <unistd.h>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>
#include "polygon.h"
#include "gfxnew.h"

using namespace std;

const int DEFAULT_RADIUS = 50;
const int VELOCITY_MIN = -20;
const int VELOCITY_MAX = 20;
const int DEFAULT_ACCELERATION = 1;
const int COLOR_MIN = 0;
const int COLOR_MAX = 255;

void gfx_color(Color c) {
  gfx_color(c.r, c.g, c.b);
}

void gfx_line(Point p1, Point p2) {
  gfx_line(
	   round(p1.x),
	   round(p1.y),
	   round(p2.x),
	   round(p2.y)
	   );
}

Point::Point(double x, double y) {
  this->x = x;
  this->y = y;
}

Point& Point::operator=(const Point& p) {
  if(this != &p) {
    this->x = p.x;
    this->y = p.y;
  }
  return *this;
}

// Rotate a point about a center (xc, yc)
// angle is the measure in radians of the rotation.  e.g. PI rotates 180 degrees
void Point::Rotate(double xc, double yc, double angle) {
  double newx = cos(angle)*(x - xc) - sin(angle)*(y - yc) + xc;
  double newy = sin(angle)*(x - xc) + cos(angle)*(y - yc) + yc;

  x = newx;
  y = newy;
}

Polygon::Polygon(Point center, int sides, int radius) {
  Point p;
  
  if((sides < 0) || (sides == 1) || (sides == 2)) {
    // number of sides must 0 (a circle) or 3 or greater. <0, 1, or 2 are not allowed
    cout << "Error: Attempt to create Polygon with sides: " << sides << endl;
  }
  this->sides = sides;
  this->center = center;
  this->radius = radius;

  if(sides >= 3) {
    // first point
    p.x = this->center.x - radius * cos(PI/sides);
    p.y = this->center.y + radius * sin(PI/sides);
    corners.push_back(p);
    for(int i = 1; i <= sides; i++) {
      p.Rotate(this->center.x, this->center.y, 2*PI/sides);
      corners.push_back(p);
    }
  }
  color = WHITE;
  angle = 0.0;
}

void Polygon::Draw() {
  for(auto i = 0; i < corners.size() - 1; i++){
    gfx_line(
	     round(corners[i].x),
	     round(corners[i].y),
	     round(corners[i+1].x),
	     round(corners[i+1].y));
  }
}

void Polygon::Rotate(double angle) {
}

void gfx_rectangle(Point upperleft, Point lowerright) {
  gfx_rectangle(upperleft.x, upperleft.y,
		     lowerright.x - upperleft.x,
		     lowerright.y - upperleft.y);
}

void gfx_fill_rectangle(Point upperleft, Point lowerright) {
  gfx_fill_rectangle(upperleft.x, upperleft.y,
		     lowerright.x - upperleft.x,
		     lowerright.y - upperleft.y);
}

void draw_border(Point ul, Point lr, int b) {
  // Top border
  for(int i = ul.y; i <= ul.y+b; i++) {
     gfx_line(ul.x, i, lr.x-1, i);
  }
  // Bottom border
  for(int i = lr.y-b-1; i <= lr.y-1; i++) {
     gfx_line(ul.x, i, lr.x-1, i);
  }
  // Left border
  for(int i = ul.x; i <= ul.x+b; i++) {
    gfx_line(i, ul.y, i, lr.y-1);
  }
  // right border
  for(int i = lr.x-b-1; i <= lr.x-1; i++) {
    gfx_line(i, ul.y, i, lr.y-1);
  }
}

char *getfont(int base) {
  int fontsize = round((((double) gfx_windowheight())/1200.) * (double) base);
  string font = "-adobe-helvetica-bold-r-normal--" + to_string(fontsize)+ "-*-*-*-*-*-*-*";
  char *cfont = new char[font.size() + 1];
  strcpy(cfont, font.c_str());
  return cfont;
}

