// Copyright (C) 2016 Aluminium Computing

#include <hedgehog.h>
#include <gfx.h>


char screen[24][81];
//screen = malloc(1920);

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
  int row, col;
  char c = 0x20;
  for (row=0;row<24;row++) {
    for (col=0;col<80;col++){
      screen[row][col]=c;
    }
    screen[row][col]='\0';
  }
}

void GXAddPixel(int row, int col) {
  screen[row][col] = '@';
}

void GXAddChar(int row, int col, char ltr) {
  screen[row][col] = ltr;
}

void GXAddText(int row, int col, char *text) {
  int spot;
  int textpos;
  for (spot = col; text[textpos] != '\0'; spot++) {
    GXAddChar(row, spot, text[textpos]);
    textpos++;
  }
}

void GXAddHLine(int row, int col, int len) {
  int spot;
  for (spot = col; spot <= (len+col); spot++) {
    GXAddPixel(row, spot);
  }
}

void GXAddVLine(int row, int col, int len) {
  int spot;
  for (spot=row; spot<=(len+row); spot++) {
    GXAddPixel(spot,col);
  }
}

void GXUpdate() {
  int k;
  for (k=0;k<24;k++){
    HHPrint(screen[k]);
  }

}
