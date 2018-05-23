#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

uint8_t sbox[16][16] = {
      {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5 ,0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76}
    , {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0 ,0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0}
    , {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc ,0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15}
    , {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a ,0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75}
    , {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0 ,0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84}
    , {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b ,0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf}
    , {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85 ,0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8}
    , {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5 ,0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2}
    , {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17 ,0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73}
    , {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88 ,0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb}
    , {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c ,0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79}
    , {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9 ,0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08}
    , {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6 ,0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a}
    , {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e ,0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e}
    , {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94 ,0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf}
    , {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68 ,0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}
};

/**
 * Multiplys a given binary polynomial by the binary polynomial x modulo the
 * binary polynomial m(x) = x^8 + x^4 + x^3 + x + 1.
 */
uint8_t xtime(uint8_t x) {
    return x >= 128 ? (x << 1) ^ 0x1b : x << 1;
}

// TODO do this better at some point
/*
 * Multiplication of two binary polynomials mod m(x), with m(x) being an
 * irreducible binary polynomial of degree 8.
 * The AES uses m(x) = x^8 + x^4 + x^3 + x + 1.
 */
uint8_t multiply(uint8_t x, uint8_t y) {
    if(x == 0 || y == 0) {
        return 0;
    }
    uint8_t product = 0;
    uint8_t basis[8];
    basis[0] = x;
    for(int i = 1; i < 8; i++) {
        basis[i] = xtime(basis[i - 1]);
    }
    for(int i = 0; i < 8; i++) {
        if(y >= 0x80) {
            product ^= basis[7 - i];
        }
        y <<= 1;
    }
    return product;
}

/**
 * Adds a polynomial b(x) to a(x). Both polynomials are of at most degree 4.
 * Note that addition and subtraction are equivalent operations, since each
 * binary polynomial's additive inverse is itself. This follows directly from
 * the defintion of addition in GF(2^8).
 *
 * @param a the first polynomial to be added
 * @param b the second polynomial to be added
 */
void addPolynomial(uint8_t * a, const uint8_t * b) {
    for(int i = 0; i < 4; i++) {
        a[i] ^= b[i];
    }
}

uint8_t * addPolynomial2(const uint8_t * a, const uint8_t * b) {
    uint8_t * d = malloc(4 * sizeof(uint8_t));
    for(int i = 0; i < 4; i++) {
        d[i] = a[i] ^ b[i];
    }
    return d;
}

/**
 * Multiplys two polynomials with coefficents of binary polynomials. This
 * multiplication is done modulo m(x) = x^4 + 1.
 */
void multiplyPolynomial(uint8_t * a, const uint8_t * b) {
     uint8_t d[4];
     d[0] = (multiply(a[0],b[0])) ^ (multiply(a[3],b[1])) ^ (multiply(a[2],b[2])) ^ (multiply(a[1],b[3]));
     d[1] = (multiply(a[1],b[0])) ^ (multiply(a[0],b[1])) ^ (multiply(a[3],b[2])) ^ (multiply(a[2],b[3]));
     d[2] = (multiply(a[2],b[0])) ^ (multiply(a[1],b[1])) ^ (multiply(a[0],b[2])) ^ (multiply(a[3],b[3]));
     d[3] = (multiply(a[3],b[0])) ^ (multiply(a[2],b[1])) ^ (multiply(a[1],b[2])) ^ (multiply(a[0],b[3]));
     for(int i = 0; i < 4; i++) {
         a[i] = d[i];
     }
 }

// TODO delete this
uint8_t * multiplyPolynomial2(const uint8_t * a, const uint8_t * b) {
    uint8_t * d = malloc(4 * sizeof(uint8_t));
    d[0] = (multiply(a[0],b[0])) ^ (multiply(a[3],b[1])) ^ (multiply(a[2],b[2])) ^ (multiply(a[1],b[3]));
    d[1] = (multiply(a[1],b[0])) ^ (multiply(a[0],b[1])) ^ (multiply(a[3],b[2])) ^ (multiply(a[2],b[3]));
    d[2] = (multiply(a[2],b[0])) ^ (multiply(a[1],b[1])) ^ (multiply(a[0],b[2])) ^ (multiply(a[3],b[3]));
    d[3] = (multiply(a[3],b[0])) ^ (multiply(a[2],b[1])) ^ (multiply(a[1],b[2])) ^ (multiply(a[0],b[3]));
    return d;
}

void shiftRows(uint8_t ** state) {
    static uint8_t shift1[4] = {0, 0, 0, 1}; // x^3
    static uint8_t shift2[4] = {0, 0, 1, 0}; // x^2
    static uint8_t shift3[4] = {0, 1, 0, 0}; // x
    multiplyPolynomial(state[1], shift1);
    multiplyPolynomial(state[2], shift2);
    multiplyPolynomial(state[3], shift3);
}

void mixColumns(uint8_t ** state) {
    uint8_t temp[4];
    for(int i = 0; i < 4; i++) {
        temp[0] = (xtime(state[0][i])) ^ (xtime(state[1][i])) ^ state[1][i] ^ state[2][i] ^ state[3][i];
        temp[1] = state[0][i] ^ (xtime(state[1][i])) ^ (xtime(state[2][i])) ^ state[2][i] ^ state[3][i];
        temp[2] = state[0][i] ^ state[1][i] ^ (xtime(state[2][i])) ^ (xtime(state[3][i])) ^ state[3][i];
        temp[0] = (xtime(state[0][i])) ^ state[0][i] ^ state[1][i] ^ state[2][i] ^ (xtime(state[3][i]));
        state[0][i] = temp[0];
        state[1][i] = temp[1];
        state[2][i] = temp[2];
        state[3][i] = temp[3];
    }
}




int main(void) {
//    uint8_t
// currently, polynomials are represented as {a,b,c,d} = ax^0 + bx^1 + cx^2 + dx^3.
// this may mess up implementation of this algorithm.
// TODO check the above condition

}
