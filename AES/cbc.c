#include <stdlib.h>
#include <time.h>
#include "aes.h"
#include "cbc.h"


void generateInitVector(uint8_t * initVector) {
    srand(time(NULL));
    for(int i = 0; i < 16; i++) {
        initVector[i] = (uint8_t) (rand() % 256);
    }
}

void encryptBlock(uint8_t * previous, uint8_t * text, uint8_t words[][4], int Nk, int Nb, int Nr) {
    for(int i = 0; i < Nb * 4; i++) {
        text[i] ^= previous[i];
    }
    encrypt(text, words, Nk, Nb, Nr);
}

void decryptBlock(uint8_t * previous, uint8_t * text, uint8_t words[][4], int Nk, int Nb, int Nr) {
    decrypt(text, words, Nk, Nb, Nr);
    for(int i = 0; i < Nb * 4; i++) {
        text[i] ^= previous[i];
    }
}
