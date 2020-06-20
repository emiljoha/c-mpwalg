#include <stdlib.h>
#include <stdint.h>
#include <sodium.h>
#include <string.h>
#include <arpa/inet.h>

void hex(const uint8_t* const buf, size_t buf_size) {
  for (size_t i = 0; i < buf_size; i++)
    printf("%x", buf[i]);
  printf("\n");
}

/**
   Phase 1: Your identity

   Your identity is defined by your key. This key unlocks all of your doors.
   Your master key is the cryptographic result of two components:

   1.Your <name> (identification)
   2.Your <master password> (authentication)

   Your master password is your personal secret and your name scopes that secret
   to your identity.  Together, they create a cryptographic identifier that
   is unique to your person.

   ´´´
   masterKey = SCRYPT( key, seed, N, r, p, dkLen )
   key = <master password>
   seed = scope + LEN(<name>) + <name>
   N = 32768
   r = 8
   p = 2
   dkLen = 64
   ´´´

   We employ the SCRYPT cryptographic function to derive a 64-byte
   cryptographic key from the user’s name and master password using a fixed
   set of parameters.
**/
int key(const char* password,
        size_t password_size,
        const char* name,
        size_t name_size,
        uint8_t buf[64]) {
  const char scope[] = "com.lyndir.masterpassword";
  uint32_t name_size_32_big_endian = htonl((uint32_t)(name_size - 1));
  size_t seed_length = \
    sizeof(scope) - 1 + \
    sizeof(name_size_32_big_endian) + \
    name_size - 1;
  char* const seed = (char*) malloc(seed_length);
  if (seed == NULL) {
    return -1;
  }
  memcpy(seed, scope, sizeof(scope) - 1);
  memcpy(seed + sizeof(scope) - 1,
         &(name_size_32_big_endian),
         sizeof(name_size_32_big_endian));
  memcpy(seed + sizeof(scope) - 1 + sizeof(name_size_32_big_endian),
         name,
         name_size - 1);
  uint64_t N = 32768U;
  uint32_t r = 8U;
  uint32_t p = 2U;
  size_t buflen = 64;
  int code = crypto_pwhash_scryptsalsa208sha256_ll((uint8_t*)password,
                                                   password_size - 1,
                                                   (uint8_t*)seed,
                                                   seed_length,
                                                   N,
                                                   r,
                                                   p,
                                                   buf,
                                                   buflen);
  free(seed);
  return code;
}
