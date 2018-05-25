#include "aes.h"

uint8_t xtime(uint8_t x) {
    return x >= 128 ? (x << 1) ^ 0x1b : x << 1;
}


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


void addPolynomial(uint8_t * a, const uint8_t * b) {
    for(int i = 0; i < 4; i++) {
        a[i] ^= b[i];
    }
}


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


void rotateWord(uint8_t * word) {
    static uint8_t shift1[4] = {0, 0, 0, 1};
    multiplyPolynomial(word, shift1);
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


void subWord(uint8_t * word) {
    for(int i = 0; i < 4; i++) {
        word[i] = sbox[word[i]];
    }
}


void subBytes(uint8_t ** state) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            state[i][j] = sbox[state[i][j]];
        }
    }
}


void keyExpansion(uint8_t * key, uint8_t ** words, int Nk, int Nb, int Nr) {
    // Nk is key length, Nb is block size, Nr is number of rounds
    uint8_t temp[4];
    for(int i = 0; i < Nk; i++) {
        for(int j = 0; j < 4; j++) {
            words[i][j] = key[4 * i + j];
        }
    }
    for(int i = Nk; i < Nb * (Nr + 1); i++) {
        for(int j = 0; j < 4; j++) {
            temp[j] = words[i][j];
        }
        if(i % Nk == 0) {
            rotateWord(temp);
            subWord(temp);
            temp[0] = rcon[i / Nk] ^ temp[0];
        } else if (Nk > 6 && i % Nk == 4) {
            subWord(temp);
        }
        for(int j = 0; j < 4; j++) {
            words[i][j] = words[i - Nk][j] ^ temp[j];
        }
    }
}
