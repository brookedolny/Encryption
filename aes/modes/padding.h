#ifndef PADDING_H
#define PADDING_H

#include <stdint.h>
#include <stdlib.h>

/**
 * Adds the appropriate padding to the block based on the
 * pkcs7 padding technique.
 *
 * @param block the block to have padding added to it
 * @param elements the number of elements that were read
 *                 in the last file read.
 */
void pkcs7AddPadding(uint8_t * block, size_t elements);

/**
 * Calculates the original, unpadded length of the block.
 *
 * @param block the block to have padding removed from it
 * @return the length of the original, unpadded block
 */
size_t pkcs7RemovePadding(uint8_t * block);

#endif
