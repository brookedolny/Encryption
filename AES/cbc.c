#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "aes.h"
#include "cbc.h"

void generateRandomBytes(uint8_t * initVector) {
    srand(time(NULL));
    for(int i = 0; i < 16; i++) {
        initVector[i] = (uint8_t) (rand() % 256);
    }
}

void cbcEncryptBlock(uint8_t * previous, uint8_t * text, uint8_t words[][4], int Nk, int Nb, int Nr) {
    for(int i = 0; i < Nb * 4; i++) {
        text[i] ^= previous[i];
    }
    encrypt(text, words, Nk, Nb, Nr);
}

void cbcDecryptBlock(uint8_t * previous, uint8_t * text, uint8_t words[][4], int Nk, int Nb, int Nr) {
    decrypt(text, words, Nk, Nb, Nr);
    for(int i = 0; i < Nb * 4; i++) {
        text[i] ^= previous[i];
    }
}

void pkcs7AddPadding(uint8_t * block, size_t elements) {
    uint8_t n = 16 - elements;
    for(int i = 0; i < 16; i++) {
        if(i >= elements) {
            block[i] = n;
        }
    }
}



void cleanMemory(uint8_t * previous, uint8_t * text, uint8_t * key, uint8_t words[][4], int Nk, int Nb, int Nr) {
    for(int i = 0; i < Nb * 4; i++) {
        previous[i] = 0;
        text[i] = 0;
    }
    for(int i = 0; i < Nk; i++) {
        key[i] = 0;
        for(int j = 0; j < 4; j++) {
            words[i][j] = 0;
        }
    }
    for(int i = Nk; i < Nb * (Nr + 1); i++) {
        for(int j = 0; j < 4; j++) {
            words[i][j] = 0;
        }
    }
}

void cbcEncryptFile(FILE * plaintextStream, FILE * ciphertextStream, uint8_t * key, int type) {
    assert(type == 128 || type == 192 || type == 256);
    int Nk = type / 32;
    int Nb = 4;
    int Nr = type == 128 ? 10 : (type == 192 ? 12 : 14);

    uint8_t previous[16];
    uint8_t text[16];
    uint8_t words[Nb*(Nr+1)][4];

    generateRandomBytes(previous); // randomized init vector
    generateRandomBytes(text); // randomized inital block
    keyExpansion(key, words, Nk, Nb, Nr);

    cbcEncryptBlock(previous, text, words, Nk, Nb, Nr);
    for(int i = 0; i < 16; i++) {
        previous[i] = text[i];
    }
    fwrite(text, 1, 16, ciphertextStream);

    size_t elements = fread(text, 1, 16, plaintextStream);
    while(elements == 16) {
        cbcEncryptBlock(previous, text, words, Nk, Nb, Nr);
        fwrite(text, 1, 16, ciphertextStream);
        for(int i = 0; i < 16; i++) {
            previous[i] = text[i];
        }
        elements = fread(text, 1, 16, plaintextStream);
    }

    if(feof(plaintextStream)) {
        pkcs7AddPadding(text, elements);
        cbcEncryptBlock(previous, text, words, Nk, Nb, Nr);
        fwrite(text, 1, 16, ciphertextStream);
    }

    cleanMemory(previous, text, key, words, Nk, Nb, Nr);
}
