#ifndef _subRoutine_h_
#define _subRoutine_h_

#include "symTab.h"

Symtab head;

#define STRING_LENGTH 16
#define NON_BIG_ALPHA (string[index]<65 || string[index]>90)
#define NON_SMALL_ALPHA (string[index]<97 || string[index]>122)
#define NON_NUMERAL (string[index]<48 || string[index]>57)
#define PERIOD 46

void Scanner(char* input);
void BookKeeper(char* string, char* type);
void ErrorHandler(char* string, char* message);
int FindSpecialSymbol(char input);
int FindKeywords(char* string);
int FindIdentifires(char* string, char** message);
int FindConstants(char* string);
int BlankOrNewline(char input);

#endif