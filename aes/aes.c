#include "aes.h"

uint8_t xtime(uint8_t x) {
    return x >= 128 ? (x << 1) ^ 0x1b : x << 1;
}


uint8_t multiply(uint8_t x, uint8_t y) {
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


void shiftRows(uint8_t state[4][4]) {
    static uint8_t shift1[4] = {0, 0, 0, 1}; // x^3
    static uint8_t shift2[4] = {0, 0, 1, 0}; // x^2
    static uint8_t shift3[4] = {0, 1, 0, 0}; // x
    multiplyPolynomial(state[1], shift1);
    multiplyPolynomial(state[2], shift2);
    multiplyPolynomial(state[3], shift3);
}

void invShiftRows(uint8_t state[4][4]) {
    static uint8_t shift1[4] = {0, 1, 0, 0}; // x
    static uint8_t shift2[4] = {0, 0, 1, 0}; // x^2
    static uint8_t shift3[4] = {0, 0, 0, 1}; // x^3
    multiplyPolynomial(state[1], shift1);
    multiplyPolynomial(state[2], shift2);
    multiplyPolynomial(state[3], shift3);
}

void mixColumns(uint8_t state[4][4]) {
    uint8_t temp[4];
    for(int i = 0; i < 4; i++) {
        temp[0] = (xtime(state[0][i])) ^ (xtime(state[1][i])) ^ state[1][i] ^ state[2][i] ^ state[3][i];
        temp[1] = state[0][i] ^ (xtime(state[1][i])) ^ (xtime(state[2][i])) ^ state[2][i] ^ state[3][i];
        temp[2] = state[0][i] ^ state[1][i] ^ (xtime(state[2][i])) ^ (xtime(state[3][i])) ^ state[3][i];
        temp[3] = (xtime(state[0][i])) ^ state[0][i] ^ state[1][i] ^ state[2][i] ^ (xtime(state[3][i]));
        state[0][i] = temp[0];
        state[1][i] = temp[1];
        state[2][i] = temp[2];
        state[3][i] = temp[3];
    }
}

void invMixColumns(uint8_t state[4][4]) {
    uint8_t temp[4];
    for(int i = 0; i < 4; i++) {
        temp[0] = multiply(0x0e, state[0][i]) ^ multiply(0x0b, state[1][i]) ^ multiply(0x0d, state[2][i]) ^ multiply(0x09, state[3][i]);
        temp[1] = multiply(0x09, state[0][i]) ^ multiply(0x0e, state[1][i]) ^ multiply(0x0b, state[2][i]) ^ multiply(0x0d, state[3][i]);
        temp[2] = multiply(0x0d, state[0][i]) ^ multiply(0x09, state[1][i]) ^ multiply(0x0e, state[2][i]) ^ multiply(0x0b, state[3][i]);
        temp[3] = multiply(0x0b, state[0][i]) ^ multiply(0x0d, state[1][i]) ^ multiply(0x09, state[2][i]) ^ multiply(0x0e, state[3][i]);
        state[0][i] = temp[0];
        state[1][i] = temp[1];
        state[2][i] = temp[2];
        state[3][i] = temp[3];

    }
}


void subWord(uint8_t * word) {
    for(int i = 0; i < 4; i++) {
        word[i] = sboxAES[word[i]];
    }
}

void invSubWord(uint8_t * word) {
    for(int i = 0; i < 4; i++) {
        word[i] = invSboxAES[word[i]];
    }
}


void subBytes(uint8_t state[4][4]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            state[i][j] = sboxAES[state[i][j]];
        }
    }
}

void invSubBytes(uint8_t state[4][4]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            state[i][j] = invSboxAES[state[i][j]];
        }
    }
}

void keyExpansion(uint8_t * key, uint8_t words[][4], int Nk, int Nb, int Nr) {
    // Nk is key length, Nb is block size, Nr is number of rounds
    uint8_t temp[4];
    for(int i = 0; i < Nk; i++) {
        for(int j = 0; j < 4; j++) {
            words[i][j] = key[4 * i + j];
        }
    }
    for(int i = Nk; i < Nb * (Nr + 1); i++) {
        for(int j = 0; j < 4; j++) {
            temp[j] = words[i - 1][j];
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


void addRoundKey(uint8_t state[4][4], uint8_t words[][4], int Nb, int rnd) {
    for(int i = 0; i < Nb; i++) {
        for(int j = 0; j < 4; j++) {
            state[j][i] ^= words[rnd * Nb + i][j];
        }
    }
}


void encrypt(uint8_t * bytes, uint8_t words[][4], int Nk, int Nb, int Nr) {
    uint8_t state[4][4];
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            state[j][i] = bytes[4 * i + j];
        }
    }
    addRoundKey(state, words, Nb, 0);
    for(int i = 1; i < Nr; i++) {
        subBytes(state);
        shiftRows(state);
        mixColumns(state);
        addRoundKey(state, words, Nb, i);
    }
    subBytes(state);
    shiftRows(state);
    addRoundKey(state, words, Nb, Nr);
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            bytes[4 * i + j] = state[j][i];
        }
    }
}


void decrypt(uint8_t * bytes, uint8_t words[][4], int Nk, int Nb, int Nr) {
    uint8_t state[4][4];
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            state[j][i] = bytes[4 * i + j];
        }
    }
    addRoundKey(state, words, Nb, Nr);
    for(int i = Nr - 1; i > 0; i--) {
        invShiftRows(state);
        invSubBytes(state);
        addRoundKey(state, words, Nb, i);
        invMixColumns(state);
    }
    invShiftRows(state);
    invSubBytes(state);
    addRoundKey(state, words, Nb, 0);
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            bytes[4 * i + j] = state[j][i];
        }
    }
}
