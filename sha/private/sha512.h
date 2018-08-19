#ifndef SHA512_H
#define SHA512_H

#include <stdlib.h>
#include <stdint.h>

/**
 * The array of constants described in NIST FIPS 180-4
 */
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

/**
 * Pads the message based on the SHA512 message padding scheme described in NIST FIPS 180-4.
 * This should only be used on the last message in the message schedule.
 * @param message the message to be padded
 * @param length the length of the message (in bits)
 */
void SHA512Padding(uint8_t * message, size_t length);

/**
 * Converts the message in 8-bit blocks into a message in 64-bit blocks, using
 * the big endian byte ordering
 * @param message the message to be parsed
 * @param parsed the array to store the parsed message
 */
void SHA512Parsing(uint8_t * message, uint64_t * parsed);

/**
 * Sets the inital SHA384 hash value
 * @param hash the array to be initalized
 */
void initalSHA384HashValue(uint64_t * hash);

/**
 * Sets the inital SHA512 hash value
 * @param hash the array to be initalized
 */
void initalSHA512HashValue(uint64_t * hash);

/**
 * Initalizes the SHA512 message schedule
 * @param message the message to be hashed
 * @param words the array that will be initalized with the SHA512 message schedule
 */
void SHA512MessageSchedule(uint64_t * message, uint64_t * words);

/**
 * Performs one iteration of SHA512
 * @param message the message to be hashed in this iteration
 * @param hash the previous iteration's hash
 */
void SHA512Iteration(uint64_t * message, uint64_t * hash);

#endif
