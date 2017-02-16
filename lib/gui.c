#include <stdio.h>
#include <unistd.h>
#include "gui.h"

void startup_screen(){
  //TestFilledRectangle(int x1, int y1, int x2, int y2, int color);

  TestFilledRectangle(0, 0, 800, 180, 9);
  TestFilledRectangle(0, 300, 800, 480, 9);


  TestFilledRectangle(0, 220, 50, 240, YELLOW);
  TestFilledRectangle(100, 220, 150, 240, YELLOW);
  TestFilledRectangle(200, 220, 250, 240, YELLOW);
  TestFilledRectangle(300, 220, 350, 240, YELLOW);
  TestFilledRectangle(400, 220, 450, 240, YELLOW);
  TestFilledRectangle(500, 220, 550, 240, YELLOW);
  TestFilledRectangle(600, 220, 650, 240, YELLOW);
  TestFilledRectangle(700, 220, 750, 240, YELLOW);

  usleep(1000000);

  //testButton(int x1, int y1, int x2, int y2, int outline_color, int font_color, int fill_color, char *text)
  testButton(300, 150,500, 200, WHITE, BLACK, BLUE, "Welcome to\nStreet Smart!\n(c)2017 all rights reserved." );

}

//void main_menu();

//void calibrate();

//void display_gps();

//void display_cars();
