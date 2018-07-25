#include "sha.h"
#include <string.h>

void SHA1Padding(uint8_t * message, size_t length) {
    int k = (448 - length - 1) % 512;
    uint8_t padding = 0x80;
    int index = length / 8;
    message[index] = 0x80;
    memset(message + index + 1, 0, 56);
    for(int i = 0; i < 8; i++) {
        padding = (uint8_t) length % 256;
        message[64 - 1 - i] = padding;
        length >>= 8;
    }
}

void SHA1Parsing(uint8_t * message, uint32_t * parsed) {
    for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 4; j++) {
            parsed[i] <<= 8;
            parsed[i] += message[4 * i + j];
        }
    }
}
