/* crypter.c
 *
 * Copyright (C) 2008 ER Technology
 * Juan P Daza P
 *
 */

#include "crypter.h"

void printCharArray(unsigned char *array, int array_length)
{
    int i;
    for (i=0; i < array_length; i++) {
        printf("%c", array[i]);
    }
    printf("\n");
}

void decryptFile(gcry_cipher_hd_t hd, char *filename)
{
    FILE *encrypted_file;
    unsigned char encrypted_data[MAX_DATA_LEN], plain_data[MAX_DATA_LEN];
    gcry_error_t err = 0;

    if ((encrypted_file = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Cannot open %s\n", filename);
        exit(1);
    }

    while (fgets((char *) encrypted_data, MAX_DATA_LEN, encrypted_file) != NULL) {
        err = gcry_cipher_decrypt(hd, plain_data, MAX_DATA_LEN, encrypted_data, MAX_DATA_LEN);
        if (err) {
            printf("grcy_cipher_decrypt failed: %s\n", gpg_strerror(err));
            exit(2);
        }
        gcry_cipher_reset(hd);

        //printf("entrada: ");
        //printCharArray(plain, MAX_DATA_LEN);
        printf("salida:  ");
        printCharArray(plain_data, MAX_DATA_LEN);
    }

    fclose(encrypted_file);
}

void encryptFileToFile(gcry_cipher_hd_t hd, char *plain_filename, char *encrypted_filename) 
{
    FILE *plain_file, *encrypted_file;
    unsigned char encrypted_data[MAX_DATA_LEN], plain_data[MAX_DATA_LEN];
    gcry_error_t err = 0;
    size_t elements_written;
    int blocks_to_write = 1;

    if ((plain_file = fopen(plain_filename, "r")) == NULL) {
        fprintf(stderr, "Cannot open %s\n", plain_filename);
        exit(1);
    }

    if ((encrypted_file = fopen(encrypted_filename, "w+")) == NULL) {
        fprintf(stderr, "Cannot open %s\n", encrypted_filename);
        exit(1);
    }

    while (fgets((char *) plain_data, MAX_DATA_LEN, plain_file) != NULL) {
    
        err = gcry_cipher_encrypt(hd, encrypted_data, MAX_DATA_LEN, plain_data, MAX_DATA_LEN);
        if (err) {
            printf("grcy_cipher_encrypt failed: %s\n", gpg_strerror(err));
            exit(2);
        }
        
        elements_written = fwrite(encrypted_data, MAX_DATA_LEN, blocks_to_write, encrypted_file);
        if (elements_written < blocks_to_write) {
            printf("Tried to write %d blocks but written %zu bytes\n", blocks_to_write, elements_written);
            exit(3);
        }
        gcry_cipher_reset(hd);

        //printf("entrada: ");
        //printCharArray(plain, MAX_DATA_LEN);
        //printf("salida:  ");
        //printCharArray(out, MAX_DATA_LEN);
    }

    fclose(encrypted_file);
    fclose(plain_file);
}

void encryptDecryptTest(gcry_cipher_hd_t hd, char *plain_filename)
{
    FILE *plain_file;
    unsigned char encrypted_data[MAX_DATA_LEN], plain_data[MAX_DATA_LEN];
    gcry_error_t err = 0;

    if ((plain_file = fopen(plain_filename, "r")) == NULL) {
        fprintf(stderr, "Cannot open %s\n", plain_filename);
        exit(1);
    }

    while (fgets((char *) plain_data, MAX_DATA_LEN, plain_file) != NULL) {
    
        err = gcry_cipher_encrypt(hd, encrypted_data, MAX_DATA_LEN, plain_data, MAX_DATA_LEN);
        if (err) {
            printf("grcy_cipher_encrypt failed: %s\n", gpg_strerror(err));
            exit(2);
        }
        gcry_cipher_reset(hd);

        printf("entrada: ");
        printCharArray(plain_data, MAX_DATA_LEN);
        printf("salida:  ");
        printCharArray(encrypted_data, MAX_DATA_LEN);

        err = gcry_cipher_decrypt(hd, plain_data, MAX_DATA_LEN, encrypted_data, MAX_DATA_LEN);
        gcry_cipher_reset(hd);

        printf("entrada: ");
        printCharArray(encrypted_data, MAX_DATA_LEN);
        printf("salida:  ");
        printCharArray(plain_data, MAX_DATA_LEN);
    }

    fclose(plain_file);
}

