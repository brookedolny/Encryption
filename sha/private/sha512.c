#include "sha512.h"
#include "sha_functions.h"
#include <string.h>

uint64_t S_0_512(uint64_t x) {
    return rotateRight(x, 28, 64) ^ rotateRight(x, 34, 64) ^ rotateRight(x, 39, 64);
}

uint64_t S_1_512(uint64_t x) {
    return rotateRight(x, 14, 64) ^ rotateRight(x, 18, 64) ^ rotateRight(x, 41, 64);
}

uint64_t s_0_512(uint64_t x) {
    return rotateRight(x, 1, 64) ^ rotateRight(x, 8, 64) ^ (x >> 7);
}

uint64_t s_1_512(uint64_t x) {
    return rotateRight(x, 19, 64) ^ rotateRight(x, 61, 64) ^ (x >> 6);
}

void SHA512Padding(uint8_t * message, size_t length) {
    int k = (896 - length - 1) % 1024;
    uint8_t padding = 0x80;
    int index = (length / 8) % 128;
    message[index] = 0x80;
    memset(message + index + 1, 0, 128 - index - 1);
    for(int i = 0; i < 16; i++) {
        padding = (uint8_t) length % 256;
        message[128 - 1 - i] = padding;
        length >>= 8;
    }
}

void SHA512Parsing(uint8_t * message, uint64_t * parsed) {
    for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 8; j++) {
            parsed[i] <<= 8;
            parsed[i] += message[8 * i + j];
        }
    }
}

void initalSHA384HashValue(uint64_t * hash) {
    hash[0] = 0xcbbb9d5dc1059ed8;
    hash[1] = 0x629a292a367cd507;
    hash[2] = 0x9159015a3070dd17;
    hash[3] = 0x152fecd8f70e5939;
    hash[4] = 0x67332667ffc00b31;
    hash[5] = 0x8eb44a8768581511;
    hash[6] = 0xdb0c2e0d64f98fa7;
    hash[7] = 0x47b5481dbefa4fa4;
}

void initalSHA512HashValue(uint64_t * hash) {
    hash[0] = 0x6a09e667f3bcc908;
    hash[1] = 0xbb67ae8584caa73b;
    hash[2] = 0x3c6ef372fe94f82b;
    hash[3] = 0xa54ff53a5f1d36f1;
    hash[4] = 0x510e527fade682d1;
    hash[5] = 0x9b05688c2b3e6c1f;
    hash[6] = 0x1f83d9abfb41bd6b;
    hash[7] = 0x5be0cd19137e2179;
}
