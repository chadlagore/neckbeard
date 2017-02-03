/**
	* Generic hardware accelerated graphics library.
	* Some functions are more hardware accelerated than others :-)
	*/

#include <stdio.h>
#include "graphics.h"

#include "OutGraphicsCharFont2.h"


/*******************************************************************************************
* Writes a single pixel to the x,y coords specified using the specified colour
* Note colour is a byte and represents a palette number (0-255) not a 24 bit RGB value
********************************************************************************************/
void WriteAPixel(int x, int y, int Colour) {

	WAIT_FOR_GRAPHICS;				// is graphics ready for new command

	GraphicsX1Reg = x;				// write coords to x1, y1
	GraphicsY1Reg = y;
	GraphicsColourReg = Colour;		// set pixel colour
	GraphicsCommandReg = PutAPixel;	// give graphics "write pixel" command
}

/*********************************************************************************************
* Read a single pixel from the x,y coords specified and returns its colour
* Note returned colour is a byte and represents a palette number (0-255) not a 24 bit RGB value
*********************************************************************************************/

int ReadAPixel(int x, int y)
{

	WAIT_FOR_GRAPHICS;					// is graphics ready for new command

	GraphicsX1Reg = x;					// write coords to x1, y1
	GraphicsY1Reg = y;
	GraphicsCommandReg = GetAPixel;		// give graphics a "get pixel" command

	WAIT_FOR_GRAPHICS;					// is graphics done reading pixel
	return (int)(GraphicsColourReg) ;	// return the palette number (colour)
}

/**********************************************************************************
* subroutine to program a hardware (graphics chip) palette number with an RGB value
* e.g. ProgramPalette(RED, 0x00FF0000) ;
************************************************************************************/

void ProgramPalette(int PaletteNumber, int RGB)
{
    WAIT_FOR_GRAPHICS;

    GraphicsColourReg = PaletteNumber;
    GraphicsX1Reg = RGB >> 16   ;        // program red value in ls.8 bit of X1 reg
    GraphicsY1Reg = RGB ;                // program green and blue into ls 16 bit of Y1 reg
    GraphicsCommandReg = ProgramPaletteColour; // issue command
}

/**********************************************************************************
* Write the entire screen in the given colour
************************************************************************************/
void ClearScreen(int Colour) {
	WriteFilledRectangle(0, 0, XRES-1, YRES-1, Colour);
}

/*******************************************************************************************
* Write a horizontal line (hardware-accelerated) starting at the x,y coords specified
* of the given length to the right
* Will print an error and return without writing anything if the start/end points are off
* of the screen or if length is negative
********************************************************************************************/
void WriteHLine(int x1, int y1, int length, int Colour)
{
	int x2 = x1 + length;

	WAIT_FOR_GRAPHICS;

	GraphicsX1Reg = x1;
	GraphicsY1Reg = y1;
	GraphicsX2Reg = x2;
	GraphicsColourReg = Colour;
	GraphicsCommandReg = DrawHLine;
}

/*******************************************************************************************
* Write a vertical line (hardware-accelerated) starting at the x,y coords specified
* of the given length downwards.
* Will print an error and return without writing anything if the start/end points are off
* of the screen or if length is negative
********************************************************************************************/
void WriteVLine(int x1, int y1, int length, int Colour)
{
	int y2 = y1 + length;

	WAIT_FOR_GRAPHICS;

	GraphicsX1Reg = x1;
	GraphicsY1Reg = y1;
	GraphicsY2Reg = y2;
	GraphicsColourReg = Colour;
	GraphicsCommandReg = DrawVLine;
}

/*******************************************************************************************
* Write a Bresenham line (hardware-accelerated) from x1,y1 to x2,y2
* Will print an error and return without writing anything if the start/end points are off
* of the screen
********************************************************************************************/
void WriteLine(int x1, int y1, int x2, int y2, int Colour)
{

	WAIT_FOR_GRAPHICS;

	GraphicsX1Reg = x1;
	GraphicsY1Reg = y1;
	GraphicsX2Reg = x2;
	GraphicsY2Reg = y2;
	GraphicsColourReg = Colour;
	GraphicsCommandReg = DrawLine;
}


/*
 * Draw a non-filled rectangle at a top-left point at (x1, y1) to a
 * bottom-right point at (x2, y2).
 * Preconditions: x1 <= x2 and y1 <= y2
 */
void Rectangle(int x1, int y1, int x2, int y2, int color)
{

	WriteHLine(x1, y1, x2-x1, color);
	WriteVLine(x1, y1, y2-y1, color);
	// the plus one ensures the bottom-right corner is drawn
	WriteHLine(x1, y2, x2-x1+1, color);
	WriteVLine(x2, y1, y2-y1, color);
}

/**
* Write a filled rectangle (hardware-accelerated) to the screen
* If x1 > x2 or y1 < y2 or if any corner does not fit on the screen, an error message
* will be printed and the function will return without drawing anything
*/
void WriteFilledRectangle(int x1, int y1, int x2, int y2, int Colour)
{
	int width = x2 - x1;

	WAIT_FOR_GRAPHICS;

	// Draw some horizontal lines.
	while(y1 != y2) {
		GraphicsX1Reg = x1;
		GraphicsY1Reg = y1;
		GraphicsX2Reg = x1 + width;
 		// Y2 = Y1 -- horizontal.
		GraphicsY2Reg = y1;
		GraphicsColourReg = Colour;
		GraphicsCommandReg = DrawHLine;
		y1++;
	}
}


/**
 * Draw a circle (hardware-accelerated)
 * Prints an error message and returns without drawing anything if any points would be off screen
 */
void WriteCircle(int x0, int y0, int radius, int color)
{
	WAIT_FOR_GRAPHICS;

	GraphicsX1Reg = x0;
	GraphicsY1Reg = y0;
	GraphicsX2Reg = radius; //pass in radius using X2 reg
	GraphicsColourReg = color;
	GraphicsCommandReg = DrawCircle;
}

/**
 * Draw text string on a single line.
 * Preconditions: text != NULL
 * Note: Writing a space character with erase set to true will set all pixels
 * in the character to the background colour
 */
void Text(int x, int y, int font_color, int background_color, char *text, int erase)
{
	const int text_char_x_size = 12;
	if (text != NULL) {
		int i;
		for (i = 0; text[i] != '\0'; i++) {
			  OutGraphicsCharFont2a(x+(text_char_x_size * i), y, font_color, background_color, (int) text[i], erase);
		}
	}
}

/*
 * Draw at a top-left point at (x1, y1) to a bottom-right point at (x2, y2).
 * It is up to the user to ensure that the button dimensions are larger than
 * the text dimensions.
 * Preconditions: x1 <= x2, y1 <= y2 and text != NULL
 */
void Button(int x1, int y1, int x2, int y2, int outline_color, int font_color, int fill_color, char *text)
{
	const int text_padding_x = 6;
	const int text_padding_y = 6;
	WriteFilledRectangle(x1, y1, x2, y2, fill_color);
	Rectangle(x1, y1, x2, y2, outline_color);
	Text(x1+text_padding_x, y1+text_padding_y, font_color, fill_color, text, 1);
}
