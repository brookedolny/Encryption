#include "sha256.h"
#include "sha_functions.h"

extern uint32_t K_256[64];

uint32_t S_0_256(uint32_t x) {
    return rotateRight(x, 2, 32) ^ rotateRight(x, 13, 32) ^ rotateRight(x, 22, 32);
}

uint32_t S_1_256(uint32_t x) {
    return rotateRight(x, 6, 32) ^ rotateRight(x, 11, 32) ^ rotateRight(x, 25, 32);
}

uint32_t s_0_256(uint32_t x) {
    return rotateRight(x, 7, 32) ^ rotateRight(x, 18, 32) ^ (x >> 3);
}

uint32_t s_1_256(uint32_t x) {
    return rotateRight(x, 17, 32) ^ rotateRight(x, 19, 32) ^ (x >> 10);
}

void initalSHA224HashValue(uint32_t * hash) {
    hash[0] = 0xc1059ed8;
    hash[1] = 0x367cd507;
    hash[2] = 0x3070dd17;
    hash[3] = 0xf70e5939;
    hash[4] = 0xffc00b31;
    hash[5] = 0x68581511;
    hash[6] = 0x64f98fa7;
    hash[7] = 0xbefa4fa4;
}

void initalSHA256HashValue(uint32_t * hash) {
    hash[0] = 0x6a09e667;
    hash[1] = 0xbb67ae85;
    hash[2] = 0x3c6ef372;
    hash[3] = 0xa54ff53a;
    hash[4] = 0x510e527f;
    hash[5] = 0x9b05688c;
    hash[6] = 0x1f83d9ab;
    hash[7] = 0x5be0cd19;
}
