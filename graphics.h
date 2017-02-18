#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <stdio.h>
#include <string.h>
#include "OutGraphicsCharFont2.h"

#define TRUE 	1
#define FALSE 0

#define XRES 	800
#define YRES 	480

#define ASSERT_POINTS_ARE_VALID TRUE

// graphics registers all address begin with '8' so as to by pass data cache on NIOS
#define GraphicsCommandReg   		(*(volatile unsigned short int *)(0x84000000))
#define GraphicsStatusReg   		(*(volatile unsigned short int *)(0x84000000))
#define GraphicsX1Reg   				(*(volatile unsigned short int *)(0x84000002))
#define GraphicsY1Reg   				(*(volatile unsigned short int *)(0x84000004))
#define GraphicsX2Reg   				(*(volatile unsigned short int *)(0x84000006))
#define GraphicsY2Reg   				(*(volatile unsigned short int *)(0x84000008))
#define GraphicsColourReg   		(*(volatile unsigned short int *)(0x8400000E))

// this macro pauses until the graphics chip status register indicates that it is idle
#define WAIT_FOR_GRAPHICS		while((GraphicsStatusReg & 0x0001) != 0x0001);

// values for the graphics command register
#define DrawHLine								1
#define DrawVLine								2
#define DrawLine								3
#define	PutAPixel								0xA
#define	GetAPixel								0xB
#define	ProgramPaletteColour    0x10
#define DrawRectangle						0x11
#define DrawCircle							0x12

// defined constants representing colours pre-programmed into colour palette
// there are 256 colours but only 8 are shown below, we write these to the colour registers
//
// the header files "colours.h" contains constants for all 256 colours
// while the course file ColourPaletteData.c contains the 24 bit RGB data
// that is pre-programmed into the palette
#define	BLACK			0
#define	WHITE			1
#define	RED				2
#define	LIME			3
#define	BLUE			4
#define	YELLOW		5
#define	CYAN			6
#define	MAGENTA		7
#define NCOLOURS 	8


// Writes a single pixel to a coordinate.
void WriteAPixel(int x, int y, int Colour);

// Writes a horizontal line using hardware.
void WriteHLine(int x1, int y1, int length, int Colour);

// Writes a vertical line using hardware.
void WriteVLine(int x1, int y1, int length, int Colour);

// Writes a generic line using hardware from poit to point.
void WriteLine(int x1, int y1, int x2, int y2, int Colour);

// Reads a pixel from the screen.
int ReadAPixel(int x, int y);

// Programs a color palette to the screen.
void ProgramPalette(int PaletteNumber, int RGB);

// Writes a filled rectangle to the screen.
void WriteFilledRectangle(int x1, int y1, int x2, int y2, int color);

// Writes an empty recangle to the screen.
void Rectangle(int x1, int y1, int x2, int y2, int color);

// Writes an empty circle to the screen.
void WriteCircle(int x0, int y0, int radius, int color);

// Writes text to a coordinate.
void Text(int x, int y, int font_color, int background_color, char *text,
					int erase);

// Writes a button to a recangle on on the screen.
void Button(int x1, int y1, int x2, int y2, int outline_color, int font_color,
				int fill_color, char *text);

// Clears the screen using hardware.
void ClearScreen(int Colour);

//software accelerated horizontal line unit test
void TestHLine(int x1, int y1, int length, int Colour);

//software accelerated vertical line unit test
void TestVLine(int x1, int y1, int length, int Colour);

//software accelerated bresenham line unit test
void TestLine(int x1, int y1, int x2, int y2, int Colour);

//software accelerated filled rectangle unit test
void TestFilledRectangle(int x1, int y1, int x2, int y2, int color);

//software accelerated circle unit test
void TestCircle(int x0, int y0, int radius, int color);

//software acclerated filled circle unit test
void TestFilledCircle(int x0, int y0, int radius, int color);

//clears the screen to a certain colour
void testClearScreen(int colour);

//software acclerated rectangle (another method) unit test
void TestFilledRectangle2(int x1, int y1, int x2, int y2, int color);

//unfilled rectangle unit test
void testRectangle (int x1, int y1, int x2, int y2, int colour);

//generates a button, which is a filled rectangle with
//an outline and has text inside.
void testButton(int x1, int y1, int x2, int y2, int outline_color, int font_color, int fill_color, char *text);

//tests a variety of shapes and compares the software and hardware
//versions in order to ensure they're accurate
void line_test_screen();


#endif /* _GRAPHICS_H */
