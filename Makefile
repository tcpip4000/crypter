 
# Copyright (C) 2008 ER Technology
# Juan P Daza P

# TODO: migrate this file to a more generic form or maybe use automake

CC=gcc
CFLAGS=-Wall -std=c99 -O2

modaler: modaler.o crypter.o
	$(CC) modaler.o crypter.o -L/usr/lib64 -lgcrypt -lgpg-error -o modaler

modaler.o: modaler.c
	$(CC) $(CFLAGS) -I/usr/include -c modaler.c

crypter.o: crypter.c
	$(CC) $(CFLAGS) -I/usr/include -c crypter.c

clean:
	rm -f *.o 
	rm -f *~
	rm modaler

