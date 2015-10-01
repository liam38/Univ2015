#include "keyGenerator.h"
#include "common.h"

//roundKeys: Ű������ ������ 48bit-key 16�� ����
extern int roundKeys[16][48];

//parityDropTable: �и�Ƽ ��Ʈ ���� ǥ [��� P-BOX (64:56)]
int parityDropTable[56] = {57, 49, 41, 33, 25, 17, 9, 1,
      58, 50, 42, 34, 26, 18, 10, 2,
      59, 51, 43, 35, 27, 19, 11, 3,
      60, 52, 44, 36, 63, 55, 47, 39,
      31, 23, 15, 7, 62, 54, 46, 38,
      30, 22, 14, 6, 61, 53, 45, 37,
      29, 21, 13, 5, 28, 20, 12, 4};

//keyCompressionTable: ��� ġȯ ǥ [��� P-BOX (56:48)]
int keyCompressionTable[48] = {14, 17, 11, 24, 1, 5, 3, 28,
       15, 6, 21, 10, 23, 19, 12, 4,
       26, 8, 16, 7, 27, 20, 13, 2,
       41, 52, 31, 37, 47, 55, 30, 40,
       51, 45, 33, 48, 44, 49, 39, 56,
       34, 53, 46, 42, 50, 36, 29, 32};

//shiftTable: shift ��Ʈ�� ǥ
int shiftTable[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

//keyWithParities: ���ʿ� �ԷµǴ� key
int keyWithParities[64] = {1,0,1,0, 1,0,1,0,
							1,0,1,1, 1,0,1,1,
							0,0,0,0, 1,0,0,1,
							0,0,0,1, 1,0,0,0,
							0,0,1,0, 0,1,1,1,
							0,0,1,1, 0,1,1,0,
							1,1,0,0, 1,1,0,0,
							1,1,0,1, 1,1,0,1};
//cipherKey: �����Է¹��� key���� �и�Ƽ�� ������ ������ key value
int cipherKey[56] = {0};
//leftKey, rightKey: shift�� ���� cipherKey�� ������ ��� ����,���� key
int leftKey[28]={0}, rightKey[28]={0};

//ShiftLeft) ���� ��Ʈ �̵�(shift) �Լ�
//			 block		: shift ��ų block
//			 numOfShifts: shift �� bit ��
void ShiftLeft(int* block, int numOfShifts) {
	int count=0;
	int temp=0, index=0;

	while(count < numOfShifts) {
		temp=block[0];
		for(index=1;index<28;index++) block[index-1]=block[index];

		block[27]=temp;
		count++;
	}
}

//Key_Generator) Ű ���� �Լ�
void Key_Generator() {
	int round=0;
	
	Permute(56, keyWithParities, cipherKey, parityDropTable);//���� �Է�Ű(64bit)�� cipherKey(56bit)�� �������
	Split(56, 28, cipherKey, leftKey, rightKey);//56bit cipherKey�� 28bit�� ���� �ɰ��� left,rightKey�� ����

	while(round<16) { // 16���� key ����
		ShiftLeft(rightKey, shiftTable[round]);//���� Ű shift
		ShiftLeft(leftKey, shiftTable[round]);//���� Ű shift
		Combine(28, 56, leftKey, rightKey, cipherKey);//�¿��� Ű ����
		Permute(48, cipherKey, roundKeys[round], keyCompressionTable);//������ cipherKey(56bit) 48bit�� ġȯ
		round++;
	}
}


