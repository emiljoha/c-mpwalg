#include <stdlib.h>
#include <stdint.h>
#include <sodium.h>
#include <string.h>
#include <arpa/inet.h>

int key(const char* password,
        size_t password_size,
        const char* name,
        size_t name_size,
        uint8_t buf[64]) {
  if (sodium_init() == -1) {
        return -1;
  }
  uint32_t name_size_32 = (uint32_t) name_size;
  size_t seed_length = \
    sizeof("com.lyndir.masterpassword") - 1 + \
    sizeof(".") - 1 + \
    sizeof(typeof(name_size_32)) + \
    sizeof(".") - 1 + \
    name_size_32 * sizeof(typeof(*name));
  char* const seed = (char*) malloc(seed_length);
  if (seed == NULL) {
    return -1;
  }
  memcpy(seed, "com.lyndir.masterpassword",
         sizeof("com.lyndir.masterpassword") - 1);
  size_t position = sizeof("com.lyndir.masterpassword") - 1;
  memcpy(seed + position, ".", sizeof(".") - 1);
  position = position + sizeof(".") - 1;
  uint32_t name_size_32_big_endian = htonl(name_size_32); // Make sure it is big endian.
  memcpy(seed + position, &(name_size_32_big_endian), sizeof(name_size_32_big_endian));
  position = position + sizeof(uint32_t) - 1;
  memcpy(seed + position, ".", sizeof(".") - 1);
  position = position + sizeof(".") - 1;
  memcpy(seed + position, name, name_size_32);
  uint64_t N = 32768;
  uint32_t r = 8;
  uint32_t p = 2;
  size_t buflen = 64;
  int code = crypto_pwhash_scryptsalsa208sha256_ll((uint8_t*)password,
                                                   password_size,
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

int main() {
  const char password[] = "password";
  const char name[] = "name";
  uint8_t result[64];
  key(password, sizeof(password), name, sizeof(name), result);
  for (int i = 0; i < 64; i++)
    printf("%x", result[i]);
  printf("\n");
}
