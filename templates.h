#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <stdlib.h>

#define MAX_SIZE_TEMPLATE 21
#define MAX_NUM_TEMPLATES_PER_TYPE 21

#define MAXIMUM "Maximum"
#define NUM_MAXIMUM 2
#define MAXIMUM_0 "anoxxxxxxxxxxxxxxxxx"
#define MAXIMUM_1 "axxxxxxxxxxxxxxxxxno"

#define LONG "Long"
#define NUM_LONG 21
#define LONG_0 "CvcvnoCvcvCvcv"
#define LONG_1 "CvcvCvcvCvccno"
#define LONG_2 "CvcvCvcvCvcvno"
#define LONG_3 "CvccnoCvcvCvcv"
#define LONG_4 "CvccCvcvnoCvcv"
#define LONG_5 "CvccCvcvCvcvno"
#define LONG_6 "CvcvnoCvccCvcv"
#define LONG_7 "CvcvCvccnoCvcv"
#define LONG_8 "CvcvCvccCvcvno"
#define LONG_9 "CvcvnoCvcvCvcc"
#define LONG_10 "CvcvCvcvnoCvcc"
#define LONG_11 "CvcvCvcvCvccno"
#define LONG_12 "CvcvCvcvCvccno"
#define LONG_13 "CvccCvccnoCvcv"
#define LONG_14 "CvccCvccCvcvno"
#define LONG_15 "CvcvnoCvccCvcc"
#define LONG_16 "CvcvCvccnoCvcc"
#define LONG_17 "CvcvCvccCvccno"
#define LONG_18 "CvccnoCvcvCvcc"
#define LONG_19 "CvccCvcvnoCvcc"
#define LONG_20 "CvccCvcvCvccno"

#define MEDIUM "Medium"
#define NUM_MEDIUM 2
#define MEDIUM_0 "CvcnoCvc"
#define MEDIUM_1 "CvcCvcno"

#define SHORT "Short"
#define NUM_SHORT 1
#define SHORT_0 "Cvcn"

#define BASIC "Basic"
#define NUM_BASIC 2
#define BASIC_0 "aaanaaan"
#define BASIC_1 "aannaaan"

#define PIN "PIN"
#define NUM_PIN 1
#define PIN_0 "nnnn"

#define NAME "Name"
#define NUM_NAME 1
#define NAME_0 "cvccvcvcv"

#define PHARSE "Pharse"
#define NUM_PHRASE 3
#define PHRASE_0 "cvcc cvc cvccvcv cvc"
#define PHRASE_1 "cv cvccv cvc cvcvccv"
#define PHRASE_2 "cvc cvccvcvcv cvcv"

#define V_CHARACTERS "AEIOU"
#define C_CHARACTERS "BCDFGHJKLMNPQRSTVWXYZ"
#define v_CHARACTERS "aeiou"
#define c_CHARACTERS "bcdfghjklmnpqrstvwxyz"
#define A_CHARACTERS "AEIOUBCDFGHJKLMNPQRSTVWXYZ"
#define a_CHARACTERS "AEIOUaeiouBCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz"
#define n_CHARACTERS "0123456789"
#define o_CHARACTERS "@&%?,=[]_:-+*$#!'^~;()/."
#define x_CHARACTERS "AEIOUaeiouBCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz0123456789!@#$%^&*()"
#define space_CHARACTERS " "
#define MAX_LENGTH_CHARACTERS_CATEGORY_STRING sizeof(x_CHARACTERS)

int number_of_templates(const char* template_class,
                        size_t template_class_size);

int template(const char* template_class,
             size_t template_class_size,
             size_t template_number,
             char* buf,
             size_t buf_size);

int template_characters(char template_char,
                        char* buf,
                        size_t buf_size);
#endif /* TEMPLATES_H */
