#ifndef __FILE_HELPER__
#define __FILE_HELPER__

#include <stdio.h>
#include "General.h"

int		writeStringToFile(const char* str, FILE* fp, const char* msg);
int		writeCharsToFile(const char* arr, int size, FILE* fp, const char* msg);
int		writeIntToFile(int val, FILE* fp, const char* msg);
int		writeFloatToFile(float val, FILE* fp, const char* msg);

char* readStringFromFile(FILE* fp, const char* msg);
char* readDynStringFromTextFile(FILE* fp);
int		readCharsFromFile(char* arr, int size, FILE* fp, const char* msg);
int		readIntFromFile(int* val, FILE* fp, const char* msg);
int		readFloatFromFile(float* val, FILE* fp, const char* msg);
int writeIntToTextFile(int val, FILE* fp, const char* msg);
int writeStringToTextFile(const char* str, FILE* fp, const char* msg);
int writeFloatToTextFile(float val, FILE* fp, const char* msg);
int readIntFromTextFile(int* pVal, FILE* fp, const char* msg);
int readfloatFromTextFile(float* pVal, FILE* fp, const char* msg);

#endif // !__FILE_HELPER__