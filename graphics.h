#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#define	BLACK		0
#define	WHITE		1
#define	RED			2
#define	LIME		3
#define	BLUE		4
#define	YELLOW		5
#define	CYAN		6
#define	MAGENTA		7

#define GraphicsCommandReg                  (*(volatile unsigned short int *)(0x84000000))
#define GraphicsStatusReg                   (*(volatile unsigned short int *)(0x84000000))
#define GraphicsX1Reg                       (*(volatile unsigned short int *)(0x84000002))
#define GraphicsY1Reg                       (*(volatile unsigned short int *)(0x84000004))
#define GraphicsX2Reg                       (*(volatile unsigned short int *)(0x84000006))
#define GraphicsY2Reg			            (*(volatile unsigned short int *)(0x84000008))
#define GraphicsColourReg                   (*(volatile unsigned short int *)(0x8400000E))
#define GraphicsBackGroundColourReg   		(*(volatile unsigned short int *)(0x84000010))

/*
 * Constants representing values we write to the graphics 'command' register to get
 * it to do something. You will add more values as you add hardware to the graphics chip
 * Note DrawHLine, DrawVLine and DrawLine at the moment do nothing - you will modify these
 */

#define DrawHLine		        1
#define DrawVLine		        2
#define DrawLine		        3
#define PutAPixel		        0xA
#define GetAPixel		        0xB
#define ProgramPaletteColour   	0x10

/* This macro pauses until the graphics chip status register indicates that it is idle */
#define WAIT_FOR_GRAPHICS		while((GraphicsStatusReg & 0x0001) != 0x0001);

/**********************************************************************
* This function writes a single pixel to the x,y coords specified in the specified colour
* Note colour is a palette number (0-255) not a 24 bit RGB value
**********************************************************************/
void WriteAPixel (int x, int y, int Colour);

/*****************************************************************************************
* This function read a single pixel from x,y coords specified and returns its colour
* Note returned colour is a palette number (0-255) not a 24 bit RGB value
******************************************************************************************/
int ReadAPixel (int x, int y);

/****************************************************************************************************
** subroutine to program a hardware (graphics chip) palette number with an RGB value
** e.g. ProgramPalette(RED, 0x00FF0000) ;
****************************************************************************************************/
void ProgramPalette(int PaletteNumber, int RGB);

#endif /* _GRAPHICS_H */
