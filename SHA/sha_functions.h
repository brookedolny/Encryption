#ifndef SHA_FUNCTIONS_H
#define SHA_FUNCTIONS_H

#include <stdint.h>

uint32_t rotateLeft32(uint32_t x, int n);

uint64_t rotateLeft64(uint64_t x, int n);

uint32_t rotateRight32(uint32_t x, int n);

uint64_t rotateRight64(uint64_t x, int n);

uint32_t choose32(uint32_t x, uint32_t y, uint32_t z);

uint64_t choose64(uint64_t x, uint64_t y, uint64_t z);

uint32_t parity32(uint32_t x, uint32_t y, uint32_t z);

uint64_t parity64(uint64_t x, uint64_t y, uint64_t z);

uint32_t majority32(uint32_t x, uint32_t y, uint32_t z);

uint64_t majority64(uint64_t x, uint64_t y, uint64_t z);



#endif
