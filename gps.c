#include "gps.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char packetStr[82]; //Max length of message
char *utc_time;
char *latitude;
char *NS_indicator;
char *longitude;
char *EW_indicator;
char *satelites_used;
char *checksum;

void init_gps(void) {

	GPS_CONTROL = 0x15;
	GPS_BAUD = 0x5;
}

void send_char(char c)
{
	while(1)
	{
		if (GPS_STATUS & GPS_TX_MASK)
		{
			GPS_TXDATA = c;
		}
	}
}

char receive_char(void){

	while(1)
	{
		if (GPS_STATUS & GPS_RX_MASK)
		{
			return GPS_RXDATA;
		}
	}
	return '\0';
}

/* Store the packet recieved in an array*/
void packet_to_str(void){
	while(1){ //keep checking for chars until new packet is read
		char packetChar = receive_char();
		//Start of new packet
		if(packetChar == '$'){
			int i = 0;
			//Copy packet to array until <CR><LF> *IS THIS RIGHT
			while(packetChar != '\r'){
				//Check that data is valid
				if(packetChar != '\0') {
					packetStr[i] = packetChar;
					i++;
				}
				packetChar = receive_char();

			}
			//Append null to terminate the array
			packetStr[i++] = '\0';
			break; //stop reading for packets once a GGA packet has been collected?
		}
	}
}

/* Verify that the packet is of type GPGGA */
int check_GGA(){
	char *strPntr = packetStr;
	char checkStr[82]; //bad practice to declare an array too long
	//Store packet string in an array without brackets
	for(int n = 0; *(strPntr + n) != ',' ; n++){
		checkStr[n] = *(strPntr + n);
	}
	//Check that the packet begins with GPGGA
	if(checkStr[3] == 'G' && checkStr[4] == 'G' && checkStr[5] == 'A'){
		return 1;
	}
	return 0;
}

/* Stores each element of GPS data in an array (Problem: sometimes no data for
a particular element, can't pass a NULL into an array..
loose uniformity of indices) */
void parse_packet(){
	char * ptr;
	//total number of tokens in GPGGA packet - excluding <CR>
	char *array[15];
	int i = 0;
	ptr = strtok (packetStr, ",");
	while (ptr != NULL)
	{
		array[i] = ptr;
		ptr = strtok (NULL, ",");
		i++;
	}

	//get tokens
	utc_time = array[1]; //starts at 1 because 0 will be $GPGGA
	latitude = array[2];
	NS_indicator = array[3];
	longitude = array[4];
	EW_indicator = array[5];
	satelites_used = array [7];
	checksum = array[14];

}

/* Alternative: Parse each entry starting at m = 7 (after $GPGGA) Problem: no mem of last ','
char * get_entry(int m){
char tempStr[];
for(int k = 0; *(ptr + m) != ',' ; k++){
tempString[k] = *(ptr + m);
m++;
}
return tempString;
}*/

/* Covert UTC timestamp to local time
*/
int utc_to_local(char *utc_time){
	
	return 0;
}


/* Functions for Data Logger
int swap_endian(char *s){
register int val;
val = strtoul(s, NULL, 16) ; // convert to 4 byte int form in base 16
val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF );
val = (val << 16) | ((val >> 16) & 0xFFFF);
return val ;
}

float convert_latitude(int x){
static char buff[100] ;
float *ptr = (float *)(&x) ; // cast int to float
float f = *ptr ; // get the float
sprintf(buff, "%2.4f", f); // write in string to an array
return buff ;
}

float convert_longitude(int x){
static char buff[100] ;
float *ptr = (float *)(&x) ;
float f = *ptr ;
sprintf(buff, "%3.4f", f);
return buff ;
}
*/
