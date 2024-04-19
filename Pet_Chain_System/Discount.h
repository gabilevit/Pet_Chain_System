#ifndef __DISCOUNT__
#define __DISCOUNT__

#include "General.h"
#include "FileHelper.h"

#define LEN 6

typedef unsigned char BYTE;

typedef struct
{
	char discountCode[LEN + 1];
	int discountPercent;
}Discount;

int initDiscountWithoutACode(Discount* pDis);
void getDiscountCode(char* code);
int getDiscountPercent(Discount* pDis);

// FILE FUNCTIONS
int	saveDiscountToTextFile(const Discount* pDis, FILE* fp);
int	loadDiscountFromTextFile(Discount* pDis, FILE* fp);
int	saveDiscountToBinaryFileCompressed(const Discount* pDis, FILE* fp);
int	loadDiscountFromBinaryFileCompressed(Discount* pDis, FILE* fp);

// PRINT FUNCTION
void printDiscount(const Discount* pDis);

#endif // !__DISCOUNT__