#ifndef SHA_H
#define SHA_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Initalizes the hash for SHA1
 * @param hash the hash to be initalized
 */
void SHA1init(uint32_t * hash);

/**
 * Computes the SHA1 hash from a message from stdin
 * @param input the input filestream
 * @param hash the location to store the final SHA1 hash
 */
void SHA1(FILE * input, uint32_t * hash);

/**
 * Initalizes the hash for SHA224
 * @param hash the hash to be initalized
 */
void SHA224init(uint32_t * hash);

/**
 * Computes the SHA224 hash from a message from stdin
 * @param input the input filestream
 * @param hash the location to store the final SHA224 hash
 */
void SHA224(FILE * input, uint32_t * hash);

/**
 * Initalizes the hash for SHA256
 * @param hash the hash to be initalized
 */
void SHA256init(uint32_t * hash);

/**
 * Computes the SHA256 hash from a message from stdin
 * @param input the input filestream
 * @param hash the location to store the final SHA256 hash
 */
void SHA256(FILE * input, uint32_t * hash);

/**
 * Initalizes the hash for SHA384
 * @param hash the hash to be initalized
 */
void SHA384init(uint64_t * hash);

/**
 * Computes the SHA384 hash from a message from stdin
 * @param input the input filestream
 * @param hash the location to store the final SHA384 hash
 */
void SHA384(FILE * input, uint64_t * hash);

/**
 * Initalizes the hash for SHA512
 * @param hash the hash to be initalized
 */
void SHA512init(uint64_t * hash);

/**
 * Computes the SHA512 hash from a message from stdin
 * @param input the input filestream
 * @param hash the location to store the final SHA512 hash
 */
void SHA512(FILE * input, uint64_t * hash);


#endif
