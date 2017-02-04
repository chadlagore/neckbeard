#include <stdio.h>
#include <string.h>
#include "graphics.h"

#include "OutGraphicsCharFont2.h"

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


Point indicator = get_press();
count = 0;

x1 = 375;
x2 = 475;
y1 = 220;
y2 = 320;

char *strbuffer = malloc


testButton(x1, y1, x2, y2, WHITE, LIME, RED, "Current Car Count: "  )
if (indicator.x > x1 - 5 && indicator.x < x2 + 5 && indicator.y > y1 - 5 && indicator.y < y2 + 5) {
    count++;
}

T
