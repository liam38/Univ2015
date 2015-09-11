/*���� ��ȣ
Des �˰����� ���� ��ȣȭ ���α׷�
�й�: 2011301039
�̸�: ��â��
����ȯ��: C
���߱Ⱓ: 15.05.22 ~ .05.23

����� �������)
keyGenerator.h: round Key 16���� �����ϴµ� �ʿ��� �˰��� ����
cipher.h: plainText�� cipherText�� ��ȣȭ �ϴµ� �ʿ��� �˰��� ����
common.h: cipher�� keyGenerator���� ���������� ���Ǵ� �Լ����� ������ ���� �������

KeyGen �Լ��� ���� 48bit Key 16���� �����ϰ�,
64bit Plain Text�� 32bit�� ���� �ɰ��� �ش��ϴ�
Key�� XOR ���� ��ȣȭ ������ ��ġ�� round��
16ȸ ������Ŵ���ν� Cipher Text�� ȹ��.
�� �������� �ش� �˰����� ��ġ�� ��ġ��ȣ��
Ư���� ���ÿ� ���� �ȴ�.
  ��ȣȭ�� ��� 16���� key�� �������� �־��ִ�
������ �����ϸ�, �� ��� ��ȣȭ �ÿ� ���Ǵ�
Ű�� ������ Ű�� ����ؾ� �Ѵ�.(��Ī Ű ��ȣ)
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
