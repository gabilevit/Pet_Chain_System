#ifndef __DISCOUNT__
#define __DISCOUNT__

#include "General.h"
#include "FileHelper.h"
#include "macros.h"

#define LEN 6

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
int	loadDiscountFromAnyFile(Discount* pDis, char* discountCode, int discountPercent);
int	saveDiscountToBinaryFile(const Discount* pDis, FILE* fp);

// PRINT FUNCTION
void printDiscount(const Discount* pDis);

// FREE FUNCTION
void freeDiscount(Discount* pDis);

#endif // !__DISCOUNT__