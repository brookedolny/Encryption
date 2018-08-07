#include "sha1.h"
#include "sha_functions.h"
#include <string.h>

void SHA1Padding(uint8_t * message, size_t length) {
    int k = (448 - length - 1) % 512;
    uint8_t padding = 0x80;
    int index = (length / 8) % 64;
    message[index] = 0x80;
    memset(message + index + 1, 0, 64 - index - 1);
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

void initalSHA1HashValue(uint32_t * hash) {
    hash[0] = 0x67452301;
    hash[1] = 0xefcdab89;
    hash[2] = 0x98badcfe;
    hash[3] = 0x10325476;
    hash[4] = 0xc3d2e1f0;
}

void SHA1MessageSchedule(uint32_t * message, uint32_t * words) {
    for(int i = 0; i < 16; i++) {
        words[i] = message[i];
    }
    for(int i = 16; i < 80; i++) {
        words[i] = rotateLeft(words[i - 3] ^ words[i - 8] ^ words[i - 14] ^ words[i - 16], 1, 32);
    }
}

void SHA1Iteration(uint32_t * message, uint32_t * hash) {
    uint32_t words[80];
    uint32_t working[5];
    uint32_t temp;
    for(int i = 0; i < 5; i++) {
        working[i] = hash[i];
    }
    SHA1MessageSchedule(message, words);
    for(int i = 0; i < 80; i++) {
        temp = rotateLeft(working[0], 5, 32) + working[4] + K_1[i] + words[i];
        switch(i / 20) {
            case 0:
                temp += choose(working[1], working[2], working[3]);
                break;
            case 2:
                temp += majority(working[1], working[2], working[3]);
                break;
            default:
                temp += parity(working[1], working[2], working[3]);
                break;
        }
        working[4] = working[3];
        working[3] = working[2];
        working[2] = rotateLeft(working[1], 30, 32);
        working[1] = working[0];
        working[0] = temp;
    }
    for(int i = 0; i < 5; i++) {
        hash[i] += working[i];
    }
}
