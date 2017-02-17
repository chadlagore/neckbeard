#ifndef _GUI_H_
#define _GUI_H_

#include <stdio.h>
#include <unistd.h>
#include "touch.h"
#include "graphics.h"
#include "gps.h"


//macros which define the boundaries of
//a particular GUI button
#define CALIBRATE_BUTTON    (x >= 130 && x <= 350 && y >= 155 && y <= 255)
#define GPS_BUTTON          (x >= 140 && x <= 350 && y >= 310 && y <= 410)
#define CAR_BUTTON          (x >= 450 && x <= 670 && y >= 160 && y <= 260)
#define EXIT_BUTTON         (x >= 570 && x <= 670 && y >= 60  && y <= 150)
#define EXIT2_BUTTON 		    (x >= 635 && x <= 800 && y >= 390 && y <= 470)
#define PLOT_BUTTON         (x >= 450 && x <= 665 && y >= 310 && y <= 410)


void startup_screen();
void main_menu();
void calibrate();
void display_gps();
void display_cars();
void plot_data();



#endif /* _GUI_H_ */
