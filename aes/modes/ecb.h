#ifndef ECB_H
#define ECB_H

#include <stdint.h>
#include <string.h>

/**
 * Encrypts a file using the ECB mode of operation for the AES_H
 *
 * @param plaintextStream the file stream to read the plaintext from
 * @param ciphertextStream the file stream to write the ciphertext to
 * @param key the key to encrypt the file
 * @param type the flavour of AES to encrypt the document with
 */
void ecbEncryptFile(FILE * plaintextStream, FILE * ciphertextStream, uint8_t * key, int type);


/**
 * Decrypts a file using the ECB mode of operation for the AES
 *
 * @param plaintextStream the file stream to write the plaintext to
 * @param ciphertextStream the file stream to read the ciphertext from
 * @param key the key to decrypt the file
 * @param type the flavour of AES to decrypt the document with
 */
void ecbDecryptFile(FILE * plaintextStream, FILE * ciphertextStream, uint8_t * key, int type);

#endif
