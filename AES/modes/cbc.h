#ifndef CBC_H
#define CBC_H

#include <stdint.h>
#include <string.h>

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

/**
 * Encrypts a file using the cbc mode of encryption
 *
 * @param plaintextStream the file stream to read the plaintext from
 * @param ciphertextStream the file stream to write the ciphertext to
 * @param key the key to encrypt the file
 * @param type the flavour of AES to encrypt the document with
 */
void cbcEncryptFile(FILE * plaintextStream, FILE * ciphertextStream, uint8_t * key, int type);

/**
 * Decrypts a file using the cbc mode of encryption
 *
 * @param plaintextStream the file stream to write the plaintext to
 * @param ciphertextStream the file stream to read the ciphertext from
 * @param key the key to decrypt the file
 * @param type the flavour of AES to decrypt the document with
 */
void cbcDecryptFile(FILE * plaintextStream, FILE * ciphertextStream, uint8_t * key, int type);

#endif
