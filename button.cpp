#include "button.h"
#include "gfxnew.h"
#include <cstring>

Button::Button(string s) {
  label = s;
  c = BLUE;
}

void Button::Draw(Point p) {
  ul = p;
  string ssmallfont = "-adobe-helvetica-bold-r-normal--18-*-*-*-*-*-*-*";
  char *csmallfont = new char[ssmallfont.size() + 1];
  strcpy(csmallfont, ssmallfont.c_str());
  gfx_changefont(csmallfont);
  char *clabel = new char[label.size() + 1];
  strcpy(clabel, label.c_str());
  int width = gfx_textpixelwidth(clabel,csmallfont)*1.5;
  int height = gfx_textpixelheight(clabel,csmallfont)*1.5;
  lr.x = ul.x + width;
  lr.y = ul.y + height;
  gfx_color(c);
  gfx_fill_rectangle(ul,lr);  
  gfx_color(WHITE);
  gfx_text(ul.x+width/10, ul.y+0.8*height, label.c_str());
}
