CC = gcc
LIBS = -lpthread

rfid_daemon : rfid_daemon.c
	$(CC) -o $@ $@.c $(LIBS) 
clean:
	rm -f rfid_daemon
