/* crypter.c
 *
 * Copyright (C) 2008 ER Technology
 * Juan P Daza P
 *
 */

#ifndef CRYPTER_HEADER_H
#define CRYPTER_HEADER_H

#include <stdio.h>
#include <gcrypt.h>

#define MAX_DATA_LEN 16

void printCharArray(unsigned char *array, int array_length);
void decryptFile(gcry_cipher_hd_t handler, char *filename);
void decryptFileToFile(gcry_cipher_hd_t hd, char *encrypted_filename, char *plain_filename);
void encryptFileToFile(gcry_cipher_hd_t handler, char *plain_filename, char *encrypted_filename);
void encryptDecryptTest(gcry_cipher_hd_t handler, char *plain_filename);

#endif /* CRYPTER_HEADER_H */

