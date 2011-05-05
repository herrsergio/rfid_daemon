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
 
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
//#include <linux/config.h>
#include <sys/types.h>

#define BUFSIZE	1024

char buffer[BUFSIZE];
struct sockaddr_in addr;
	
int sd, addr_size, bytes_read;

int port=10001;

int init_socket(void) {
	if ( (sd = socket(PF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("Socket");
		return 1;
		abort();
   }
	
	addr.sin_family = AF_INET;
   addr.sin_port = htons(port);
   
	if ( inet_aton("127.0.0.1", &addr.sin_addr) == 0 ) {
   	perror("127.0.0.1");
		return 1;
		abort();
   }
	
	return 0;
}

void kill_socket(void) {
	close(sd);
}
