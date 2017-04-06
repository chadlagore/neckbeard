#ifndef GPS_H_
#define GPS_H_

// Define bluetooth control registers
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

#define MAX_PACKET_LENGTH 82
#define UTC_TIME_LENGTH 8
#define LATITUDE_LENGTH 9
#define LONGITUDE_LENGTH 10
#define INDICATOR_LENGTH 1
#define SATS_USED_LENGTH 1
#define CHECKSUM_LENGTH 3

struct gps_packet {
    char *packetStr;
    char *packetStr_copy;
    char *utc_time;
    char *local_time;
    char *latitude;
    char *NS_indicator;
    char *longitude;
    char *EW_indicator;
    char *satelites_used;
    char *checksum;
    float latitude_float;
    float longitude_float;
};

void init_gps(void);
void gps_send_char(char c);
char gps_receive_char(void);

struct gps_packet *gps_packet_create(void);
void gps_packet_destroy(struct gps_packet *pkt);
void update_gps_data(struct gps_packet *gps_pkt);
void receive_packet(struct gps_packet *gps_pkt);
int is_GGA(struct gps_packet *gps_pkt);
void parse_packet(struct gps_packet *gps_pkt);
char *utc_to_local(struct gps_packet *gps_pkt);

#endif /* GPS_H_ */
