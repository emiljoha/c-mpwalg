#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "templates.h"

size_t max(size_t a, size_t b) {
  if (a < b)
    return b;
  else
    return a;
}

bool is_template(const char* string,
                 size_t string_size,
                 const char* template,
                 size_t template_size) {
  return strncmp(string,
                 template,
                 max(string_size, template_size)) == 0;
}

int number_of_templates(const char* template_class,
                        size_t template_class_size) {
  if (is_template(template_class, template_class_size, MAXIMUM, sizeof(MAXIMUM)))
    return NUM_MAXIMUM;
  else if (is_template(template_class, template_class_size, LONG, sizeof(LONG)))
    return NUM_LONG;
  else if (is_template(template_class, template_class_size, MEDIUM, sizeof(MEDIUM)))
    return NUM_MEDIUM;
  else if (is_template(template_class, template_class_size, SHORT, sizeof(SHORT)))
    return NUM_SHORT;
  else if (is_template(template_class, template_class_size, BASIC, sizeof(BASIC)))
    return NUM_BASIC;
  else if (is_template(template_class, template_class_size, PIN, sizeof(PIN)))
    return NUM_PIN;
  else if (is_template(template_class, template_class_size, NAME, sizeof(NAME)))
    return NUM_NAME;
  else if (is_template(template_class, template_class_size, PHARSE, sizeof(PHARSE)))
    return NUM_PHRASE;
  else
    return 0;
}

int template(const char* template_class,
             size_t template_class_size,
             size_t template_number,
             char* buf,
             size_t buf_size) {
  if (buf_size < MAX_SIZE_TEMPLATE) {
    return -1;
  }
  if (is_template(template_class, template_class_size, MAXIMUM, sizeof(MAXIMUM)))
    switch (template_number) {
    case 0:
      strncpy(buf, MAXIMUM_0, buf_size);
      break;
    case 1:
      strncpy(buf, MAXIMUM_1, buf_size);
      break;
    default:
      return -1;
    }
  else if (is_template(template_class, template_class_size, LONG, sizeof(LONG)))
    switch (template_number) {
    case 0:
      strncpy(buf, LONG_0, buf_size);
      break;
    case 1:
      strncpy(buf, LONG_1, buf_size);
      break;
    case 2:
      strncpy(buf, LONG_2, buf_size);
      break;
    case 3:
      strncpy(buf, LONG_3, buf_size);
      break;
    case 4:
      strncpy(buf, LONG_4, buf_size);
      break;
    case 5:
      strncpy(buf, LONG_5, buf_size);
      break;
    case 6:
      strncpy(buf, LONG_6, buf_size);
      break;
    case 7:
      strncpy(buf, LONG_7, buf_size);
      break;
    case 8:
      strncpy(buf, LONG_8, buf_size);
      break;
    case 9:
      strncpy(buf, LONG_9, buf_size);
      break;
    case 10:
      strncpy(buf, LONG_10, buf_size);
      break;
    case 11:
      strncpy(buf, LONG_11, buf_size);
      break;
    case 12:
      strncpy(buf, LONG_12, buf_size);
      break;
    case 13:
      strncpy(buf, LONG_13, buf_size);
      break;
    case 14:
      strncpy(buf, LONG_14, buf_size);
      break;
    case 15:
      strncpy(buf, LONG_15, buf_size);
      break;
    case 16:
      strncpy(buf, LONG_16, buf_size);
      break;
    case 17:
      strncpy(buf, LONG_17, buf_size);
      break;
    case 18:
      strncpy(buf, LONG_18, buf_size);
      break;
    case 19:
      strncpy(buf, LONG_19, buf_size);
      break;
    case 20:
      strncpy(buf, LONG_20, buf_size);
      break;
    default:
      return -1;
    }
  else if (is_template(template_class, template_class_size, MEDIUM, sizeof(MEDIUM)))
    switch (template_number) {
    case 0:
      strncpy(buf, MEDIUM_0, buf_size);
      break;
    case 1:
      strncpy(buf, MEDIUM_1, buf_size);
      break;
    default:
      return -1;
    }
  else if (is_template(template_class, template_class_size, SHORT, sizeof(SHORT)))
    switch (template_number) {
    case 0:
      strncpy(buf, SHORT_0, buf_size);
      break;
    default:
      return -1;
    }
  else if (is_template(template_class, template_class_size, BASIC, sizeof(BASIC)))
    switch (template_number) {
    case 0:
      strncpy(buf, BASIC_0, buf_size);
      break;
    case 1:
      strncpy(buf, BASIC_1, buf_size);
      break;
    default:
      return -1;
    }
  else if (is_template(template_class, template_class_size, PIN, sizeof(PIN)))
    switch (template_number) {
    case 0:
      strncpy(buf, PIN_0, buf_size);
      break;
    default:
      return -1;
    }
  else if (is_template(template_class, template_class_size, NAME, sizeof(NAME)))
    switch (template_number) {
    case 0:
      strncpy(buf, NAME_0, buf_size);
      break;
    default:
      return -1;
    }
  else if (is_template(template_class, template_class_size, PHARSE, sizeof(PHARSE)))
    switch (template_number) {
    case 0:
      strncpy(buf, PHRASE_0, buf_size);
      break;
    case 1:
      strncpy(buf, PHRASE_1, buf_size);
      break;
    case 2:
      strncpy(buf, PHRASE_2, buf_size);
      break;
    default:
      return -1;
    }
  else
    return -1;
  return 0;
}

int template_characters(char template_char,
                        char* buf, size_t buf_size) {
  if (buf_size < MAX_LENGTH_CHARACTERS_CATEGORY_STRING)
    return -1;
  switch (template_char) {
  case 'V': {
    strncpy(buf, V_CHARACTERS, buf_size);
    break;
  }
  case 'C': {
    strncpy(buf, C_CHARACTERS, buf_size);
    break;
  }
  case 'v': {
    strncpy(buf, v_CHARACTERS, buf_size);
    break;
  }
  case 'c': {
    strncpy(buf, c_CHARACTERS, buf_size);
    break;
  }
  case 'A': {
    strncpy(buf, A_CHARACTERS, buf_size);
    break;
  }
  case 'a': {
    strncpy(buf, a_CHARACTERS, buf_size);
    break;
  }
  case 'n': {
    strncpy(buf, n_CHARACTERS, buf_size);
    break;
  }
  case 'o': {
    strncpy(buf, o_CHARACTERS, buf_size);
    break;
  }
  case 'x': {
    strncpy(buf, x_CHARACTERS, buf_size);
    break;
  }
  case ' ': {
    strncpy(buf, space_CHARACTERS, buf_size);
    break;
  }
  default:
    return -1;
  }
  return 0;
}
