#ifndef ECB_H
#define ECB_H

#include <stdint.h>
#include <string.h>

void ecbEncryptFile(FILE * plaintextStream, FILE * ciphertextStream, uint8_t * key, int type);

void ecbDecryptFile(FILE * plaintextStream, FILE * ciphertextStream, uint8_t * key, int type);

#endif
