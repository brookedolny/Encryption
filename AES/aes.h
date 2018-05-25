#ifndef AES_H
#define AES_H

#include <stdint.h>

extern uint8_t sbox[256];
extern uint8_t rcon[256];

/**
 * Multiplys a given binary polynomial by the binary polynomial x modulo the
 * binary polynomial m(x) = x^8 + x^4 + x^3 + x + 1.
 */
uint8_t xtime(uint8_t x);

/**
 * Multiplication of two binary polynomials mod m(x), with m(x) being an
 * irreducible binary polynomial of degree 8.
 * The AES uses m(x) = x^8 + x^4 + x^3 + x + 1.
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
 */
void multiplyPolynomial(uint8_t * a, const uint8_t * b);

/**
 * Performs the transformation [b0, b1, b2, b3] -> [b1, b2, b3, b0] for a given
 * polynomial with binary polynomial coefficients (elements in GF(2^8)).
 */
void rotateWord(uint8_t * word);

/**
 * Performs the "ShiftRows(state)" operation as defined by the Advanced Encryption
 * Standard.
 */
void shiftRows(uint8_t ** state);


void mixColumns(uint8_t ** state);


void subWord(uint8_t * word);


 void subBytes(uint8_t ** state);


 void keyExpansion(uint8_t * key, uint8_t ** words, int Nk, int Nb, int Nr);

#endif
