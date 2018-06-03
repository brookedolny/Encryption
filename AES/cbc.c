#include <stdio.h>
#include "aes.h"

// TODO probably make this random at some point
uint8_t tempInitVector[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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

int main() {}
