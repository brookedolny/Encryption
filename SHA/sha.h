#ifndef SHA_H
#define SHA_H

#include <stdint.h>
#include <stdlib.h>

extern uint32_t K_1[80];
extern uint64_t K_256[64];
extern uint64_t K_512[80];


/**
 * Adds SHA1 padding to the last block of the message.
 * @param message the last block of the message to be hashed. The array should have
 *    a length of 64. Note that this should be the last message block.
 * @param length the length of the whole message (in bits).
 */
void SHA1Padding(uint8_t * message, size_t length);

/**
 * Parses the SHA1 message from 1-byte blocks to 4-byte words
 * @param message the message consisting of 64 1-byte blocks
 * @param parsed the parsed message location, consisting of 16 4-byte blocks
 */
void SHA1Parsing(uint8_t * message, uint32_t * parsed);

/**
 * Sets the inital hash value
 * @param hash the array to be initalized
 */
void initalSHA1HashValue(uint32_t * hash);

/**
 * Initializes the message schedule for the SHA1 algorithm
 * @param message the message to be hashed. Should have a length of 16 4-byte words.
 * @param words the array to have the message schedule initalized to. Should have a length
 *    of 80 4-byte words.
 */
void messageSchedule(uint32_t * message, uint32_t * words);

/**
 * Performs one iteration of the SHA algorithm for the given message block
 * @param message the message block corresponding to the iteration to be performed
 * @param hash the inital hash values, and where the final hash value for the
 *    iteration will be stored.
 */
void SHA1Iteration(uint32_t * message, uint32_t * hash);


#endif
