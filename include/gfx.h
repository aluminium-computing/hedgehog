#ifndef GFX_H
#define GFX_H
void GXSetColours(unsigned char colour, unsigned char backcolour);
void GXAddPixel(int x, int y);
void GXUpdate();
void GXInit();
void GXAddHLine(int row, int col, int len);
#endif // GFX_H
