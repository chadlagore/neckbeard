#include "gui.h"
#include "graphics.h"
#include "touch.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>


void startup_screen() {

    int i;
    testClearScreen(BLACK);
    TestFilledRectangle(0, 0, 800, 180, 9);
    TestFilledRectangle(0, 300, 800, 480, 9);

    testButton(200, 130,600, 180, WHITE, BLACK, BLUE, "");
    Text(250, 136, BLACK, BLUE, "WELCOME TO STREET SMART", 0);
    Text(225, 160, BLACK, BLUE, "(c) 2017, all rights reserved",0 );

    for (i = 0; i <= 30; i++) {
        TestFilledRectangle(0,180, 800, 300, BLACK);
        TestFilledRectangle(0, 220, 50, 240, YELLOW);
        TestFilledRectangle(100, 220, 150, 240, YELLOW);
        TestFilledRectangle(200, 220, 250, 240, YELLOW);
        TestFilledRectangle(300, 220, 350, 240, YELLOW);
        TestFilledRectangle(400, 220, 450, 240, YELLOW);
        TestFilledRectangle(500, 220, 550, 240, YELLOW);
        TestFilledRectangle(600, 220, 650, 240, YELLOW);
        TestFilledRectangle(700, 220, 750, 240, YELLOW);

        /* exhaust pipe - 80 */
        TestFilledRectangle(60+i*22,240 , 80+i*22, 250, 9);
        /* body of car */
        TestFilledRectangle(80+i*22,220 , 210+i*22, 250, RED );
        /* top of car */
        TestFilledRectangle(100+i*22, 190, 190+i*22, 220, RED);
        /* window */
        TestFilledRectangle(150+i*22, 200 ,180+i*22 , 220, BLUE);

        /* tires */
        TestFilledCircle(110+i*22, 260, 20, BLACK);
        TestCircle(110+i*22, 260, 20, WHITE);
        TestFilledCircle(110+i*22, 260, 10, WHITE);

        TestFilledCircle(180+i*22, 260, 20, BLACK);
        TestCircle(180+i*22, 260, 20, WHITE);
        TestFilledCircle(180+i*22, 260, 10, WHITE);
        usleep(60000);
    }
}


void main_menu() {
    testClearScreen(BLUE);

    TestFilledRectangle(0, 0, 800, 10, BLACK);
    TestFilledRectangle(0, 0, 40, 480, BLACK);
    TestFilledRectangle(0, 470, 800, 480, BLACK);
    TestFilledRectangle(775, 0, 800, 480, BLACK);

    TestLine(20, 0, 40, 10, WHITE);
    TestLine(790, 0, 775, 10, WHITE);
    TestLine(20, 480, 40, 470, WHITE);
    TestLine(790, 480, 775, 470, WHITE);

    TestFilledRectangle(245, 20, 555, 120, BLACK);
    testButton(250, 25, 550, 115, BLACK, WHITE, YELLOW, "");
    Text(330, 37, BLACK, YELLOW, "STREET SMART", 0);
    Text(275, 75, BLACK, YELLOW, "touch your selection", 0);

    /* calibration button */
    TestFilledRectangle(145, 145, 345, 220, BLACK);
    testButton(150, 150, 350, 225, BLACK, WHITE, RED, "" );
    Text(180, 165, BLACK, RED, "CALIBRATE", 0);
    Text(180, 185, BLACK, RED, "SENSOR", 0);

    /* gps button */
    TestFilledRectangle(145, 255, 345, 330, BLACK);
    testButton(150, 260, 350, 335, BLACK, WHITE, RED, "" );
    Text(180, 275, BLACK, RED, "DISPLAY GPS", 0);
    Text(180, 295, BLACK, RED, "DATA", 0);

    /* counter button */
    TestFilledRectangle(145, 365, 345, 440, BLACK);
    testButton(150, 370, 350, 445, BLACK, WHITE, RED, "" );
    Text(180, 385, BLACK, RED, "DISPLAY CAR", 0);
    Text(180, 405, BLACK, RED, "COUNT", 0);

    TestFilledRectangle(445, 145, 645, 220, BLACK);
    testButton(450, 150, 650, 225, BLACK, WHITE, RED, "");
    TestFilledRectangle(445, 255, 645, 330, BLACK);
    testButton(450, 260, 650, 335, BLACK, WHITE, RED, "");
    TestFilledRectangle(445,365,645,440, BLACK);
    testButton(450, 370, 650, 445, BLACK, WHITE, RED, "");
}


void calibrate(){
    TestFilledRectangle(220, 115, 570, 365, BLACK);
    TestFilledRectangle(225, 120, 565, 360, YELLOW);
    Text(220, 170, BLACK, YELLOW, "calibrating", 0);
    Text(285, 200, BLACK, YELLOW, "distance sensor...", 0);

    TestFilledRectangle(245, 310 , 545, 340, BLACK);
    int i;

    for (i = 0; i <= 10; i++){
        TestFilledRectangle(250, 315, 250 + 29*i , 335, BLUE );
        if (i == 5){
            usleep(300000);
        }
        usleep(100000);
    }
}


void display_gps() {
    TestFilledRectangle(220, 115, 570, 365, BLACK);
    TestFilledRectangle(225, 120, 565, 360, YELLOW);
    TestFilledRectangle(570, 115, 670, 215, BLACK);
    TestFilledRectangle(575, 120, 665, 210, MAGENTA);
    Text(595, 150, BLACK, MAGENTA, "EXIT", 0);
    Text(300, 140, BLACK, YELLOW, "GPS LOCATION:", 0);
    TestFilledRectangle(245, 170, 545, 200, BLACK);
    Text(320, 220, BLACK, YELLOW, "TIME:", 0);
    TestFilledRectangle(245, 260, 545, 290, BLACK);

    /* Get GPS data */
    struct gps_packet *gps_pkt = gps_packet_create();
    char local_time[9], coordinates[16];
    Point touch_piont;
    int x, y;
    clock_t start = clock();
    clock_t time_delta;

    while(1) {
        time_delta = (clock() - start)/CLOCKS_PER_SEC;

        if (time_delta >= 5) {
            update_gps_data(gps_pkt);
            sprintf(local_time, "%s\0", gps_pkt->local_time);
            sprintf(coordinates, "%s, %s\0", gps_pkt->latitude, gps_pkt->longitude);
            start = clock();
        }

        /* Display the time and coordinates */
        // TODO

        touch_piont = get_press();
        x = touch_piont.x;
        y = touch_piont.y;

        if (EXIT_BUTTON) {
            free(gps_pkt);
            main_menu();
            return;
        }
    }
}
