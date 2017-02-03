/*
 * A test suite for the graphics library.
 */

#include <stdio.h>
#include "graphics.h"

#include "OutGraphicsCharFont2.h"

/**
 * Draw a circle (one pixel at a time)
 * Prints an error message and returns without drawing anything if any points would be off screen
 */
void TestCircle(int x0, int y0, int radius, int color)
{


	int x = radius;
	int y = 0;
	int decisionOver2 = 1 - x;   // Decision criterion divided by 2 evaluated at x=r, y=0

	while( y <= x ) {
		WriteAPixel( x + x0,  y + y0, color); // Octant 1
		WriteAPixel( y + x0,  x + y0, color); // Octant 2
		WriteAPixel(-x + x0,  y + y0, color); // Octant 4
		WriteAPixel(-y + x0,  x + y0, color); // Octant 3
		WriteAPixel(-x + x0, -y + y0, color); // Octant 5
		WriteAPixel(-y + x0, -x + y0, color); // Octant 6
		WriteAPixel( x + x0, -y + y0, color); // Octant 7
		WriteAPixel( y + x0, -x + y0, color); // Octant 8
		y++;
		if (decisionOver2 <= 0) {
		  decisionOver2 += 2 * y + 1;   // Change in decision criterion for y -> y+1
		}
		else {
		  x--;
		  decisionOver2 += 2 * (y - x) + 1;   // Change for y -> y+1, x -> x-1
		}
	}
}

/**
 * Draw a filled rectangle at a top-left point (x1, y1) to a
 * bottom-right point at (x2, y2).
 * Preconditions: x1 <= x2 and y1 <= y2
 */
void TestFilledRectangle(int x1, int y1, int x2, int y2, int color)
{

	int i;
	for (i = y1; i <= y2; i++) {
		WriteHLine(x1, i, x2-x1, color);
	}
}

void TestFilledRectangle2(int x1, int y1, int x2, int y2, int color){

	int i;
	int j;

	for (i = y1; i <= y2; i++){
		for (j = x1; j <= x2; j++){
			WriteAPixel(j, i, color);
		}
	}
}

/*********************************************************************************************
* Draw a horizontal line (1 pixel at a time) starting at the x,y coords specified
* Use for testing only
*********************************************************************************************/

void TestHLine(int x1, int y1, int length, int Colour)
{
	int i;
	for(i = x1; i < x1+length; i++ )
		WriteAPixel(i, y1, Colour);
}

void testClearScreen(void){
	int i;
	int j;

	for (i = 0; i <= YRES; i++){
		for (j = 0; j <= XRES; j++){
			WriteAPixel(j, i, BLACK);
		}
	}

}

/*********************************************************************************************
* Draw a vertical line (1 pixel at a time) starting at the x,y coords specified
* Use for testing only
*********************************************************************************************/

void TestVLine(int x1, int y1, int length, int Colour)
{
	int i;
	for(i = y1; i < y1+length; i++ )
		WriteAPixel(x1, i, Colour);
}

/*******************************************************************************
* Implementation of Bresenhams line drawing algorithm (1 pixel at a time)
* Use for testing only
*******************************************************************************/

int abs(int a)
{
    if(a < 0)
        return -a ;
    else
        return a ;
}

int sign(int a)
{
    if(a < 0)
        return -1 ;
    else if (a == 0)
        return 0 ;
    else
        return 1 ;
}

void TestLine(int x1, int y1, int x2, int y2, int Colour)
{
    int x = x1;
    int y = y1;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int s1 = sign(x2 - x1);
    int s2 = sign(y2 - y1);
    int i, temp, interchange = 0, error ;

// if x1=x2 and y1=y2 then it is a line of zero length

    if(dx == 0 && dy == 0)
        return ;

 // must be a complex line so use bresenhams algorithm
    else    {

// swap delta x and delta y depending upon slop of line

        if(dy > dx) {
            temp = dx ;
            dx = dy ;
            dy = temp ;
            interchange = 1 ;
        }

// initialise the error term to compensate for non-zero intercept

        error = (dy << 1) - dx ;    // (2 * dy) - dx

// main loop
        for(i = 1; i <= dx; i++)    {
            WriteAPixel(x, y, Colour);

            while(error >= 0)   {
                if(interchange == 1)
                    x += s1 ;
                else
                    y += s2 ;

                error -= (dx << 1) ;    // times 2
            }

            if(interchange == 1)
                y += s2 ;
            else
                x += s1 ;

            error += (dy << 1) ;    // times 2
        }
    }
}

void testButton(int x1, int y1, int x2, int y2, int outline_color, int font_color, int fill_color, char *text)
{
	const int text_padding_x = 6;
	const int text_padding_y = 6;
	TestFilledRectangle2(x1, y1, x2, y2, fill_color);
	Rectangle(x1, y1, x2, y2, outline_color);
	Text(x1+text_padding_x, y1+text_padding_y, font_color, fill_color, text, 1);
}

