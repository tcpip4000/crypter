#include <stdio.h>
#include <gcrypt.h>

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
    printf("hola mundo\n");


    // Release handler
    //gcry_cipher_close (gcry cipher hd t h )
    return 0;
	
}

