#include <stdlib.h>
#include <stdint.h>
#include <sodium.h>
#include <string.h>
#include <arpa/inet.h>
#include "mpw.h"

int main() {
  const char password[] = "password";
  const char name[] = "name";
  const char site_name[] = "example.org";
  uint32_t counter = 1;
  uint8_t identity[64];
  key(password, sizeof(password), name, sizeof(name), identity);
  uint8_t site_identity[32];
  site_key(site_name, sizeof(site_name), identity, counter, site_identity);
  hex(site_identity, 32);
}
