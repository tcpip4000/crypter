#include <stdio.h>
#include <gcrypt.h>

#define MAX_DATA_LEN 100

int main()
{
    const char* libgcrypt_version = gcry_check_version(GCRYPT_VERSION);
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
    //unsigned char *out;
    char out[MAX_DATA_LEN];
    char *in = "my secret data";
    size_t outsize = sizeof(out);
    size_t insize = sizeof(in);
    gcry_cipher_encrypt(hd, out, outsize, in, insize);

    printf("entrada: %s\n", in);
    printf("salida: %s\n", out);
//gcry_error_t gcry_cipher_encrypt (gcry cipher hd t h, unsigned
//        char *out, size t outsize, const unsigned char *in, size t inlen )
//gcry_error_t gcry_cipher_decrypt (gcry cipher hd t h, unsigned
//        char *out, size t outsize, const unsigned char *in, size t inlen )

    //printf("hola mundo\n");


    // Release handler
    gcry_cipher_close(hd);

    return 0;
	
}

