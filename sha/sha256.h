#ifndef SHA256_H
#define SHA256_H

#include <stdint.h>
#include <stdlib.h>

/**
 * This function is provided by the SHA2 standard. See the NIST FIPS 180-4 publication
 * for more information about this function.
 */
uint32_t S_0_256(uint32_t x);

/**
 * This function is provided by the SHA2 standard. See the NIST FIPS 180-4 publication
 * for more information about this function.
 */
uint32_t S_1_256(uint32_t x);

/**
 * This function is provided by the SHA2 standard. See the NIST FIPS 180-4 publication
 * for more information about this function.
 */
uint32_t s_0_256(uint32_t x);

/**
 * This function is provided by the SHA2 standard. See the NIST FIPS 180-4 publication
 * for more information about this function.
 */
uint32_t s_1_256(uint32_t x);

/**
 * Sets the given hash to the inital SHA224 hash values
 * @param hash the array of 8 elements to be initalized
 */
void initalSHA224HashValue(uint32_t * hash);

/**
 * Sets the given hash to the inital SHA256 hash values
 * @param hash the array of 8 elements to be initalized
 */
void initalSHA256HashValue(uint32_t * hash);

/**
 * Initalizes the SHA224 and SHA256 message schedule.
 * @param message the message to be hashed, consisting of 16 32-bit words
 * @param words the expanded message schedule, consisting of 64 32-bit words
 */
void SHA256MessageSchedule(uint32_t * message, uint32_t * words);

/**
 * Performs one iteration of the SHA224 and SHA256 algorithm, given the previous hash and
 * the message.
 * @param message the message to be hashed in this iteration of the SHA224 or SHA256 algorithm
 * @param hash the previous iteration's hash values, also where the resulting hash will be stored
 */
void SHA256Iteration(uint32_t * message, uint32_t * hash);

#endif
