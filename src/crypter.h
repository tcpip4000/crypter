/* crypter.c
 *
 * Copyright (C) 2008 ER Technology
 * Juan P Daza P
 *
 */

#ifndef CRYPTER_HEADER_H
#define CRYPTER_HEADER_H

#if HAVE_CONFIG_H
# include <config.h> 
#endif

#if HAVE_STDIO_H
# include <stdio.h>
#endif

#if HAVE_GCRYPT_H
# include <gcrypt.h>
#endif

#define MAX_DATA_LEN 32

void printCharArray(unsigned char *array, int array_length);
void decryptFile(gcry_cipher_hd_t handler, char *filename);
void decryptFileToFile(gcry_cipher_hd_t hd, const char *encrypted_filename, const char *plain_filename);
void encryptFileToFile(gcry_cipher_hd_t handler, const char *plain_filename, const char *encrypted_filename);
void encryptDecryptTest(gcry_cipher_hd_t handler, char *plain_filename);
void fillCharVectorWithSpaces(unsigned char vector[], int len); 

#endif /* CRYPTER_HEADER_H */

