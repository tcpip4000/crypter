/* crypter.c
 *
 * Copyright (C) 2008,2009
 * ER Technology
 */

#include <stdio.h>
#include <gcrypt.h>

#define MAX_DATA_LEN 16
#define MAX_REC_LEN 17

void printCharArray(unsigned char *, int);
void decryptFile(gcry_cipher_hd_t , char *);
void encryptFileToFile(gcry_cipher_hd_t, char *, char *);
void encryptDecryptTest(gcry_cipher_hd_t, char *);

int main()
{
    const char *libgcrypt_version = gcry_check_version(GCRYPT_VERSION);
    gcry_error_t err = 0;
    char key[32];
    int keylen;
    int algo = GCRY_CIPHER_SERPENT128;

    char filename[] = "modal.erc";
    char filename2[] = "modal_out.erc";
    char filename3[] = "modal_enc.erc";

    memcpy(key, "0123456789abcdef.,;/[]{}-=ABCDEF", 32);

    // cipher initialization
    if (!libgcrypt_version) {
        fputs ("libgcrypt version mismatch\n", stderr);
        exit (2);
    } else {
        printf("Using libgcrypt version: %s\n", libgcrypt_version);
    }

    // cipher settings
    gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);
    keylen = gcry_cipher_get_algo_keylen(algo);
    
    // Open cipher handler
    gcry_cipher_hd_t hd;
    gcry_cipher_open(&hd, algo, GCRY_CIPHER_MODE_OFB, 0);
    err = gcry_cipher_setkey(hd, key, keylen);
    //gcry_cipher_setiv

    //decryptFile(hd, filename3);
    //encryptFileToFile(hd, filename, filename2);
    encryptDecryptTest(hd, filename);

    // Release file and handler
    gcry_cipher_close(hd);

    return 0;
}

void printCharArray(unsigned char *array, int array_length)
{
    int i;
    for (i=0; i < array_length && array[i] != NULL; i++) {
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

    while (fgets(encrypted_data, MAX_REC_LEN, encrypted_file) != NULL) {
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

    if ((plain_file = fopen(plain_filename, "r")) == NULL) {
        fprintf(stderr, "Cannot open %s\n", plain_filename);
        exit(1);
    }

    if ((encrypted_file = fopen(encrypted_filename, "w+")) == NULL) {
        fprintf(stderr, "Cannot open %s\n", encrypted_filename);
        exit(1);
    }

    while (fgets(plain_data, MAX_REC_LEN, plain_file) != NULL) {
    
        err = gcry_cipher_encrypt(hd, encrypted_data, MAX_DATA_LEN, plain_data, MAX_DATA_LEN);
        if (err) {
            printf("grcy_cipher_encrypt failed: %s\n", gpg_strerror(err));
            exit(2);
        }
        //fputs(out, out_file);
        fwrite(encrypted_data, MAX_DATA_LEN, 1, encrypted_file);
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

    while (fgets(plain_data, MAX_REC_LEN, plain_file) != NULL) {
    
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

