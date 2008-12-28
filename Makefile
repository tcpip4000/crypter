CC=gcc 
CFLAGS=-Wall

crypter: crypter.o
	$(CC) crypter.o -L/usr/lib64 -lgcrypt -lgpg-error -o crypter

crypter.o: crypter.c
	$(CC) $(CFLAGS) -I/usr/include -c crypter.c

clean:
	rm -f *.o 
	rm -f *~
	rm crypter

