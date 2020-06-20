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

void memcpy3(void* destination,
             const void* a, size_t a_size,
             const void* b, size_t b_size,
             const void* c, size_t c_size) {
  memcpy(destination,
         a, a_size);
  memcpy(destination + a_size,
         b, b_size);
  memcpy(destination + a_size + b_size,
         c, c_size);
}

void memcpy4(void* destination,
             const void* a, size_t a_size,
             const void* b, size_t b_size,
             const void* c, size_t c_size,
             const void* d, size_t d_size) {
  memcpy3(destination,
          a, a_size,
          b, b_size,
          c, c_size);
  memcpy(destination + a_size + b_size + c_size,
         d, d_size);
}

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
  memcpy3(seed,
          scope, sizeof(scope) - 1,
          &(name_size_32_big_endian), sizeof(name_size_32_big_endian),
          name, name_size - 1);
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

int site_key(const char* site_name,
             size_t site_name_length,
             const uint8_t key[64],
             uint32_t counter,
             uint8_t buf[64]) {
  const char scope[] = "com.lyndir.masterpassword";
  uint32_t name_size_32_big_endian = htonl((uint32_t)(site_name_length - 1));
  uint32_t counter_32_big_endian = htonl((uint32_t)(counter));
  size_t seed_length = \
    sizeof(scope) - 1 + \
    sizeof(name_size_32_big_endian) + \
    site_name_length - 1 + \
    sizeof(counter_32_big_endian);
  unsigned char* const seed = (unsigned char*) malloc(seed_length);
  if (seed == NULL) {
    return -1;
  }
  memcpy4(seed,
          scope, sizeof(scope) - 1,
          &(name_size_32_big_endian), sizeof(name_size_32_big_endian),
          site_name, site_name_length - 1,
          &(counter_32_big_endian), sizeof(counter_32_big_endian));
  crypto_auth_hmacsha256_state state;
  size_t key_length = 64;
  if (crypto_auth_hmacsha256_init(&state, key, key_length) != 0) {
    free(seed);
    return -1;
  }
  if (crypto_auth_hmacsha256_update(&state, seed, seed_length) != 0) {
    free(seed);
    return -1;
  }
  int return_code = crypto_auth_hmacsha256_final(&state, buf);
  free(seed);
  return return_code;
}
