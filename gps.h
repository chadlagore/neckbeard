#ifndef GPS_H_
#define GPS_H_

// Define bluetooth control registers
#define GPS_STATUS   (*(volatile unsigned char *)(0x84000210))
#define GPS_CONTROL  (*(volatile unsigned char *)(0x84000210))
#define GPS_TXDATA   (*(volatile unsigned char *)(0x84000212))
#define GPS_RXDATA   (*(volatile unsigned char *)(0x84000212))
#define GPS_BAUD     (*(volatile unsigned char *)(0x84000214))

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
    char *utc_time;
    char *local_time;
    char *latitude;
    char *NS_indicator;
    char *longitude;
    char *EW_indicator;
    char *satelites_used;
    char *checksum;
};

struct gps_packet *gps_packet_create() {
    struct gps_packet *packet = malloc(sizeof(struct gps_packet));
    packet->packetStr = malloc(sizeof(char)*MAX_PACKET_LENGTH);
    packet->utc_time = malloc(sizeof(char)*UTC_TIME_LENGTH);
    packet->local_time = malloc(sizeof(char)*UTC_TIME_LENGTH);
    packet->latitude = malloc(sizeof(char)*LATITUDE_LENGTH);
    packet->NS_indicator = malloc(sizeof(char)*INDICATOR_LENGTH);
    packet->longitude = malloc(sizeof(char)*LONGITUDE_LENGTH);
    packet->EW_indicator = malloc(sizeof(char)*INDICATOR_LENGTH);
    packet->satelites_used = malloc(sizeof(char)*SATS_USED_LENGTH);
    packet->checksum = malloc(sizeof(char)*CHECKSUM_LENGTH);
}

void init_gps(void);
void gps_send_char(char c);
char gps_receive_char(void);

void get_gps_data(struct gps_packet *pack);
void receive_packet(struct gps_packet *pack);
int is_GGA(struct gps_packet *pack);
void parse_packet(struct gps_packet *pack);
char *utc_to_local(struct gps_packet *pack);

#endif /* GPS_H_ */
