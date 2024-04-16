#ifndef __CATEGORY__
#define __CATEGORY__

#include "Discount.h"

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
void printCategory(const Category* pCat);
void freeCategory(Category* pCat);

#endif // !__CATEGORY__