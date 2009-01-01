 
# Copyright (C) 2008 ER Technology
# Juan P Daza P

# TODO: migrate this file to a more generic form or maybe use automake

CC=gcc
CFLAGS=-Wall -std=c99 -O2

modalgen: modalgen.o libcrypter.a modaler
	$(CC) modalgen.o -L./src -L/usr/lib -lgcrypt -lgpg-error -lcrypter -o modalgen

modaler: modaler.o libcrypter.a
	$(CC) modaler.o -L./src -L/usr/lib -lgcrypt -lgpg-error -lcrypter -o modaler

libcrypter.a: crypter.o
	ar cr src/libcrypter.a src/crypter.o

modalgen.o: modalgen.c
	$(CC) $(CFLAGS) -I/usr/include -I./src -c modalgen.c

modaler.o: modaler.c
	$(CC) $(CFLAGS) -I/usr/include -I./src -c modaler.c

crypter.o: src/crypter.c
	$(CC) $(CFLAGS) -I/usr/include -I./src -c src/crypter.c -o src/crypter.o

clean:
	rm -f *.o 
	rm -f *~ 
	rm -f src/*.[oa]
	rm -f src/*~
	rm modaler modalgen

