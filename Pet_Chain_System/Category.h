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
	Discount* pDiscount;
	eCategoryType type;
}Category;

void initCategory(Category* pCat, const Discount* discount);
eCategoryType getCategoryType();
void printCategory(const Category* pCat);
void freeCategory(Category* pCat);

#endif // !__CATEGORY__