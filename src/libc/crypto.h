#ifndef CRYPTO_H
#define CRYPTO_H

#define RAND_MAX 1024

#include "../libc/stdint.h"

int lcg(int seed);
int randint(int seed);
uint32_t rand();
float rand_float();
void srand(uint32_t seed);

#endif
