#ifndef _TEST_H_
#define _TEST_H_

#include <stdio.h>
#include <string.h>
#include <gmp.h>
#include "dghv.h"

int initial();
int reset(int level);
int encrypt_one();
int encrypt_zero();
char decrypt();
int generatePKmod();
unsigned long DGHV_decrypt_2(mpz_t ciphertext, __prikey* prikey);

#endif