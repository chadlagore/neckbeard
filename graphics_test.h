#include <stdio.h>
#include "graphics.h"

void TestHLine(int x1, int y1, int length, int Colour);
void TestVLine(int x1, int y1, int length, int Colour);
void TestLine(int x1, int y1, int x2, int y2, int Colour);
void TestFilledRectangle(int x1, int y1, int x2, int y2, int color);
void TestCircle(int x0, int y0, int radius, int color);
void line_test_screen();
void testClearScreen(void);
void TestFilledRectangle2(int x1, int y1, int x2, int y2, int color);
void testRectangle (int x1, int y1, int x2, int y2, int colour);
void testButton(int x1, int y1, int x2, int y2, int outline_color, int font_color, int fill_color, char *text);
