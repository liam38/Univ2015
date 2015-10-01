#include "symTab.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void Insert(Symtab* head, char* token, char* type) {
	Symtab* newNode = (Symtab*)malloc(sizeof(Symtab));
	Symtab* insteadNode = head;

	strcpy(newNode->token, token);
	strcpy(newNode->type, type);
	newNode->next = NULL;

	while(insteadNode->next != NULL)
		insteadNode = insteadNode->next;
	
	insteadNode->next = newNode;
}

void PrintTab(Symtab* head) {
	Symtab* insteadNode = head;

	printf("\n======================== printing Symtab ========================\n");
	while(insteadNode->next != NULL) {
		insteadNode = insteadNode->next;
		if(strlen(insteadNode->token) > 8)
			printf("%s	: %s\n", insteadNode->token, insteadNode->type);
		else
			printf("%s		: %s\n", insteadNode->token, insteadNode->type);
	}
}