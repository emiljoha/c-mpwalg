#include <stdlib.h>
#include <stdint.h>
#include <sodium.h>
#include <string.h>
#include <arpa/inet.h>
#include "mpw.h"

int main() {
  const char password[] = "password";
  const char name[] = "name";
  uint8_t result[64];
  key(password, sizeof(password), name, sizeof(name), result);
  //printf("Result:\n");
  hex(result, 64);
}
