#ifndef __CATEGORY__
#define __CATEGORY__

#include "Discount.h"
#include "FileHelper.h"

typedef enum {
	eDog, eCat, eBird, eNofCategoryTypes
} eCategoryType;

static const char* CategoryTypeStr[eNofCategoryTypes]
= { "Dog", "Cat", "Bird" };

typedef struct
{
	eCategoryType type;
	Discount* pDiscount;
}Category;

void initCategory(Category* pCat, int option);
eCategoryType getCategoryType();
int addDiscountOrUpdateDiscount(Category* pCat);
int initDiscount(Discount* pDiscount, Category* pCat);
int checkUniqeCode(const char* code, const Category* pCat);

// FILE FUNCTIONS
int	saveCategoryToTextFile(Category* pCat, FILE* fp);
int	loadCategoryFromTextFile(Category* pCat, FILE* fp);
int	saveCategoryToBinaryFile(Category* pCat, FILE* fp);
int	loadCategoryFromBinaryFile(Category* pCat, FILE* fp);
int createDiscount(Category* pCat);

// PRINT FUNCTION
void printCategory(const Category* pCat);

// FREE FUNCTION
void freeCategory(Category* pCat);

#endif // !__CATEGORY__