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

    usleep(1500000);

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
    TestFilledRectangle(125, 155, 345, 255, BLACK);
    testButton(130, 160, 350, 260, BLACK, WHITE, RED, "" );
    Text(160, 190, BLACK, RED, "CALIBRATE", 0);
    Text(160, 210, BLACK, RED, "SENSOR", 0);

    /* gps button */
    TestFilledRectangle(125, 305, 345, 405, BLACK);
    testButton(130, 310, 350, 410, BLACK, WHITE, RED, "" );
    Text(160, 340, BLACK, RED, "DISPLAY GPS", 0);
    Text(160, 360, BLACK, RED, "DATA", 0);

    /* counter button */
    TestFilledRectangle(445, 155, 665, 255, BLACK);
    testButton(450, 160, 670, 260, BLACK, WHITE, RED, "" );
    Text(480, 190, BLACK, RED, "DISPLAY CAR", 0);
    Text(480, 210, BLACK, RED, "COUNT", 0);


    /* data button */
    TestFilledRectangle(445, 305, 665, 405, BLACK);
    testButton(450, 310, 670, 410, BLACK, WHITE, RED, "");
    Text(480, 340, BLACK, RED, "PLOT DATA", 0);


}


void calibrate(){
    TestFilledRectangle(220, 115, 570, 365, BLACK);
    TestFilledRectangle(225, 120, 565, 360, YELLOW);
    Text(320, 170, BLACK, YELLOW, "calibrating", 0);
    Text(285, 200, BLACK, YELLOW, "distance sensor...", 0);

    TestFilledRectangle(245, 310 , 545, 340, BLACK);
    int i;

    for (i = 0; i <= 10; i++){
        TestFilledRectangle(250, 315, 250 + 29*i , 335, BLUE );
        if (i == 5){
            // base_dist = read_dist(); TODO uncomment when sensor ready
        }
        usleep(100000);
    }

    main_menu();
}


void display_gps() {
    TestFilledRectangle(220, 115, 570, 365, BLACK);
    TestFilledRectangle(225, 120, 565, 360, YELLOW);
    TestFilledRectangle(570, 115, 670, 215, BLACK);
    TestFilledRectangle(575, 120, 665, 210, MAGENTA);
    Text(595, 150, BLACK, MAGENTA, "EXIT", 0);
    Text(350, 130, BLACK, YELLOW, "TIME:", 0);
    TestFilledRectangle(245, 160, 545, 190, BLACK);
    Text(330, 200, BLACK, YELLOW, "LATITUDE:", 0);
    TestFilledRectangle(245, 230, 545, 260, BLACK);
    Text(330, 280, BLACK, YELLOW, "LONGITUDE:", 0);
    TestFilledRectangle(245, 310, 545, 340, BLACK);

    /* Get GPS data */
    struct gps_packet *gps_pkt = gps_packet_create();
    Point touch_point;
    int x = 0, y = 0;
    clock_t start = clock();
    clock_t time_delta;

    while(1) {
        time_delta = (clock() - start)/CLOCKS_PER_SEC;

        /* Display the time and coordinates */
        if (time_delta >= 5) {
            update_gps_data(gps_pkt);
            start = clock();

            printf("%s\n", gps_pkt->packetStr);

            Text(251, 166, LIME, BLACK, gps_pkt->local_time, 0);
            Text(251, 236, LIME, BLACK, gps_pkt->latitude, 0);
            Text(251, 316, LIME, BLACK, gps_pkt->longitude, 0);
        }

        if (screen_touched()) {
            touch_point = get_press();
            x = touch_point.x;
            y = touch_point.y;

            if (EXIT_BUTTON) {
                free(gps_pkt);
                main_menu();
                return;
            }
        }
    }
}
