#ifndef _cipher_h_
#define _cipher_h_
#include <stdlib.h>
#include <string.h>
#include "common.h"

extern int cipherText[64];
extern int plainText[64];

void Cipher();
void Mixer(int leftBlock[32], int rightBlock[32], const int roundKey[48]);
void Swapper(int leftBlock[32], int rightBlock[32]);
void Function(int* inBlock, const int* roundKey);
void ExclusiveOr(const int length, int* inputBlock, const int* operand);
void Substitute(int* inBlock, int* outBlock);

#endif