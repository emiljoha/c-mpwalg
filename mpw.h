#include <stdlib.h>
#include <stdint.h>

void hex(const uint8_t* const buf, size_t buf_size);

/**
   Phase 1: Your identity

   We employ the SCRYPT cryptographic function to derive a 64-byte
   cryptographic key from the user’s name and master password using a fixed
   set of parameters.

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

   scope and name are coded as UTF-8.
   LEN(<name>) is represented as a 32 bit- big-endian-, unsigned-integer.

**/
int key(const char* password,
        size_t password_size,
        const char* name,
        uint32_t name_size,
        uint8_t* buf);
