#ifndef _symTab_h_
#define _symTab_h_

#define Symtab_NUMBER 100
#define STRING_LENGTH 16

typedef struct table{
	char token[16];
	char type[16];

	struct table *next;
}Symtab;

void Insert(Symtab* head, char* token, char* type);
void PrintTab(Symtab* head);

#endif