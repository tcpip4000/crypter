
#include <stdio.h>
#include <gcrypt.h>

#define MAX_DATA_LEN 16
#define MAX_REC_LEN 17

void printCharArray(unsigned char *, int);

int main()
{
    const char *libgcrypt_version = gcry_check_version(GCRYPT_VERSION);
    unsigned char out[MAX_DATA_LEN], in[MAX_DATA_LEN], plain[MAX_DATA_LEN];
    gcry_error_t err = 0;
    char key[32];
    int keylen;
    int algo = GCRY_CIPHER_SERPENT128;

    FILE *data_file, *out_file; 
    FILE *encrypted_file;
    char filename[] = "modal.erc";
    char filename2[] = "modal_out.erc";
    char filename3[] = "modal_enc.erc";

    memcpy(key, "0123456789abcdef.,;/[]{}-=ABCDEF", 32);

    // check file existence
    if ((data_file = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Cannot open %s\n", filename);
        exit(1);
    }
    if ((encrypted_file = fopen(filename3, "r")) == NULL) {
        fprintf(stderr, "Cannot open %s\n", filename3);
        exit(1);
    }
    if ((out_file = fopen(filename2, "w+")) == NULL) {
        fprintf(stderr, "Cannot open %s\n", filename2);
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
    keylen = gcry_cipher_get_algo_keylen(algo);
    
    // Open cipher handler
    gcry_cipher_hd_t hd;
    gcry_cipher_open(&hd, algo, GCRY_CIPHER_MODE_OFB, 0);
    err = gcry_cipher_setkey(hd, key, keylen);
    //gcry_cipher_setiv
    
    while (fgets(plain, MAX_REC_LEN, encrypted_file) != NULL) {
    
        err = gcry_cipher_decrypt(hd, in, MAX_DATA_LEN, plain, MAX_DATA_LEN);
        gcry_cipher_reset(hd);

        //printf("entrada: ");
        //printCharArray(plain, MAX_DATA_LEN);
        printf("salida:  ");
        printCharArray(in, MAX_DATA_LEN);
    }

    //while (fgets(plain, MAX_REC_LEN, data_file) != NULL) {
    //
    //    err = gcry_cipher_encrypt(hd, out, MAX_DATA_LEN, plain, MAX_DATA_LEN);
    //    //fputs(out, out_file);
    //    fwrite(out,MAX_DATA_LEN,1,out_file);
    //    gcry_cipher_reset(hd);

    //    //printf("entrada: ");
    //    //printCharArray(plain, MAX_DATA_LEN);
    //    //printf("salida:  ");
    //    //printCharArray(out, MAX_DATA_LEN);
    //}

    //while (fgets(plain, MAX_REC_LEN, data_file) != NULL) {
    //
    //    err = gcry_cipher_encrypt(hd, out, MAX_DATA_LEN, plain, MAX_DATA_LEN);
    //    gcry_cipher_reset(hd);

    //    printf("entrada: ");
    //    printCharArray(plain, MAX_DATA_LEN);
    //    printf("salida:  ");
    //    printCharArray(out, MAX_DATA_LEN);

    //    err = gcry_cipher_decrypt(hd, in, MAX_DATA_LEN, out, MAX_DATA_LEN);
    //    gcry_cipher_reset(hd);

    //    printf("entrada: ");
    //    printCharArray(out, MAX_DATA_LEN);
    //    printf("salida:  ");
    //    printCharArray(in, MAX_DATA_LEN);
    //}

    // Release file and handler
    gcry_cipher_close(hd);
    fclose(data_file);
    fclose(out_file);
    fclose(encrypted_file);

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

