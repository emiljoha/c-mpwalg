#include <stdlib.h>
#include <stdint.h>
#include <sodium.h>
#include <string.h>
#include <arpa/inet.h>
#include "mpw.h"

int main() {
  const char main_password[] = "password";
  const char name[] = "name";
  const char site_name[] = "example.org";
  uint32_t counter = 1;
  uint8_t identity[64];
  key(main_password, sizeof(main_password), name, sizeof(name), identity);
  uint8_t site_identity[32];
  site_key(site_name, sizeof(site_name), identity, counter, site_identity);
  char result[21];
  password(site_identity, "Long", sizeof("Long"), result, 21);
  printf("%s\n", result);
  //hex(site_identity, 32);
}
