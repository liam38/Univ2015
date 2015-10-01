#include "subRoutine.h"
#include "symTab.h"
#include <stdio.h>
#include <string.h>

void Scanner(char* input) {
	char* errorMessage=NULL;
	char specialToken;
	char* p;
	if(!FindSpecialSymbol(input[0])) {
		specialToken = input[strlen(input)-1];
		if(specialToken == EOF)
			input[strlen(input)-1] = '\0';
		else
			strtok_s(input, "\n;()	+-*/=,<> ", &p);
		
		if(FindConstants(input)) {
			printf("%s			: %s\n", input, "Constants");
			BookKeeper(input, "Constants");
		}
		else if(FindKeywords(input)) {
			printf("%s			: %s\n", input, "Keyword");
		}
		else if(FindIdentifires(input, &errorMessage)) {
			printf("%s			: %s\n", input, "Identifire");
			BookKeeper(input, "Identifire");
		}
		else ErrorHandler(input, errorMessage);
	
		if(FindSpecialSymbol(specialToken))
			printf("%c			: %s\n", specialToken, "SpecialSymbol");
	}

	else printf("%c			: %s\n", input[0], "SpecialSymbol");
}

void BookKeeper(char* string, char* type) {
	Insert(&head, string, type);
}

void ErrorHandler(char* string, char* message) {
	printf("%s			: %s\n", string, message);
}

int FindSpecialSymbol(char input) {
	int index = 0;
	const char specialSymbol[11] = {';', '(', ')', '+', '-', '*', '/', '=', ',', '<', '>'};
	
	while(index < 11) {
		if(input==specialSymbol[index])
			return 1;
		index++;
	}
	return 0;
}

int FindKeywords(char* string) {
	int index = 0;
	const char keywords[15][8] = {"program", "begin", "end", "if", "then",
								  "else", "while", "do", "int", "float",
								  "char", "read", "write", "and", "or"};

	while(index < 15) {
		if(strcmp(string,keywords[index])==0)
			return 1;
		index++;
	}
	return 0;
}

int FindIdentifires(char* string, char** message) {
	int index = 0;
	
	if(strlen(string) > STRING_LENGTH) {
		*message = "unvalid Identifire for over length.";
		return 0; //unvalid Identifire for over length.
	}
	if(NON_BIG_ALPHA && NON_SMALL_ALPHA) {
		*message = "unvalid Identifire for unvalid initial letter.";
		return 0; //unvalid Identifire for unvalid initial letter.
	}

	while( (string[index]!='\0') ) {
		if(NON_BIG_ALPHA && NON_SMALL_ALPHA && NON_NUMERAL && (string[index] != PERIOD)) {
			*message = "unvalid Identifire for unvalid character.";
			return 0; //unvalid Identifire for unvalid character.
		}
		if(string[index] == PERIOD && string[index-1] == PERIOD) {
			*message = "unvalid Identifire for consecutive periods.";
			return 0; //unvalid Identifire for consecutive periods.
		}
		index++;
	}
	return 1;
}

int FindConstants(char* string) {
	int index = 0;
	
	if(strlen(string) > STRING_LENGTH) return 0; //unvalid Identifire for over length.
	if(NON_NUMERAL) return 0; //unvalid Identifire for not numeral followed string.
	
	while( string[index]!='\0' ) {
		if(NON_NUMERAL && (string[index]!=PERIOD) )
			return 0; //unvalid Identifire for unvalid character.
		if(string[index] == PERIOD && string[index-1] == PERIOD) {
			return 0; //unvalid Identifire for consecutive periods.
		}
		index++;
	}
	return 1;
}

int BlankOrNewline(char input) {
	int index = 0;
	const char specialSymbol[3] = {' ', '	', '\n'};
	
	while(index < 3) {
		if(input==specialSymbol[index])
			return 1;
		index++;
	}
	return 0;
}