/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include "client_rfid.h"

#define TARJETA_BLANCA 	"01 09 0D 69 00 00 00 00 00 00 00 6D "
#define CIRCULO_NEGRO  	"01 09 0D 33 33 33 33 33 33 33 33 04 "
#define TUBO_NEGRO		"01 09 0C AF D5 E9 04 00 00 00 00 92 "
#define TOPECITO			"01 09 0C 3D DB 52 07 00 00 00 00 B6 "
#define CIRCULO_CHICO	"01 09 0C 08 37 3B 07 00 00 00 00 06 "
#define LLAVERO			"01 09 0C 4A 4F 78 07 00 00 00 00 7F "
#define CUADRITITO		"01 09 0C 02 0B 58 07 00 00 00 00 53 "
#define TUBO_CRISTAL_1  "01 09 0C 95 16 12 00 00 00 50 00 C4 "
#define TUBO_CRISTAL_2	"01 09 0D 55 55 55 55 55 55 55 55 04 "

#define BAUDRATE B9600

#define USB_SERIAL
//#define DEBUG

#define MAX_NUM_CHARACTERS 200

#ifdef USB_SERIAL
	#define PORT "/dev/ttyUSB0"
#else
	#define PORT "/dev/ttyS0"
#endif

char normal_mode[] = {1, 2,  9, 50, 57}; 
char     no_read[] = {1, 1,  3,  2};


int fd;
char line[256];



void catch_int(int sig_num) {
	sigset_t mask_set;	/* used to set a signal masking set. */
   sigset_t old_set;	/* used to store the old mask set.   */
	
	char answer[30];
	
   /* re-set the signal handler again to catch_int, for next time */
   signal(SIGINT, catch_int);
   /* mask any further signals while we're inside the handler. */
   sigfillset(&mask_set);
   sigprocmask(SIG_SETMASK, &mask_set, &old_set);
	sprintf(line, "%s",no_read);
   write(fd,line,strlen(line));
	fflush(stdout);
	exit(0);
}

int init_serial_port(void){
	struct termios oldtio,newtio;
	fd = open(PORT, O_RDWR | O_NOCTTY ); 
   if (fd <0) {
		#ifdef DEBUG
			perror("open failed");
		#endif
		return 1;
		exit(-1);
	}
	
	tcgetattr(fd,&oldtio); /* save current port settings */

   bzero(&newtio, sizeof(newtio));
   newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
   newtio.c_iflag = IGNPAR;
   newtio.c_oflag = 0;

   /* set input mode (non-canonical, no echo,...) */
   newtio.c_lflag = 0;
        
   newtio.c_cc[VTIME]    = 0;   /* inter-character timer unused */
   newtio.c_cc[VMIN]     = 1;   /* blocking read until 1 chars received */

   tcflush(fd, TCIOFLUSH);
   tcsetattr(fd,TCSANOW,&newtio);
   tcflush(fd, TCIOFLUSH);
	
	sprintf(line, "%s",normal_mode);
   write(fd,line,strlen(line));
	
	return 0;
}
	
void which_object(unsigned char *all_numbers) {
	char code[MAX_NUM_CHARACTERS];
			
	#ifdef DEBUG
   	printf("en which_numbers: %s\n", all_numbers);
	#endif
	if(strcmp(all_numbers, TARJETA_BLANCA) == 0) {
		#ifdef DEBUG
			printf("Tarjeta Blanca !!\n");
		#endif
		sprintf(code, "1");
		sendto(sd, code, strlen(code)+1, 0, (struct sockaddr*)&addr, sizeof(addr));
		memset(code, 0, MAX_NUM_CHARACTERS);
	}
	if(strcmp(all_numbers, CIRCULO_NEGRO) == 0) {
		#ifdef DEBUG
			printf("Circulo Negro !!\n");
		#endif
		sprintf(code, "2");
		sendto(sd, code, strlen(code)+1, 0, (struct sockaddr*)&addr, sizeof(addr));
		memset(code, 0, MAX_NUM_CHARACTERS);
	}
	if(strcmp(all_numbers, TUBO_NEGRO) == 0) {
		#ifdef DEBUG
			printf("Tubo Negro !!\n");
		#endif
		sprintf(code, "3");
		sendto(sd, code, strlen(code)+1, 0, (struct sockaddr*)&addr, sizeof(addr));
		memset(code, 0, MAX_NUM_CHARACTERS);
		
	}
	if(strcmp(all_numbers, TOPECITO) == 0) {
		#ifdef DEBUG
			printf("Topecito!!\n");
		#endif
		sprintf(code, "4");
		sendto(sd, code, strlen(code)+1, 0, (struct sockaddr*)&addr, sizeof(addr));
		memset(code, 0, MAX_NUM_CHARACTERS);
	}
	if(strcmp(all_numbers, CIRCULO_CHICO) == 0) {
		#ifdef DEBUG
			printf("Circulo Chico !!\n");
		#endif
		sprintf(code, "5");
		sendto(sd, code, strlen(code)+1, 0, (struct sockaddr*)&addr, sizeof(addr));
		memset(code, 0, MAX_NUM_CHARACTERS);
	}
	if(strcmp(all_numbers, LLAVERO) == 0) {
		#ifdef DEBUG
			printf("Llavero !!\n");
		#endif
		sprintf(code, "6");
		sendto(sd, code, strlen(code)+1, 0, (struct sockaddr*)&addr, sizeof(addr));
		memset(code, 0, MAX_NUM_CHARACTERS);
	}
	if(strcmp(all_numbers, TUBO_CRISTAL_1) == 0) {
		#ifdef DEBUG
			printf("Tubo de cristal 1 !!\n");
		#endif
		sprintf(code, "7");
		sendto(sd, code, strlen(code)+1, 0, (struct sockaddr*)&addr, sizeof(addr));
		memset(code, 0, MAX_NUM_CHARACTERS);
	}
	if(strcmp(all_numbers, TUBO_CRISTAL_2) == 0) {
		#ifdef DEBUG
			printf("tubo de cristal 2 !!\n");
		#endif
		sprintf(code, "8");
		sendto(sd, code, strlen(code)+1, 0, (struct sockaddr*)&addr, sizeof(addr));
		memset(code, 0, MAX_NUM_CHARACTERS);
	}
	if(strcmp(all_numbers, CUADRITITO) == 0) {
		#ifdef DEBUG
			printf("Cuadritito !!\n");
		#endif
		sprintf(code, "9");
		sendto(sd, code, strlen(code)+1, 0, (struct sockaddr*)&addr, sizeof(addr));
		memset(code, 0, MAX_NUM_CHARACTERS);
	}
}


void read_serial_port(void) {
	unsigned char c;
	int datos=0, i;
	int temp[MAX_NUM_CHARACTERS];
	unsigned char all_numbers[MAX_NUM_CHARACTERS];
	unsigned char temp_char[MAX_NUM_CHARACTERS];

   while (1) {
		if(read(fd,&c,(size_t) 1)){
			datos++;
			temp[datos] = c;
			if(datos == 12) {
				for(i = 1; i <= datos; i++) {
					sprintf(temp_char, "%02X ", temp[i]);
					strcat(all_numbers, temp_char);
					//printf("%02X ", temp[i]);
				}
			}
		}
		if(datos == 12) {
			#ifdef DEBUG
				printf("all_numbers: %s\n", all_numbers);
			#endif
			which_object(all_numbers);
			datos=0;
			memset(temp, 0 , MAX_NUM_CHARACTERS);
			memset(temp_char, 0, MAX_NUM_CHARACTERS);
			memset(all_numbers, 0, MAX_NUM_CHARACTERS);
		}
	}
}
