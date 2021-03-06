#include <stdlib.h>
#include <stdint.h>
#include <sodium.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "templates.h"

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

int main_key(const char* secret,
             size_t secret_length,
             const char* name,
             size_t name_size,
             uint8_t result_buffer[64],
             size_t result_buffer_size) {
  if (result_buffer_size != 64) {
    printf("mpw::main_key result_buffer must have size 64\n");
  }
  const char scope[] = "com.lyndir.masterpassword";
  uint32_t name_size_32_big_endian = htonl((uint32_t)(name_size - 1));
  size_t seed_length =
    sizeof(scope) - 1 + sizeof(name_size_32_big_endian) + name_size - 1;
  char* const seed = (char*) malloc(seed_length);
  if (seed == NULL) {
    printf("mpw::main_key Failed to allocate memmory for seed\n");
    return -1;
  }
  memcpy3(seed,
          scope, sizeof(scope) - 1,
          &(name_size_32_big_endian), sizeof(name_size_32_big_endian),
          name, name_size - 1);
  uint64_t N = 32768U;
  uint32_t r = 8U;
  uint32_t p = 2U;
  int code = crypto_pwhash_scryptsalsa208sha256_ll((uint8_t*)secret,
                                                   secret_length,
                                                   (uint8_t*)seed,
                                                   seed_length,
                                                   N,
                                                   r,
                                                   p,
                                                   result_buffer,
                                                   result_buffer_size);
  free(seed);
  return code;
}

int site_key(const char* site_name,
             size_t site_name_length,
             const uint8_t key[64],
             size_t key_size,
             uint32_t counter,
             uint8_t result_buffer[32],
             size_t result_buffer_size) {
  if (key_size != 64) {
    printf("mpw::site_key: key must have size 64\n");
    return -1;
  }
  if (result_buffer_size != 32) {
    printf("mpw::site_key: result_buffer must have size 64\n");
    return -1;
  }
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
  if (crypto_auth_hmacsha256_init(&state, key, key_size) != 0) {
    free(seed);
    return -1;
  }
  if (crypto_auth_hmacsha256_update(&state, seed, seed_length) != 0) {
    free(seed);
    return -1;
  }
  int return_code = crypto_auth_hmacsha256_final(&state, result_buffer);
  free(seed);
  return return_code;
}

int site_password(uint8_t site_key[32],
                  size_t site_key_size,
                  const char* result_type,
                  size_t result_type_size,
                  char* result_buffer,
                  size_t result_buffer_size){
  if (site_key_size != 32) {
    printf("mpw:site_password site_key must have size 32\n");
    return -1;
  }
  int num_templates_for_class = number_of_templates(result_type,
                                                    result_type_size);
  if (num_templates_for_class == 0) {
    printf("mpw::password Template does not exists.\n");
    return -1;
  }
  char template_buffer[MAX_SIZE_TEMPLATE];
  if (template(result_type,
               result_type_size,
               site_key[0] % num_templates_for_class,
               template_buffer,
               MAX_SIZE_TEMPLATE) != 0) {
    printf("Could not find template\n");
    return -1;
  }
  size_t template_length = strnlen(template_buffer, MAX_SIZE_TEMPLATE);
  if (result_buffer_size < template_length) {
    printf("mpw::password Buffer not large enough to hold password.\n");
    return -1;
  }
  char pass_chars[MAX_LENGTH_CHARACTERS_CATEGORY_STRING];
  for (size_t i = 0; i < template_length; i++) {
    template_characters(template_buffer[i],
                        pass_chars,
                        MAX_LENGTH_CHARACTERS_CATEGORY_STRING);
    int pass_char_len = strnlen(pass_chars, MAX_LENGTH_CHARACTERS_CATEGORY_STRING);
    result_buffer[i] = pass_chars[site_key[i+1] % pass_char_len];
  }
  return 0;
}

int password(const char* secret,
             size_t secret_size,
             const char* site_name,
             size_t site_name_size,
             const char* full_name,
             size_t full_name_size,
             const char* site_result_type,
             size_t site_result_type_size,
             size_t counter,
             char* result_buffer,
             size_t result_buffer_size) {
  uint8_t main_key_buffer[64];
  if (main_key(secret,
               secret_size,
               full_name,
               full_name_size,
               main_key_buffer,
               sizeof(main_key_buffer)) != 0) {
    printf("mpw:password Failed to generate main key\n");
    return -1;
  }
  uint8_t site_key_buffer[32];
  if (site_key(site_name,
               site_name_size,
               main_key_buffer,
               sizeof(main_key_buffer),
               counter,
               site_key_buffer,
               sizeof(site_key_buffer)) != 0) {
    printf("mpw:password Failed to generate site key\n");
    return -1;
  }
  if (site_password(site_key_buffer,
                    sizeof(site_key_buffer),
                    site_result_type,
                    site_result_type_size,
                    result_buffer,
                    result_buffer_size) != 0) {
    printf("mpw:password Failed to generate site password\n");
    return -1;
  }
  return 0;
}
