#ifndef GPS_H_
#define GPS_H_

// Define gps control registers
#define GPS_STATUS   (*(volatile unsigned char *)(0x84000210))
#define GPS_CONTROL  (*(volatile unsigned char *)(0x84000210))
#define GPS_TXDATA   (*(volatile unsigned char *)(0x84000212))
#define GPS_RXDATA   (*(volatile unsigned char *)(0x84000212))
#define GPS_BAUD     (*(volatile unsigned char *)(0x84000214))
#define HEX0_1       (volatile unsigned char *) (0x2030)
#define HEX2_3		 (volatile unsigned char *) (0x2040)
#define HEX4_5 	     (volatile unsigned char *) (0x2050)

#define GPS_TX_MASK 0x02
#define GPS_RX_MASK 0x01

void gps_send_char(char c);
char gps_receive_char(void);
void packet_to_str(void);
int check_GGA(void);
void parse_packet(void);
int swap_endian(char *s);
float convert_latitude(int x);
float convert_longitude(int x);
void utc_to_local(void);
void test_gps(void);


#endif /* GPS_H_ */
