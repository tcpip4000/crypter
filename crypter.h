/* crypter.c
 *
 * Copyright (C) 2008 ER Technology
 * Juan P Daza P
 *
 */

#include <stdio.h>
#include <gcrypt.h>

#define MAX_DATA_LEN 16

void printCharArray(unsigned char *, int);
void decryptFile(gcry_cipher_hd_t , char *);
void encryptFileToFile(gcry_cipher_hd_t, char *, char *);
void encryptDecryptTest(gcry_cipher_hd_t, char *);

