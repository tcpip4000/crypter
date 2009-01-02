/* modalgen.c
 *
 * Copyright (C) 2008 ER Technology
 * Juan P Daza P
 *
 */

#include "crypter.h"

int main(int argc, const char *argv[])
{
    const char *libgcrypt_version = gcry_check_version(GCRYPT_VERSION);
    gcry_error_t err = 0;
    char *key;
    int keylen;
    int algo = GCRY_CIPHER_SERPENT128;
    char *filename, *filename2;
    
    if (argc != 4) {
        printf("Wrong parameter quantity\n");
        exit(1);
    }

    filename = argv[1];
    filename2 = argv[2];
    key = argv[3];

    // cipher initialization
    if (!libgcrypt_version) {
        fputs ("libgcrypt version mismatch or not installed\n", stderr);
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
    if (err) {
        printf("grcy_cipher_setkey failed: %s\n", gpg_strerror(err));
        exit(2);
    }
    //gcry_cipher_setiv

    encryptFileToFile(hd, filename, filename2);

    // Release handler
    gcry_cipher_close(hd);

    return 0;
}

