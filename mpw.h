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

/**
   Phase 2: Your site key "com.lyndir.masterpassword"

   Your site key is a derivative from your master key when it is used to
   unlock the door to a specific site. Your site key is the result of two
   components:

   1.Your <site name> (identification)
   2.Your <masterkey> (authentication)
   3.Your <site counter> 

   Your master key ensures only your identity has access to this key and your
   site name scopes the key to your site.  The site counter ensures you can
   easily create new keys for the site should a key become
   compromised. Together, they create a cryptographic identifier that is
   unique to your account at this site.

   siteKey = HMAC-SHA-256( key, seed )
   key = <master key>
   seed = scope . LEN(<site name>) . <site name> . <counter>

   We employ the HMAC-SHA-256 cryptographic function to derive a 32-byte
   cryptographic site key from the from the site name and master key scoped
   to a given counter value.
**/
int site_key(const char* site_name,
             size_t site_name_length,
             const uint8_t key[64],
             uint32_t counter,
             uint8_t buf[32]);
