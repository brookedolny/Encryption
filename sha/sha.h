#ifndef SHA_H
#define SHA_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

extern uint64_t K_256[64];
extern uint64_t K_512[80];

void SHA1init(uint32_t * hash);

/**
 * Computes the SHA1 hash from a message from stdin
 * @param hash the location to store the final SHA1 hash
 */
void SHA1(FILE * input, uint32_t * hash);

void SHA224init(uint32_t * hash);

void SHA224(FILE * input, uint32_t * hash);

void SHA256init(uint32_t * hash);

void SHA256(FILE * input, uint32_t * hash);

#endif
