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
}
