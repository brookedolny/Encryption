#include "sha.h"
#include <stdio.h>

void SHA1(uint32_t * hash) {
    uint8_t message[64] = {0};
    uint32_t parsed[16] = {0};
    size_t elements;
    size_t length;
    size_t bits = 0;
    elements = fread(message, 1, 64, stdin);
    length += elements;
    initalSHA1HashValue(hash);
    while(elements == 64) {
        SHA1Parsing(message, parsed);
        SHA1Iteration(parsed, hash);
        elements = fread(message, 1, 64, stdin);
        length += elements;
    }
    SHA1Padding(message, length * 8);
    SHA1Parsing(message, parsed);
    SHA1Iteration(parsed, hash);
}
