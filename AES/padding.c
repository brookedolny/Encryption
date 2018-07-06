#include "padding.h"

void pkcs7AddPadding(uint8_t * block, size_t elements) {
    uint8_t n = 16 - elements;
    for(int i = 0; i < 16; i++) {
        if(i >= elements) {
            block[i] = n;
        }
    }
}

size_t pkcs7RemovePadding(uint8_t * block) {
    return 16 - block[15];
}
