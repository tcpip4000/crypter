 
# Copyright (C) 2008 ER Technology
# Juan P Daza P

# TODO: migrate this file to a more generic form or maybe use automake

CC=gcc
CFLAGS=-Wall -std=c99 -O2

modalgen: modalgen.o libcrypter.a modaler
	$(CC) modalgen.o -L./libcrypter -L/usr/lib -lgcrypt -lgpg-error -lcrypter -o modalgen

modaler: modaler.o libcrypter.a
	$(CC) modaler.o -L./libcrypter -L/usr/lib -lgcrypt -lgpg-error -lcrypter -o modaler

libcrypter.a: crypter.o
	ar cr libcrypter/libcrypter.a libcrypter/crypter.o

modalgen.o: modalgen.c
	$(CC) $(CFLAGS) -I/usr/include -I./libcrypter -c modalgen.c

modaler.o: modaler.c
	$(CC) $(CFLAGS) -I/usr/include -Ilibcrypter -c modaler.c

crypter.o: libcrypter/crypter.c
	$(CC) $(CFLAGS) -I/usr/include -Ilibcrypter -c libcrypter/crypter.c -o libcrypter/crypter.o

clean:
	rm -f *.o 
	rm -f *~ 
	rm -f libcrypter/*.[oa]
	rm -f libcrypter/*~
	rm modaler modalgen

