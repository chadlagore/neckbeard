#ifndef GUI_H_
#define GUI_H_

#include <stdio.h>
#include <unistd.h>
#include "touch.h"
#include "graphics_test.h"
#include "graphics.h"

/**
 * TODO: create macros for the size of the buttons and their
 * placement
 */

/**
 * this displays a crosswalk and introduces the app, fake
 * copyright info and stuff.
 */
void startup_screen();

/**
 * this function draws the main menu and the buttons
 */
void main_menu();

/**
 * this calls the calibrate function, then performs a graphical
 * flourish of sorts showing progress or something.
 */
void calibrate();

/**
 * this displays a pop-up window that has the live gps, time and
 * car counting data. this would be an event loop that is constantly
 * updating the graphics with the information. this will include an exit
 * button to leave the function.
 */
void display_gps();

/**
 * opens a pop-up window that displays the amount of cars
 * that have driven past in real time.
 */
void display_cars();



#endif /* GUI_H_ */
