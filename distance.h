#ifndef _DISTANCE_H_
#define _DISTANCE_H_

/* Define registers for distance sensor */
#define DISTANCE_CONTROL (*(volatile unsigned char *)(0x84000200))
#define DISTANCE_STATUS (*(volatile unsigned char *)(0x84000200))
#define DISTANCE_TXDATA (*(volatile unsigned char *)(0x84000202))
#define DISTANCE_RXDATA (*(volatile unsigned char *)(0x84000202))
#define DISTANCE_BAUD (*(volatile unsigned char *)(0x84000204))

/* Masks for status register */
#define DISTANCE_TX_MASK 0x02
#define DISTANCE_RX_MASK 0x01

void init_distance(void);
int get_distance(void);

#endif /* _DISTANCE_H_ */
