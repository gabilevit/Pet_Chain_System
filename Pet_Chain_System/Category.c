#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Category.h"

void initCategory(Category* pCat, int option)
{
	pCat->type = (eCategoryType)option;
	pCat->pDiscount = NULL;
}

eCategoryType getCategoryType()
{
	int option;
	printf("\n\n");
	do {
		printf("Please choose one of the following types\n");
		for (int i = 0; i < eNofCategoryTypes; i++)
			printf("%d for %s\n", i, CategoryTypeStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofCategoryTypes);
	getchar();
	return (eCategoryType)option;
}

int addDiscountOrUpdateDiscount(Category* pCat)
{
	if (pCat->pDiscount == NULL) // addNewDiscount
	{
		pCat->pDiscount = (Discount*)calloc(1, sizeof(Discount));
		if (!pCat->pDiscount)
			return 0;
	}
	else // updateDiscount
	{
		printf("A discount already exists for this category. Do you want to update it? (1/0): ");
		int updateChoice;
		scanf("%d", &updateChoice);
		if (!updateChoice) 
			return 1; 
	}
	if (!initDiscount(pCat->pDiscount, pCat))
		return 0;
	return 1;
}

int initDiscount(Discount* pDiscount, Category* pCat)
{
	while (1)
	{
		getDiscountCode(pDiscount->discountCode);
		if (checkUniqeCode(pDiscount->discountCode, pCat))
			break;
		printf("This code already in use - if you are updating the discount you need to make a new code\n");
	}

	return initDiscountWithoutACode(pDiscount);
}

int checkUniqeCode(const char* code, const Category* pCat)
{
	// Check if the category has a discount
	if (pCat->pDiscount == NULL) {
		return 0; // No discount, so the code is unique
	}

	// Compare the entered code with the discount code of the category
	if (strcmp(pCat->pDiscount->discountCode, code) == 0) {
		// If the entered code matches the category's specific discount code, it's not unique
		return 1; // Code is not unique
	}

	// If the code does not match the specific category's discount code, it's unique
	return 0; // Code is unique
}

void printCategory(const Category* pCat)
{
	printf("Category type: %s\n", CategoryTypeStr[pCat->type]);
	if (pCat->pDiscount != NULL)
		printDiscount(pCat->pDiscount);
	else
		printf("This category of animals doesnt have an discount");
}

void freeCategory(Category* pCat)
{
	free(pCat->pDiscount);
}


