#include <stdio.h>
#include <gcrypt.h>

#define MAX_DATA_LEN 16

int main()
{
    const char* libgcrypt_version = gcry_check_version(GCRYPT_VERSION);
    gcry_error_t err = 0;
    // libgcrypt initialization
    if (!libgcrypt_version) {
        fputs ("libgcrypt version mismatch\n", stderr);
        exit (2);
    } else {
        printf("Using libgcrypt version: %s\n", libgcrypt_version);
    }

    // Initialization complete
    gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);

    // main actions
    // gcry_error_t gcry_cipher_open (gcry cipher hd t *hd, int algo, int
    //         mode, unsigned int flags )
    //
    // Open cipher handler
    gcry_cipher_hd_t hd;
    gcry_cipher_open(&hd, GCRY_CIPHER_SERPENT128, GCRY_CIPHER_MODE_OFB, 0);

    //gcry_cipher_setkey
    //gcry_cipher_setiv

    //gcry_error_t gcry_cipher_setkey (gcry cipher hd t h, const void *k, size t l )
    unsigned char out[MAX_DATA_LEN], in[MAX_DATA_LEN], plain[MAX_DATA_LEN];
    memcpy(plain, "foobar42FOOBAR17", 16);
    err = gcry_cipher_encrypt(hd, out, MAX_DATA_LEN, plain, MAX_DATA_LEN);

    printf("entrada: %s\n", plain);
    printf("salida: %s\n", out);

    gcry_cipher_reset (hd);

    err = gcry_cipher_decrypt(hd, in, MAX_DATA_LEN, out, MAX_DATA_LEN);

    printf("entrada: %s\n", out);
    printf("salida: %s\n", in);

    //gcry_error_t gcry_cipher_encrypt (gcry cipher hd t h, unsigned
    //        char *out, size t outsize, const unsigned char *in, size t inlen )
    //gcry_error_t gcry_cipher_decrypt (gcry cipher hd t h, unsigned
    //        char *out, size t outsize, const unsigned char *in, size t inlen )

    // Release handler
    gcry_cipher_close(hd);

    return 0;
	
}

