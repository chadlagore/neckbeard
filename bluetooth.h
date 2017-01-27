#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

/* Define bluetooth control registers */
#define BLUETOOTH_STATUS   (*(volatile unsigned char *)(0x84000220))
#define BLUETOOTH_CONTROL  (*(volatile unsigned char *)(0x84000220))
#define BLUETOOTH_TXDATA   (*(volatile unsigned char *)(0x84000222))
#define BLUETOOTH_RXDATA   (*(volatile unsigned char *)(0x84000222))
#define BLUETOOTH_BAUD     (*(volatile unsigned char *)(0x84000224))

#define BLUETOOTH_TX_MASK 0x02
#define BLUETOOTH_RX_MASK 0x01

void init_bluetooth(void);
void send_ch(char c);
void send_string(char str[]);
void command_mode(void);
void data_mode(void);

void reset_bluetooth(void);
void set_name(char name[]);
void set_pw(char pw[]);

#endif /* _BLUETOOTH_H_ */
