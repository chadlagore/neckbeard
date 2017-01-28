#ifndef GPS_H_
#define GPS_H_

// Define bluetooth control registers
#define GPS_STATUS   (*(volatile unsigned char *)(0x84000210))
#define GPS_CONTROL  (*(volatile unsigned char *)(0x84000210))
#define GPS_TXDATA   (*(volatile unsigned char *)(0x84000212)) //Not sure
#define GPS_RXDATA   (*(volatile unsigned char *)(0x84000212)) //which is which
#define GPS_BAUD     (*(volatile unsigned char *)(0x84000214)) //provided

#define GPS_TX_MASK 0x02
#define GPS_RX_MASK 0x01

void send_char(char c);
char receive_char(void);
void packet_to_str(void);
int check_GGA();
void parse_packet(char packetStr[]);
int swap_endian(char *s);
float convert_latitude(int x);
float convert_longitude(int x);
int utc_to_local(char *utc_time);

void save_points(void);
void config_log(void);
void start_log(void);
void stop_log(void);
void erase_log(void);

#endif // GPS_H_
