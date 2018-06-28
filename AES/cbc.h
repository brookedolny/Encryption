#include <stdint.h>

/**
 * Generates a random 128-bit initalization vector.
 *
 * @param initVector array of 16 uint8_t's where the init vector will be stored
 */
void generateInitVector(uint8_t * initVector);

/**
 * Encrypts one block with the CBC mode of encryption
 *
 * @param previous the previous ciphertext block
 * @param text the plaintext to be encrypted
 * @param words the expanded key (as per the AES)
 * @param Nk the key length
 * @param Nb the block size
 * @param Nr the number of rounds to perform the AES algorithm
 */
void encryptBlock(uint8_t * previous, uint8_t * text, uint8_t words[][4], int Nk, int Nb, int Nr);

/**
 * Decrypts one block with the CBC mode of decryption
 *
 * @param previous the previous ciphertext block
 * @param text the plaintext to be decrypted
 * @param words the expanded key (as per the AES)
 * @param Nk the key length
 * @param Nb the block size
 * @param Nr the number of rounds to perform the AES algorithm
 */
void decryptBlock(uint8_t * previous, uint8_t * text, uint8_t words[][4], int Nk, int Nb, int Nr);
