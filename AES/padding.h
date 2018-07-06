#ifndef PADDING_H
#define PADDING_H

#include <stdint.h>
#include <stdlib.h>

void pkcs7AddPadding(uint8_t * block, size_t elements);

size_t pkcs7RemovePadding(uint8_t * block);

#endif
