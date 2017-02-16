#ifndef _DISTANCE_H_
#define _DISTANCE_H_

/* Define registers for distance sensor */
#define DISTANCE_CONTROL (*(volatile unsigned char *)(0x84000200))
#define DISTANCE_STATUS (*(volatile unsigned char *)(0x84000200))
#define DISTANCE_TXDATA (*(volatile unsigned char *)(0x84000202))
#define DISTANCE_RXDATA (*(volatile unsigned char *)(0x84000202))
#define DISTANCE_BAUD (*(volatile unsigned char *)(0x84000204))

/* For reading from Car detection hardware */
#define CYCLES          (*(volatile unsigned short int *)(0x84000900))
#define CAR_IS_PASSING  (*(volatile unsigned short int *)(0x84000904))
#define CAR_COUNT       (*(volatile unsigned short int *)(0x84000908))

#define CLOCK_SPEED_MHZ             50
#define BIT_FACTOR                  32

/* Minimum distance (cm) we must read to be able to say we detected a car */
#define CAR_DETECTION_THRESHOLD     100

/* Masks for status register */
#define DISTANCE_TX_MASK 0x02
#define DISTANCE_RX_MASK 0x01

void init_distance(void);
int get_distance(void);
float read_dist(void);
void count_cars(int seconds, float base_dist);

#endif /* _DISTANCE_H_ */
