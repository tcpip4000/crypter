/* modaler.c
 *
 * Copyright (C) 2008 ER Technology
 * Juan P Daza P
 *
 */

#include "crypter.h"

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
    if (err) {
        printf("grcy_cipher_setkey failed: %s\n", gpg_strerror(err));
        exit(2);
    }
    //gcry_cipher_setiv

    //decryptFile(hd, filename3);
    //encryptFileToFile(hd, filename, filename2);
    encryptDecryptTest(hd, filename);

    // Release file and handler
    gcry_cipher_close(hd);

    return 0;
}

