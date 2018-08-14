#include "sha.h"
#include "private/sha1.h"
#include "private/sha256.h"

void SHA1init(uint32_t * hash) {
    initalSHA1HashValue(hash);
}

void SHA1(FILE * input, uint32_t * hash) {
    uint8_t message[64] = {0};
    uint32_t parsed[16] = {0};
    size_t elements;
    size_t length = 0;
    elements = fread(message, 1, 64, input);
    length += elements;
    while(elements == 64) {
        SHA1Parsing(message, parsed);
        SHA1Iteration(parsed, hash);
        elements = fread(message, 1, 64, input);
        length += elements;
    }
    if (feof(input)) {
        SHA1Padding(message, length * 8);
        SHA1Parsing(message, parsed);
        SHA1Iteration(parsed, hash);
    } else if (ferror(input)) {
        perror("Failed to compute SHA1 hash");
    }
}

void SHA224init(uint32_t * hash) {
    initalSHA224HashValue(hash);
}

void SHA224(FILE * input, uint32_t * hash) {
    SHA256(input, hash);
    hash[7] = 0;
}

void SHA256init(uint32_t * hash) {
    initalSHA256HashValue(hash);
}

void SHA256(FILE * input, uint32_t * hash) {
    uint8_t message[64] = {0};
    uint32_t parsed[16] = {0};
    size_t elements;
    size_t length = 0;
    elements = fread(message, 1, 64, input);
    length += elements;
    while(elements == 64) {
        SHA1Parsing(message, parsed);
        SHA256Iteration(parsed, hash);
        elements = fread(message, 1, 64, input);
        length += elements;
    }
    if (feof(input)) {
        SHA1Padding(message, length * 8);
        SHA1Parsing(message, parsed);
        SHA256Iteration(parsed, hash);
    } else if (ferror(input)) {
        perror("Failed to compute SHA1 hash");
    }
}
