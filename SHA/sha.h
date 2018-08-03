#ifndef SHA_H
#define SHA_H

#include <stdint.h>
#include <stdlib.h>

extern uint64_t K_256[64];
extern uint64_t K_512[80];

/**
 * Computes the SHA1 hash from a message from stdin
 * @param hash the location to store the final SHA1 hash
 */
void SHA1(uint32_t * hash);

#endif
