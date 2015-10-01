#ifndef _common_h_
#define _common_h_

extern int roundKeys[16][48];

void Permute(const int outputNum, int* inBlock, int* outBlock, int* table);
void Split(const int inputNum, const int outputNum, const int* inBlock, int* leftBlock, int* rightBlock);
void Combine(const int inputNum, const int outputNum, const int* left, const int* right, int* outBlock);
void PrintText(const int length, const int* text) ;

#endif