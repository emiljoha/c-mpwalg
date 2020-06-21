#include <stdlib.h>
#include <stdint.h>

#define MAX_SIZE_PASSWORD 21

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
             size_t result_buffer_size);

int main_key(const char* secret,
             size_t secret_size,
             const char* name,
             size_t name_size,
             uint8_t* result_buffer,
             size_t result_buffer_size);

int site_key(const char* site_name,
             size_t site_name_length,
             const uint8_t key[64],
             size_t key_size,
             uint32_t counter,
             uint8_t result_buffer[32],
             size_t result_buffer_size);

int site_password(uint8_t site_key[32],
                  const char* result_type,
                  size_t result_type_size,
                  char* result_buffer,
                  size_t result_buffer_size);
