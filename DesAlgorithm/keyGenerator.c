#include "keyGenerator.h"
#include "common.h"

//roundKeys: 키젠으로 생성된 48bit-key 16개 변수
extern int roundKeys[16][48];

//parityDropTable: 패리티 비트 제거 표 [축소 P-BOX (64:56)]
int parityDropTable[56] = {57, 49, 41, 33, 25, 17, 9, 1,
      58, 50, 42, 34, 26, 18, 10, 2,
      59, 51, 43, 35, 27, 19, 11, 3,
      60, 52, 44, 36, 63, 55, 47, 39,
      31, 23, 15, 7, 62, 54, 46, 38,
      30, 22, 14, 6, 61, 53, 45, 37,
      29, 21, 13, 5, 28, 20, 12, 4};

//keyCompressionTable: 축소 치환 표 [축소 P-BOX (56:48)]
int keyCompressionTable[48] = {14, 17, 11, 24, 1, 5, 3, 28,
       15, 6, 21, 10, 23, 19, 12, 4,
       26, 8, 16, 7, 27, 20, 13, 2,
       41, 52, 31, 37, 47, 55, 30, 40,
       51, 45, 33, 48, 44, 49, 39, 56,
       34, 53, 46, 42, 50, 36, 29, 32};

//shiftTable: shift 비트량 표
int shiftTable[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

//keyWithParities: 최초에 입력되는 key
int keyWithParities[64] = {1,0,1,0, 1,0,1,0,
							1,0,1,1, 1,0,1,1,
							0,0,0,0, 1,0,0,1,
							0,0,0,1, 1,0,0,0,
							0,0,1,0, 0,1,1,1,
							0,0,1,1, 0,1,1,0,
							1,1,0,0, 1,1,0,0,
							1,1,0,1, 1,1,0,1};
//cipherKey: 최초입력받은 key에서 패리티를 제거한 이후의 key value
int cipherKey[56] = {0};
//leftKey, rightKey: shift를 위해 cipherKey를 분할한 결과 좌측,우측 key
int leftKey[28]={0}, rightKey[28]={0};

//ShiftLeft) 좌향 비트 이동(shift) 함수
//			 block		: shift 시킬 block
//			 numOfShifts: shift 할 bit 수
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

//Key_Generator) 키 생성 함수
void Key_Generator() {
	int round=0;
	
	Permute(56, keyWithParities, cipherKey, parityDropTable);//최초 입력키(64bit)를 cipherKey(56bit)에 축소저장
	Split(56, 28, cipherKey, leftKey, rightKey);//56bit cipherKey를 28bit로 각각 쪼개어 left,rightKey에 저장

	while(round<16) { // 16개의 key 생성
		ShiftLeft(rightKey, shiftTable[round]);//우측 키 shift
		ShiftLeft(leftKey, shiftTable[round]);//좌측 키 shift
		Combine(28, 56, leftKey, rightKey, cipherKey);//좌우측 키 병합
		Permute(48, cipherKey, roundKeys[round], keyCompressionTable);//합쳐진 cipherKey(56bit) 48bit로 치환
		round++;
	}
}


