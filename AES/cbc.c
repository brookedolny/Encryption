#include <stdlib.h>
#include <time.h>
#include "aes.h"

uint8_t tempInitVector[16];


void generateInitVector(void) {
    // NOTE: this implementation of CBC is technically invalid.
    // the random number generation for the initalization vector is not
    // uniformly distributed, and uses an LCG which can be implemented
    // in a way that generates predictable random numbers. Also,
    // using the time as a the seed can cause obvious problems.
    srand(time(NULL));
    for(int i = 0; i < 16; i++) {
        tempInitVector[i] = (uint8_t) (rand() % 256);
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
