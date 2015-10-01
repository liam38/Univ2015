#include <stdio.h>
#include <string.h>
#include "subRoutine.h"
#include "symTab.h"

#define TRUE 1
extern Symtab head;

void main() {
	int state=0, index=0;
	char pState;
	char string[16]={'\0'};
	FILE* compileFile;

	fopen_s(&compileFile, "CompilerText.txt", "rt");
	
	if(compileFile == NULL) {
		printf("file open error!\n");
		return;
	}

	while(TRUE) {
		pState = fgetc(compileFile);

		string[index] = pState;
		index++;

		if(FindSpecialSymbol(pState) || BlankOrNewline(pState) || pState==EOF) {
			if( !BlankOrNewline(string[0]) )
				Scanner(string);

			index=0;
			memset(string, '\0', 16);
		}

		if(pState==EOF) break;
	}

	PrintTab(&head);

	state = fclose(compileFile);
	if(state!=0) {
		printf("file close error!\n");
		return;
	}
	printf("\n\n");

}