 
# Copyright (C) 2008 ER Technology
# Juan P Daza P

# TODO: migrate this file to a more generic form or maybe use automake

CC=gcc
CFLAGS=-Wall -std=c99 -O2

modaler: modaler.o crypter.o
	$(CC) modaler.o crypter/crypter.o -L/usr/lib64 -lgcrypt -lgpg-error -o modaler

modaler.o: modaler.c
	$(CC) $(CFLAGS) -I/usr/include -Icrypter -c modaler.c

crypter.o: crypter/crypter.c
	$(CC) $(CFLAGS) -I/usr/include -Icrypter -c crypter/crypter.c -o crypter/crypter.o

clean:
	rm -f *.o 
	rm -f *~ 
	rm -f crypter/*.o
	rm -f crypter/*~
	rm modaler

