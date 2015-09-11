#include <stdio.h>
#include "cipher.h"
#include "common.h"

extern int roundKeys[16][48];

//initPermutation: �ʱ� ġȯ) �ܼ�P-BOX
int initPermutation[64]={58, 50, 42, 34, 26, 18, 10, 2,
						60, 52, 44, 36, 28, 20, 12, 4,
						62, 54, 46, 38, 30, 22, 14, 6,
						64, 56, 48, 40, 32, 24, 16, 8,
						57, 49, 41, 33, 25, 17, 9, 1,
						59, 51, 43, 35, 27, 19, 11, 3,
						61, 53, 45, 37, 29, 21, 13, 5,
						63, 55, 47, 39, 31, 23, 15, 7};
//finPermutation: ���� ġȯ) �ܼ�P-BOX
int finalPermutation[64]={40, 8, 48, 16, 56, 24, 64, 32,
						39, 7, 47, 15, 55, 23, 63, 31,
						38, 6, 46, 14, 54, 22, 62, 30,
						37, 5, 45, 13, 53, 21, 61, 29,
						36, 4, 44, 12, 52, 20, 60, 28,
						35, 3, 43, 11, 51, 19, 59, 27,
						34, 2, 42, 10, 50, 18, 58, 26,
						33, 1, 41, 9, 49, 17, 57, 25};
//expansionPermutation: Ȯ��P-BOX (32:48)
int expansionPermutation[48]={32, 1, 2, 3, 4, 5,
							4, 5, 6, 7, 8, 9,
							8, 9, 10, 11, 12, 13,
							12, 13, 14, 15, 16, 17,
							16, 17, 18, 19, 20, 21,
							20, 21, 22, 23, 24, 25,
							24, 25, 26, 27, 28, 29,
							28, 29, 30, 31, 32, 01};
//plainText: 64bit �ʱ� ��
int plainText[64]={0,0,0,1, 0,0,1,0,
					0,0,1,1, 0,1,0,0,
					0,1,0,1, 0,1,1,0,
					1,0,1,0, 1,0,1,1,
					1,1,0,0, 1,1,0,1,
					0,0,0,1, 0,0,1,1,
					0,0,1,0, 0,1,0,1,
					0,0,1,1, 0,1,1,0};  //��
					/*{1,1,0,0, 0,0,0,0,
					 1,0,1,1, 0,1,1,1,
					 1,0,1,0, 1,0,0,0,
					 1,1,0,1, 0,0,0,0,
					 0,1,0,1, 1,1,1,1,
					 0,0,1,1, 1,0,1,0,
					 1,0,0,0, 0,0,1,0,
					 1,0,0,1, 1,1,0,0};*/  //��ȣ��
							//S-Box 1
int substituteBOX[8][4][16]={{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
							  0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
							  4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
							  15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13},
							//S-Box 2  
							  {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
							   3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
							   0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
							   13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9},
							//S-Box 3
							  {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
							   13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
							   13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
							   1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12},
							//S-Box 4
							  {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
							   13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
							   10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
							   3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14},
							//S-Box 5
							  {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
							   14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
							   4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
							   11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3},
							//S-Box 6
							  {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
							   10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
							   9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
							   4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13},
							//S-Box 7
							  {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
							   13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
							   1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
							   6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12},
							//S-Box 8
							  {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
							   1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
							   7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
							   2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}};
int straightPermutation[32]={16,7,20,21,29,12,28,17,
							 1,15,23,26,5,18,31,10,
							 2,8,24,14,32,27,3,9,
							 19,13,30,6,22,11,4,25};
int cipherText[64]={0}, cipherTemp[64]={0};//cipherText:64bit ���� ��ȣ��
int left[32]={0}, right[32]={0};//���� ��ȣ��, ���� ��ȣ��
int leftTemp[32]={0};//���� XOR�뵵 32bit

