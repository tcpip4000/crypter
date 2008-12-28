 
# Copyright (C) 2008 ER Technology
# Juan P Daza P

# TODO: migrate this file to a more generic form or maybe use automake

CC=gcc
CFLAGS=-Wall -std=c99 -O2

modaler: modaler.o libcrypter.a
	$(CC) modaler.o -L./crypter -L/usr/lib64 -lgcrypt -lgpg-error -lcrypter -o modaler

libcrypter.a: crypter.o
	ar cr crypter/libcrypter.a crypter/crypter.o

modaler.o: modaler.c
	$(CC) $(CFLAGS) -I/usr/include -Icrypter -c modaler.c

crypter.o: crypter/crypter.c
	$(CC) $(CFLAGS) -I/usr/include -Icrypter -c crypter/crypter.c -o crypter/crypter.o

clean:
	rm -f *.o 
	rm -f *~ 
	rm -f crypter/*.[oa]
	rm -f crypter/*~
	rm modaler

