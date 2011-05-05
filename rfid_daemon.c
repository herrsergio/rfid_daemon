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


#include "rfid_daemon.h"
#include "daemonize.h"


int main(int argc, char *argv[])
{
			
   //pthread_t a_thread;
	
	//daemonize();
	
	init_serial_port();
	init_socket();
	
	//signal(SIGINT, catch_int);
	
	/* For some reason, if I used a thread, the process becomes a 
	   zombie. Sergio Cuellar Valdes. Feb 2006
	*/

   //pthread_create(&a_thread, NULL, read_serial_port, NULL);
	//pthread_exit(NULL);
	
	read_serial_port();
	kill_socket();
   return 0;
}
