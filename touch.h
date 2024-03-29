#ifndef _TOUCH_H_
#define _TOUCH_H_

typedef struct {
    int x, y;
} Point;

#define AR1100_CONTROL   (*(volatile unsigned char *)(0x84000230))
#define AR1100_STATUS    (*(volatile unsigned char *)(0x84000230))
#define AR1100_TX        (*(volatile unsigned char *)(0x84000232))
#define AR1100_RX        (*(volatile unsigned char *)(0x84000232))
#define AR1100_BAUD      (*(volatile unsigned char *)(0x84000234))

#define AR1100_RX_MASK 0x01
#define AR1100_TX_MASK 0x02

#define WAIT_FOR_TOUCH  while(!(AR1100_RX_MASK & AR1100_STATUS));

void init_touch(void);
void sendchar_touch(char c);
int screen_touched(void);
int screen_release(void);
void wait_for_touch();
void wait_for_release();
Point get_press(void);
Point get_release(void);

#endif /* _TOUCH_H_ */
