#include "common.h"
#include <stdio.h>

//roundKeys: Ű������ ������ 48bit-key 16�� ����
int roundKeys[16][48] = {0};

//Permute) ġȯ �Լ�
//		   outputNum: ġȯ �� text length
//		   inBlock  : ġȯ ��ų text block
//		   outBlock : ġȯ ���� text block
//		   talbe    : ġȯ�� ���� ġȯǥ
void Permute(const int outputNum, int* inBlock, int* outBlock, int* table) {
	int index=0, i=0, j=0;

	while(index < outputNum)
	{
		outBlock[index] = inBlock[table[index]-1];
		index++;
	}
}

//Split) Block ���� �Լ�
//		 inputNum  : �Էµ� Block�� length
//		 outputNum : ���� �� ������ Block length
//		 inBlock   : ���ҽ�ų Block
//		 leftBlock : ���� �� ���� ���� Block
//		 rightBlock: ���� �� ���� ���� Block
void Split(const int inputNum, const int outputNum, const int* inBlock, int* leftBlock, int* rightBlock) {
	int index=0;//���� Block ����
	while(index < outputNum) {
		leftBlock[index] = inBlock[index];
		index++;
	}

	index=0;//���� Block ����
	while(index < outputNum) {
		rightBlock[index] = inBlock[index+outputNum];
		index++;
	}
}

//Combine) Block ���� �Լ�
//		   inputNum : �Էµ� Block length
//		   outputNum: ���� ���� ��ü�� Block length
//		   left		: �ԷµǴ� ���� ���� Block
//		   right	: �ԷµǴ� ���� ���� Block
//		   outBlock	: ���� ���� ��ü�� Block
void Combine(const int inputNum, const int outputNum, const int* left, const int* right, int* outBlock) {
	int count=0;

	for(count=0; count<inputNum; count++) outBlock[count]=left[count]; //���� Block ����
	for(count=0; count<inputNum; count++) outBlock[count+inputNum]=right[count]; //���� Block ����
}

//PrintText) 2������ 16����ȭ �Ͽ� ����ϴ� �Լ�
//			 length: ����� text�� length
//			 text  : ����� text
void PrintText(const int length, const int* text) {
	const int fourBit=4, positionNumber[4]={8,4,2,1}; //positionNumber: 2���� �� �ڸ��� value
	int count=0, hexValue=0;;	//hexValue: ���ڸ� 2������ ��ģ value

	while(count < length) {
		hexValue += text[count]*positionNumber[count%fourBit];
		// 2�� text�� �� �ڸ��� * �� �ڸ����� �ش��ϴ� 10���� value
		
		if(count%fourBit == 3) { // 2���� 4�ڸ� ���� ���� & ���
			printf("%X", hexValue);
			hexValue=0;
		}
		count++;
	}
}