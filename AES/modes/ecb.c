#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "../aes.h"
#include "ecb.h"
#include "padding.h"

void ecbCleanMemory(uint8_t * text, uint8_t * key, uint8_t words[][4], int Nk, int Nb, int Nr) {
    for(int i = 0; i < Nb * 4; i++) {
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

void ecbEncryptFile(FILE * plaintextStream, FILE * ciphertextStream, uint8_t * key, int type) {
    assert(type == 128 || type == 192 || type == 256);
    int Nk = type / 32;
    int Nb = 4;
    int Nr = type == 128 ? 10 : (type == 192 ? 12 : 14);

    uint8_t text[16];
    uint8_t words[Nb*(Nr+1)][4];
    keyExpansion(key, words, Nk, Nb, Nr);

    size_t elements = fread(text, 1, 16, plaintextStream);
    while(elements == 16) {
        encrypt(text, words, Nk, Nb, Nr);
        fwrite(text, 1, 16, ciphertextStream);
        elements = fread(text, 1, 16, plaintextStream);
    }

    if(feof(plaintextStream)) {
        pkcs7AddPadding(text, elements);
        encrypt(text, words, Nk, Nb, Nr);
        fwrite(text, 1, 16, ciphertextStream);
    }

    ecbCleanMemory(text, key, words, Nk, Nb, Nr);
}


void ecbDecryptFile(FILE * plaintextStream, FILE * ciphertextStream, uint8_t * key, int type) {
    assert(type == 128 || type == 192 || type == 256);
    int Nk = type / 32;
    int Nb = 4;
    int Nr = type == 128 ? 10 : (type == 192 ? 12 : 14);

    uint8_t text[16];
    uint8_t words[Nb*(Nr+1)][4];

    keyExpansion(key, words, Nk, Nb, Nr);

    size_t elements = fread(text, 1, 16, ciphertextStream); // initial file data
    if(elements < 16 && elements != 0) {
        assert(0 && "wrong final block size");
        return;
    }
    decrypt(text, words, Nk, Nb, Nr);
    while(elements == 16) {
        fwrite(text, 1, 16, plaintextStream);
        elements = fread(text, 1, 16, ciphertextStream); // actual file data
        decrypt(text, words, Nk, Nb, Nr);
    }

    if(elements != 0) {
        assert(0 && "wrong final block size");
    }
    if(feof(ciphertextStream)) {
        decrypt(text, words, Nk, Nb, Nr);
        elements = pkcs7RemovePadding(text);
        fwrite(text, 1, elements, ciphertextStream);
    }

    ecbCleanMemory(text, key, words, Nk, Nb, Nr);
}