void testRectangle (int x1, int y1, int x2, int y2, int colour) {
	int i;

	for (i = x1; i <= x2; i++) {
		WriteAPixel(i, y1, colour);
	}

	for (i = x1; i <= x2; i++) {
		WriteAPixel(i, y2, colour);
	}

	for (i = y1; i <= y2; i++) {
			WriteAPixel(x1, i, colour);
	}

	for (i = y1; i <= y2; i++) {
			WriteAPixel(x2, i, colour);
	}
}
/*******************************************************************************
* Compare functions to check for correctness
* Use for testing only
*******************************************************************************/
void write_test_screen() {
	// write RED lines (software) over the entire screen area
	// if we do hardware-accelerated lines and they fail,
	// the rest of the test will be harder to see
	int i;
	for(i = 0; i <= YRES-1; i++) {
		TestHLine(0, i, XRES-1, RED);
	}

	//each pair of lines (for horizontal/vertical) should have the same length

	//for horizontal lines,
	//test lines should start at both even and odd indexes
	//and have even and odd lengths
	//because they may be drawn incorrectly when drawing two pixels per cycle

	// even start pixel, even length
	TestHLine(100,100,100,LIME);
	TestHLine(100,101,100,LIME);
	TestHLine(100,102,100,LIME);
	TestHLine(100,103,100,LIME);
	TestHLine(100,104,100,LIME);
	WriteHLine(100,105,100,BLUE);
	WriteHLine(100,106,100,BLUE);
	WriteHLine(100,107,100,BLUE);
	WriteHLine(100,108,100,BLUE);
	WriteHLine(100,109,100,BLUE);

	// odd start pixel, even length
	TestHLine(101,120,100,LIME);
	TestHLine(101,121,100,LIME);
	TestHLine(101,122,100,LIME);
	TestHLine(101,123,100,LIME);
	TestHLine(101,124,100,LIME);
	WriteHLine(101,125,100,BLUE);
	WriteHLine(101,126,100,BLUE);
	WriteHLine(101,127,100,BLUE);
	WriteHLine(101,128,100,BLUE);
	WriteHLine(101,129,100,BLUE);

	// even start pixel, odd length
	TestHLine(100,140,101,LIME);
	TestHLine(100,141,101,LIME);
	TestHLine(100,142,101,LIME);
	TestHLine(100,143,101,LIME);
	TestHLine(100,144,101,LIME);
	WriteHLine(100,145,101,BLUE);
	WriteHLine(100,146,101,BLUE);
	WriteHLine(100,147,101,BLUE);
	WriteHLine(100,148,101,BLUE);
	WriteHLine(100,149,101,BLUE);

	// odd start pixel, odd length
	TestHLine(101,160,101,LIME);
	TestHLine(101,161,101,LIME);
	TestHLine(101,162,101,LIME);
	TestHLine(101,163,101,LIME);
	TestHLine(101,164,101,LIME);
	WriteHLine(101,165,101,BLUE);
	WriteHLine(101,166,101,BLUE);
	WriteHLine(101,167,101,BLUE);
	WriteHLine(101,168,101,BLUE);
	WriteHLine(101,169,101,BLUE);

	// test vertical lines
	TestVLine(200,200,100,LIME);
	TestVLine(201,200,100,LIME);
	TestVLine(202,200,100,LIME);
	TestVLine(203,200,100,LIME);
	TestVLine(204,200,100,LIME);
	WriteVLine(205,200,100,BLUE);
	WriteVLine(206,200,100,BLUE);
	WriteVLine(207,200,100,BLUE);
	WriteVLine(208,200,100,BLUE);
	WriteVLine(209,200,100,BLUE);

	// compare bresenham lines
	// should see a black line on top
	// and a purple line a few pixels below it
	// otherwise the hardware-accelerated line doesn't perfectly match

	WriteLine(240,340,440,440,MAGENTA);
	WriteLine(239,339,439,439,MAGENTA);
	TestLine(240,340,440,440,BLACK);
	TestLine(239,339,439,439,BLACK);

	TestLine(250,350,450,450,BLACK);
	TestLine(249,349,449,449,BLACK);
	WriteLine(250,350,450,450,MAGENTA);
	WriteLine(249,349,449,449,MAGENTA);

	// compare rectangles
	// should see WHITE rectangles above
	// and a LIME rectangles below

	// even to even
	//WriteFilledRectangle(400, 250, 500, 300, LIME);
	//TestFilledRectangle(400, 250, 500, 300, WHITE);

	// even to odd
	WriteFilledRectangle(600, 250, 701, 300, LIME);
	TestFilledRectangle(600, 250, 701, 300, WHITE);

	// odd to even
	TestFilledRectangle(401, 350, 500, 400, WHITE);
	WriteFilledRectangle(401, 350, 500, 400, LIME);

	// odd to odd
	TestFilledRectangle(601, 350, 701, 400, WHITE);
	WriteFilledRectangle(601, 350, 701, 400, LIME);

	// compare circles
	WriteCircle(500, 100, 50, LIME);
	TestCircle(500, 100, 50, WHITE);
	TestCircle(700, 100, 50, WHITE);
	WriteCircle(700, 100, 50, LIME);

}

void main(void) {
	int i;
	//ClearScreen(BLACK);
	//Text(200, 240, LIME, BLACK, "in the time of chimpanzees I was a monkey", 0);
	//Button(400, 250, 500, 300, RED, BLUE, LIME, "push me i'm a button");
	//TestFilledRectangle(601, 350, 701, 400, WHITE);
	//write_test_screen();
	testClearScreen();
	//TestFilledRectangle2(100, 100, 200, 200, RED);
	testButton(100, 100, 200, 200, WHITE, LIME, RED, "PEACE");
	TestCircle(125, 150, 25, WHITE);
	TestCircle(175, 150, 25, WHITE);

	for (i = 12; i >=0; i--){
		TestCircle(125, 150, i, WHITE);
		TestCircle(175, 150, i, WHITE);
	}
}
