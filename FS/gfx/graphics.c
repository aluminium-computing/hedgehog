// Copyright (C) 2016 Aluminium Computing

#include <hedgehog.h>
#include <gfx.h>

void GXRow(char *bar);

char screen[1920]  ;

const char pixel = '@';
unsigned char front;
unsigned char back;
void GXSetColours(unsigned char colour, unsigned char backcolour) {
  front = colour;
  back = backcolour;
  HHSetScreenColor(front,back);
  HHClearScreen();
}

void GXInit() {
  int q;
  int rowlen = 80;
  /*
  for (q = 0; q < (rowlen * 24); q += rowlen) {
      HHMemsetW(screen[q], 'D', 80);
  }
  */
  HHMemsetW(screen, 'X', 640);
}

void GXAddPixel(int x, int y) {
  int rowlen = 80;
  int i = (rowlen * x) + y;
  screen[i] = '@';
}

void GXUpdate() {
  HHPrint(screen);
}

void GXRow(char *bar) {
  HHPrint(bar);
  HHPrint("\n");
}
