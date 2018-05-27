#ifndef AES_H
#define AES_H

#include <stdint.h>

extern uint8_t sbox[256];
extern uint8_t rcon[256];

/**
 * Multiplys a given binary polynomial by the binary polynomial x modulo the
 * binary polynomial m(x) = x^8 + x^4 + x^3 + x + 1.
 *
 * @param x the binary polynomial to be multiplied by x.
 */
uint8_t xtime(uint8_t x);

/**
 * Multiplication of two binary polynomials mod m(x), with m(x) being an
 * irreducible binary polynomial of degree 8.
 * The AES uses m(x) = x^8 + x^4 + x^3 + x + 1.
 *
 * @param x the first binary polynomial in the product
 * @param y the second binary polynomial in the product
 */
uint8_t multiply(uint8_t x, uint8_t y);

/**
 * Adds a polynomial b(x) to a(x). Both polynomials are of at most degree 4.
 * Note that addition and subtraction are equivalent operations, since each
 * binary polynomial's additive inverse is itself. This follows directly from
 * the defintion of addition in GF(2^8).
 *
 * @param a the first polynomial to be added
 * @param b the second polynomial to be added
 */
void addPolynomial(uint8_t * a, const uint8_t * b);

/**
 * Multiplys two polynomials with coefficents of binary polynomials. This
 * multiplication is done modulo m(x) = x^4 + 1.
 *
 * @param a the first polynomial in the product. The final product will be
 *        stored here.
 * @param b the second polynomial in the product.
 */
void multiplyPolynomial(uint8_t * a, const uint8_t * b);

/**
 * Performs the transformation [b0, b1, b2, b3] -> [b1, b2, b3, b0] for a given
 * polynomial with binary polynomial coefficients (elements in GF(2^8)).
 *
 * @param word the word to be rotated
 */
void rotateWord(uint8_t * word);

/**
 * Performs the "ShiftRows(state)" operation as defined by the Advanced Encryption
 * Standard.
 *
 * @param state the current state
 */
void shiftRows(uint8_t state[4][4]);

/**
 * Performs the "MixColumns(state)" operation as defined by the Advanced Encryption
 * Standard.
 *
 * @param state the current state
 */
void mixColumns(uint8_t state[4][4]);

/**
 * Uses the Rijndael SBox as defined in aes_tables.c to substitute values
 * in a word with the correspoinding values in the sbox array.
 *
 * @param word the word that will have it's bytes substituted
 */
void subWord(uint8_t * word);

/**
 * Uses the Rijndael SBox as defined in aes_tables.c to substitute values
 * in the current state with the correspoinding values in the sbox array.
 *
 * @param state the current state
 */
void subBytes(uint8_t state[4][4]);

/**
 * Expands the given ciper key into Nb * (Nr + 1) words, where each word is
 * 4 bytes, represented as a polynomial with coefficients in GF(2^8).
 *
 * @param key the cipher key to be expanded
 * @param words the array where the expanded key will be stored. Should have
 *        dimensions of [Nb*(Nr+1)][4].
 * @param Nk the key length (as stated in the standard)
 * @param Nb the block size (as stated in the standard)
 * @param Nr the number of rounds to be performed (as stated in the standard)
 */
void keyExpansion(uint8_t * key, uint8_t words[][4], int Nk, int Nb, int Nr);

void addRoundKey(uint8_t state[4][4], uint8_t words[][4], int Nb, int rnd);

void encrypt(uint8_t * bytes, uint8_t * key, int Nk, int Nb, int Nr);

#endif
