#include <stdio.h>
#include <gcrypt.h>

#define MAX_DATA_LEN 16
#define MAX_REC_LEN 1024

int printCharArray(unsigned char *, int);

int main()
{
    const char *libgcrypt_version = gcry_check_version(GCRYPT_VERSION);
    gcry_error_t err = 0;
    char key[32];
    int keylen;
    unsigned char out[MAX_DATA_LEN], in[MAX_DATA_LEN], plain[MAX_DATA_LEN];

    memcpy(key, "0123456789abcdef.,;/[]{}-=ABCDEF", 32);

    FILE *data_file;
    char filename[] = "modal.erc";

    if ((data_file = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Cannot open %s\n", filename);
        exit(1);
    }

    // cipher initialization
    if (!libgcrypt_version) {
        fputs ("libgcrypt version mismatch\n", stderr);
        exit (2);
    } else {
        printf("Using libgcrypt version: %s\n", libgcrypt_version);
    }

    // cipher settings
    gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);
    keylen = gcry_cipher_get_algo_keylen(GCRY_CIPHER_SERPENT128);
    
    // Open cipher handler
    gcry_cipher_hd_t hd;
    gcry_cipher_open(&hd, GCRY_CIPHER_SERPENT128, GCRY_CIPHER_MODE_OFB, 0);

    err = gcry_cipher_setkey(hd, key, keylen);
    //gcry_cipher_setiv
    
    while (fgets(plain, MAX_REC_LEN, data_file) != NULL) {
    
        err = gcry_cipher_encrypt(hd, out, MAX_DATA_LEN, plain, MAX_DATA_LEN);
        gcry_cipher_reset(hd);

        printf("entrada: ");
        printCharArray(plain, MAX_DATA_LEN);
        printf("salida:  ");
        printCharArray(out, MAX_DATA_LEN);

        err = gcry_cipher_decrypt(hd, in, MAX_DATA_LEN, out, MAX_DATA_LEN);
        gcry_cipher_reset(hd);

        printf("entrada: ");
        printCharArray(out, MAX_DATA_LEN);
        printf("salida:  ");
        printCharArray(in, MAX_DATA_LEN);
    }

    //gcry_error_t gcry_cipher_encrypt (gcry cipher hd t h, unsigned
    //        char *out, size t outsize, const unsigned char *in, size t inlen )
    //gcry_error_t gcry_cipher_decrypt (gcry cipher hd t h, unsigned
    //        char *out, size t outsize, const unsigned char *in, size t inlen )

    // Release file and handler
    gcry_cipher_close(hd);
    fclose(data_file);

    return 0;
	
}

int printCharArray(unsigned char *array, int array_length)
{
    int i;
    for (i=0; i < array_length && array[i] != NULL; i++) {
        printf("%c", array[i]);
    }
    printf("\n");
    return 0;
}
