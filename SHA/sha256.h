#ifndef SHA256_H
#define SHA256_H

#include <stdint.h>
#include <stdlib.h>

uint32_t S_0_256(uint32_t x);

uint32_t S_1_256(uint32_t x);

uint32_t s_0_256(uint32_t x);

uint32_t s_1_256(uint32_t x);

void initalSHA224HashValue(uint32_t * hash);

void initalSHA256HashValue(uint32_t * hash);

void SHA256MessageSchedule(uint32_t * message, uint32_t * words);

void SHA256Iteration(uint32_t * message, uint32_t * hash);

#endif
