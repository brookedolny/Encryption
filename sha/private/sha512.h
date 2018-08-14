#ifndef SHA512_H
#define SHA512_H

#include <stdlib.h>
#include <stdint.h>

extern uint64_t K_512[80];

/**
 * This function is provided by the SHA2 standard. See the NIST FIPS 180-4 publication
 * for more information about this function.
 */
uint64_t S_0_512(uint64_t x);

/**
 * This function is provided by the SHA2 standard. See the NIST FIPS 180-4 publication
 * for more information about this function.
 */
uint64_t S_1_512(uint64_t x);

/**
 * This function is provided by the SHA2 standard. See the NIST FIPS 180-4 publication
 * for more information about this function.
 */
uint64_t s_0_512(uint64_t x);

/**
 * This function is provided by the SHA2 standard. See the NIST FIPS 180-4 publication
 * for more information about this function.
 */
uint64_t s_1_512(uint64_t x);

void SHA512Padding(uint8_t * message, size_t length);

void SHA512Parsing(uint8_t * message, uint64_t * parsed);

#endif
