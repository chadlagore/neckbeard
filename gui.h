#ifndef _GUI_H_
#define _GUI_H_

#include <stdio.h>
#include <unistd.h>
#include "touch.h"
#include "graphics.h"
#include "gps.h"

/**
 * TODO: create macros for the size of the buttons and their
 * placement
 */

#define CALIBRATE_BUTTON    (x >= 130 && x <= 350 && y >= 155 && y <= 255)
#define GPS_BUTTON          (x >= 140 && x <= 350 && y >= 310 && y <= 410)
#define CAR_BUTTON          (x >= 450 && x <= 670 && y >= 160 && y <= 260)
#define EXIT_BUTTON         (x >= 570 && x <= 670 && y >= 60  && y <= 150)
#define EXIT2_BUTTON 		(x >= 635 && x <= 800 && y >= 390 && y <= 470)
#define PLOT_BUTTON         (x >= 450 && x <= 665 && y >= 310 && y <= 410)
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
void calibrate(float *base_dist);

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

/**
 * Respond to user actions on the touch screen
 */
void gui_control(void);

void plot_data(float base_dist);



#endif /* _GUI_H_ */
