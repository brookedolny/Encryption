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

void SHA256MessageSchedule(uint32_t * message, uint32_t * words) {
    for(int i = 0; i < 16; i++) {
        words[i] = message[i];
    }
    for(int i = 16; i < 64; i++) {
        words[i] = s_1_256(words[i - 2]) + words[i - 7] + s_0_256(words[i - 15]) + words[i - 16];
    }
}

void SHA256Iteration(uint32_t * message, uint32_t * hash) {
    uint32_t temp1 = 0;
    uint32_t temp2 = 0;
    uint32_t words[64];
    uint32_t working[8];
    SHA256MessageSchedule(message, words);
    for(int i = 0; i < 8; i++) {
        working[i] = hash[i];
    }
    for(int i = 0; i < 64; i++) {
        temp1 = working[7] + S_1_256(working[4]) + choose(working[4], working[5], working[6]) + K_256[i] + words[i];
        temp2 = S_0_256(working[0]) + majority(working[0], working[1], working[2]);
        for(int j = 7; j > 0; j--) {
            working[j] = working[j - 1];
        }
        working[4] += temp1;
        working[0] = temp1 + temp2;
    }
    for(int i = 0; i < 8; i++) {
        hash[i] += working[i];
    }
}
