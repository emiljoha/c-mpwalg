#include <stdlib.h>
#include <stdint.h>

void hex(const uint8_t* const buf, size_t buf_size);

int key(const char* password,
        size_t password_size,
        const char* name,
        uint32_t name_size,
        uint8_t* buf);
