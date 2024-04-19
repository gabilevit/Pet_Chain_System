#ifndef __GENERAL__
#define __GENERAL__

#include <stdio.h>

#define MAX_STR_LEN 255


char* getStrExactName(const char* msg);
char* myGets(char* buffer, int size, FILE* source);
char* getDynStr(char* str);

void generalArrayFunction(void* element, int size, int typeSize, void f(void* element));
int generalSaveLoadArrFile(void* element, int size, int typeSize, FILE* fp, int f(void* element, FILE* fp));

#endif