//Cipher) ��ȣȭ&��ȣȭ �Լ�
void Cipher() {
	int round=0; //round ����: 48bit Key�� XOR Ƚ��(16ȸ)

	//Permute : �ʱ�ġȯ �Լ�
	Permute(64, plainText, cipherText, initPermutation);//��(64bit) �ܼ�ġȯ(�ʱ�ġȯǥ�� �ǰ�)

	printf("After initial permutation: ");
	PrintText(64, cipherText);
	puts("");
	
	//Split : bit ���� �Լ�
	Split(64, 32, cipherText, left, right);//64bit cipherText�� 32bit�� ���� ����(left, right)

	printf("After splitting: L0=");
	PrintText(32, left);
	printf("  R0=");
	PrintText(32, right);
	printf("\n\n");

	while(round<16) {		//Key & function�� XOR [16ȸ]
		Mixer(left, right, roundKeys[round]); //roundKeys�� index�� round �� ��, ��ȣȭ
		if(round!=15) Swapper(left, right);	  //					15-round �� ��, ��ȣȭ

		printf("Round %-10d", round+1);
		printf("Left: ");
		PrintText(32, left);
		printf("   Right: ");
		PrintText(32, right);
		printf("   RoundKey: ");
		PrintText(48, roundKeys[round]);//index�� round �� ��, ��ȣȭ
		puts("");						   //		 15-round �� ��, ��ȣȭ
		
		round++;
	}

	Combine(32, 64, left, right, cipherTemp);//32bit�� ���ҵ� left�� right�� cipherTemp�� ����
	
	puts("");
	printf("After combination:");
	PrintText(64, cipherTemp);
	puts("");

	Permute(64, cipherTemp, cipherText, finalPermutation);//64bit cipherTemp�� ����ġȯ(����ġȯǥ�� �ǰ�) => cipherText
}

//Mixer) 32bit�� ���ҵ� right�� roundKey�� XOR. �� ����� left�� XOR �ϴ� �Լ�
//		 leftBlock : ���� 32bit
//		 rightBlock: ���� 32bit
//		 roundKey  : 16�� key�� ���� round�� �ش��ϴ� Key
void Mixer(int leftBlock[32], int rightBlock[32], const int roundKey[48]) {
	Function(rightBlock, roundKey);
	ExclusiveOr(32, left, leftTemp);
}

//Swapper) ���� 32bit (right), ���� 32bit (left)�� �ڸ��ٲ� �Լ�
//		   leftBlock : ���� 32bit
//		   rightBlock: ���� 32bit
void Swapper(int leftBlock[32], int rightBlock[32]) {
	int temp=0, index=0;

	while(index < 32) {
		temp = leftBlock[index];
		leftBlock[index] = rightBlock[index];
		rightBlock[index] = temp;
		index++;
	}
}

//Function) 32bit right�� �޾�, 48bit�� Ȯ���Ͽ�, key(48bit)�� XOR.
//			���� ������� 32bit�� ���.
//			inBlock : �޾ƿ� 32bit (right)
//			roundKey: 16�� key�� ���� round�� �ش��ϴ� Key
void Function(int* inBlock, const int* roundKey) {
	int temp32[32]={0}, temp48[48]={0};

	Permute(48, inBlock, temp48, expansionPermutation);//32bit inBlock(right)�� 48bit�� Ȯ��(Ȯ��P-Box) ���� temp48�� ����
	ExclusiveOr(48, temp48, roundKey);//temp48(48bit)�� roundKey(48bit)�� XOR
	Substitute(temp48, temp32);//48bit temp48�� 32bit�� ���
	Permute(32, temp32, leftTemp, straightPermutation);//32bit�� ��ҵ� temp32�� �ܼ�ġȯ ���� leftTemp�� ����
}

//ExclusiveOr) �ش� ���̸� ���� �� Block�� XOR �ϴ� �Լ�
//			   length	 : XOR �� Block length
//			   inputBlock: XOR�� �ǿ�����. XOR ���� Value�� ������� Block
//			   operand	 : XOR�� �ǿ�����.
void ExclusiveOr(const int length, int* inputBlock, const int* operand) {
	int count=0;
	while(count < length) {
		if(inputBlock[count] == operand[count]) inputBlock[count]=0;//�� �ǿ������� value�� ������ 0
		else inputBlock[count]=1;									//						�ٸ��� 1
		count++;
	}
}

//Substitute) 48bit Block�� 32bit�� ���
//			  inBlock : ��ҽ�ų 48bit Block
//			  outBlock: ����� ������ 32bit Block
void Substitute(int* inBlock, int* outBlock) {
	int count=0, row=0, col=0, value=0;

	while(count < 8) { //48bit Block�� 6bit¥�� 8�������� ����
		row=2*inBlock[count*6] + inBlock[count*6+5];//6bit �� ������ ù��° bit�� ������ bit�� ��(row)�� ����
		col=8*inBlock[count*6+1] + 4*inBlock[count*6+2] + 2*inBlock[count*6+3] + inBlock[count*6+4];
		//6bit �� ������ 2,3,4,5��° bit�� ��(column)�� ����

		value=substituteBOX[count][row][col];//�ش� ��ġ�� ���� value�� ����

		//10������ �̷���� value���� 2������ �ٲپ� outBlock�� ����
		outBlock[count*4] = value/8;
		value%=8;
		outBlock[count*4+1] = value/4;
		value%=4;
		outBlock[count*4+2] = value/2;
		value%=2;
		outBlock[count*4+3] = value;
		count++;
	}
}