#ifndef __GENERAL__
#define __GENERAL__

#define MAX_STR_LEN 255


char* getStrExactName(const char* msg);
char* myGets(char* buffer, int size);
char* getDynStr(char* str);

void generalArrayFunction(void* element, int size, int typeSize, void f(void* element));

#endif

