#include <stdlib.h>
#include <stdint.h>
#include <sodium.h>
#include <string.h>
#include <arpa/inet.h>
#include "mpw.h"

int main() {
  char password_buffer[MAX_SIZE_PASSWORD];
  password("password",
           sizeof("password"),
           "example.org",
           sizeof("example.org"),
           "name",
           sizeof("name"),
           "Long",
           sizeof("Long"),
           1,
           password_buffer,
           sizeof(password_buffer));
  printf("%s\n", password_buffer);
  return 0;
  /*
  const char secret[] = "password";
  const char name[] = "name";
  const char site_name[] = "example.org";
  uint32_t counter = 1;
  uint8_t key[64];
  main_key(secret, sizeof(secret),
           name, sizeof(name),
           key, sizeof(key));
  uint8_t site_identity[32];
  site_key(site_name, sizeof(site_name), key, counter, site_identity);
  char site_password_buffer[MAX_SIZE_PASSWORD];
  site_password(site_identity,
                "Long",
                sizeof("Long"),
                site_password_buffer,
                MAX_SIZE_PASSWORD);
  printf("%s\n", site_password_buffer);
  */
}
