#include "common.h"
#include <stdio.h>

//roundKeys: 키젠으로 생성된 48bit-key 16개 변수
int roundKeys[16][48] = {0};

//Permute) 치환 함수
//		   outputNum: 치환 후 text length
//		   inBlock  : 치환 시킬 text block
//		   outBlock : 치환 이후 text block
//		   talbe    : 치환에 사용될 치환표
void Permute(const int outputNum, int* inBlock, int* outBlock, int* table) {
	int index=0, i=0, j=0;

	while(index < outputNum)
	{
		outBlock[index] = inBlock[table[index]-1];
		index++;
	}
}

//Split) Block 분할 함수
//		 inputNum  : 입력될 Block의 length
//		 outputNum : 분할 후 각각의 Block length
//		 inBlock   : 분할시킬 Block
//		 leftBlock : 분할 후 좌측 절반 Block
//		 rightBlock: 분할 후 우측 절반 Block
void Split(const int inputNum, const int outputNum, const int* inBlock, int* leftBlock, int* rightBlock) {
	int index=0;//좌측 Block 생성
	while(index < outputNum) {
		leftBlock[index] = inBlock[index];
		index++;
	}

	index=0;//우측 Block 생성
	while(index < outputNum) {
		rightBlock[index] = inBlock[index+outputNum];
		index++;
	}
}

//Combine) Block 결합 함수
//		   inputNum : 입력될 Block length
//		   outputNum: 결합 이후 합체된 Block length
//		   left		: 입력되는 좌측 절반 Block
//		   right	: 입력되는 우측 절반 Block
//		   outBlock	: 결합 이후 합체된 Block
void Combine(const int inputNum, const int outputNum, const int* left, const int* right, int* outBlock) {
	int count=0;

	for(count=0; count<inputNum; count++) outBlock[count]=left[count]; //좌측 Block 결합
	for(count=0; count<inputNum; count++) outBlock[count+inputNum]=right[count]; //우측 Block 결합
}

//PrintText) 2진수를 16진수화 하여 출력하는 함수
//			 length: 출력할 text의 length
//			 text  : 출력할 text
void PrintText(const int length, const int* text) {
	const int fourBit=4, positionNumber[4]={8,4,2,1}; //positionNumber: 2진수 각 자리의 value
	int count=0, hexValue=0;;	//hexValue: 네자리 2진수를 합친 value

	while(count < length) {
		hexValue += text[count]*positionNumber[count%fourBit];
		// 2진 text의 각 자리수 * 각 자리수에 해당하는 10진수 value
		
		if(count%fourBit == 3) { // 2진수 4자리 단위 측정 & 출력
			printf("%X", hexValue);
			hexValue=0;
		}
		count++;
	}
}