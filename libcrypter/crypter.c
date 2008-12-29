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

    fread(encrypted_data, MAX_DATA_LEN, 1, encrypted_file);
    while (!feof(encrypted_file) && !ferror(encrypted_file)) {
        err = gcry_cipher_decrypt(hd, plain_data, MAX_DATA_LEN, encrypted_data, MAX_DATA_LEN);
        if (err) {
            printf("grcy_cipher_decrypt failed: %s\n", gpg_strerror(err));
            exit(2);
        }
        gcry_cipher_reset(hd);

        printf("entrada: ");
        printCharArray(encrypted_data, MAX_DATA_LEN);
        printf("salida:  ");
        printCharArray(plain_data, MAX_DATA_LEN);
        fread(encrypted_data, MAX_DATA_LEN, 1, encrypted_file);
    }

    fclose(encrypted_file);
}

void decryptFileToFile(gcry_cipher_hd_t hd, char *encrypted_filename, char *plain_filename)
{
    FILE *plain_file, *encrypted_file;
    unsigned char encrypted_data[MAX_DATA_LEN], plain_data[MAX_DATA_LEN];
    gcry_error_t err = 0;
    size_t elements_written;
    int blocks_to_write = 1;

    if ((plain_file = fopen(plain_filename, "w+")) == NULL) {
        fprintf(stderr, "Cannot open %s\n", plain_filename);
        exit(1);
    }

    if ((encrypted_file = fopen(encrypted_filename, "r")) == NULL) {
        fprintf(stderr, "Cannot open %s\n", encrypted_filename);
        exit(1);
    }

    fread(encrypted_data, MAX_DATA_LEN, 1, encrypted_file);
    while (!feof(encrypted_file) && !ferror(encrypted_file)) {
        err = gcry_cipher_decrypt(hd, plain_data, MAX_DATA_LEN, encrypted_data, MAX_DATA_LEN);
        if (err) {
            printf("grcy_cipher_decrypt failed: %s\n", gpg_strerror(err));
            exit(2);
        }
        elements_written = fwrite(plain_data, MAX_DATA_LEN, blocks_to_write, plain_file);
        if (elements_written < blocks_to_write) {
            printf("Tried to write %d blocks but written %zu bytes\n", blocks_to_write, elements_written);
            exit(3);
        }
        gcry_cipher_reset(hd);
        fread(encrypted_data, MAX_DATA_LEN, 1, encrypted_file);
    }

    fflush(plain_file);
    fclose(plain_file);
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

    while (!feof(plain_file) && !ferror(plain_file)) { 
        //memcpy(plain_data, "                                ", MAX_DATA_LEN);
        fillCharVectorWithSpaces(plain_data, MAX_DATA_LEN);
        fread(plain_data, MAX_DATA_LEN, 1, plain_file);
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
    }

    fflush(encrypted_file);
    fclose(encrypted_file);
    fclose(plain_file);
}

void encryptDecryptTest(gcry_cipher_hd_t hd, char *plain_filename)
{
    FILE *plain_file;
    unsigned char encrypted_data[MAX_DATA_LEN], plain_data[MAX_DATA_LEN];
    gcry_error_t err = 0;
    int blocks_to_read = 1;

    if ((plain_file = fopen(plain_filename, "r")) == NULL) {
        fprintf(stderr, "Cannot open %s\n", plain_filename);
        exit(1);
    }

    while (!feof(plain_file) && !ferror(plain_file)) {
        //memcpy(plain_data, "                                ", MAX_DATA_LEN);
        fillCharVectorWithSpaces(plain_data, MAX_DATA_LEN);
        fread(plain_data, MAX_DATA_LEN, blocks_to_read, plain_file); 

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

void fillCharVectorWithSpaces(unsigned char vector[], int len) 
{
        for (int i=0; i < len; i++)
            vector[i] = ' ';
}
