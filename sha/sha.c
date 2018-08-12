#include "sha.h"
#include "sha1.h"
#include "sha256.h"
#include <stdio.h>

void SHA1init(uint32_t * hash) {
    initalSHA1HashValue(hash);
}

void SHA1(uint32_t * hash) {
    uint8_t message[64] = {0};
    uint32_t parsed[16] = {0};
    size_t elements;
    size_t length = 0;
    elements = fread(message, 1, 64, stdin);
    length += elements;
    while(elements == 64) {
        SHA1Parsing(message, parsed);
        SHA1Iteration(parsed, hash);
        elements = fread(message, 1, 64, stdin);
        length += elements;
    }
    if (feof(stdin)) {
        SHA1Padding(message, length * 8);
        SHA1Parsing(message, parsed);
        SHA1Iteration(parsed, hash);
    } else if (ferror(stdin)) {
        perror("Failed to compute SHA1 hash");
    }
}

void SHA224init(uint32_t * hash) {
    initalSHA224HashValue(hash);
}

void SHA224(uint32_t * hash) {
    SHA256(hash);
    hash[8] = 0;
}

void SHA256init(uint32_t * hash) {
    initalSHA256HashValue(hash);
}

void SHA256(uint32_t * hash) {
    uint8_t message[64] = {0};
    uint32_t parsed[16] = {0};
    size_t elements;
    size_t length = 0;
    elements = fread(message, 1, 64, stdin);
    length += elements;
    while(elements == 64) {
        SHA1Parsing(message, parsed);
        SHA256Iteration(parsed, hash);
        elements = fread(message, 1, 64, stdin);
        length += elements;
    }
    if (feof(stdin)) {
        SHA1Padding(message, length * 8);
        SHA1Parsing(message, parsed);
        SHA256Iteration(parsed, hash);
    } else if (ferror(stdin)) {
        perror("Failed to compute SHA1 hash");
    }
}
