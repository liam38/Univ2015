/*정보 보호
Des 알고리즘을 통한 암호화 프로그램
학번: 2011301039
이름: 박창주
개발환경: C
개발기간: 15.05.22 ~ .05.23

사용자 헤더파일)
keyGenerator.h: round Key 16개를 생성하는데 필요한 알고리즘 구현
cipher.h: plainText를 cipherText로 암호화 하는데 필요한 알고리즘 구현
common.h: cipher와 keyGenerator에서 복합적으로 사용되는 함수들을 구현해 놓은 헤더파일

KeyGen 함수를 통해 48bit Key 16개를 생성하고,
64bit Plain Text를 32bit로 각각 쪼개어 해당하는
Key와 XOR 통해 암호화 과정을 거치는 round를
16회 루프시킴으로써 Cipher Text를 획득.
이 과정에서 해당 알고리즘은 대치와 전치암호의
특성을 동시에 갖게 된다.
  복호화의 경우 16개의 key를 역순으로 넣어주는
것으로 가능하며, 이 경우 암호화 시에 사용되는
키와 동일한 키를 사용해야 한다.(대칭 키 암호)
*/

#include <stdio.h>
#include "keyGenerator.h"
#include "cipher.h"
#include "common.h"

extern int roundKeys[16][48];
extern int cipherText[64];
extern int plainText[64];

void main() {
	printf("Plaintext: ");
	PrintText(64, plainText);
	puts("");
	
	Key_Generator();
	Cipher();

	printf("Ciphertext:");
	PrintText(64, cipherText);
	printf("\n\n");
} 
