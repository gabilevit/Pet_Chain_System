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
		PRINT_RETURN_NUM(pCat->pDiscount, 0, "Alocation error for discount");
	}
	else // updateDiscount
	{
		puts("A discount already exists for this category. Do you want to update it? (1/0): ");
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
		puts("This code already in use - if you are updating the discount you need to make a new code\n");
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

int	saveCategoryToTextFile(Category* pCat, FILE* fp)
{
	WRITE_INT_TEXT_FILE_PRINT_RETURN(pCat->type, fp, "Error writing category type to text file\n", 0);
	if (pCat->pDiscount == NULL)
	{
		// If there is no discount save to file info that can asure that there is NO discount
		WRITE_STRING_TEXT_FILE_PRINT_RETURN("XXXXXX", fp, "Error writing to text file\n", 0);
		WRITE_INT_TEXT_FILE_PRINT_RETURN(0, fp, "Error writing text file\n", 0);
	}
	else if(!saveDiscountToTextFile(pCat->pDiscount, fp))
		return 0;
	return 1;
}

int	loadCategoryFromTextFile(Category* pCat, FILE* fp)
{
	int type;
	if (!readIntFromTextFile(&type, fp, "Error reading category type from text file\n"))
		return 0;
	pCat->type = type;
	char isDiscountCode[LEN + 1];
	myGets(isDiscountCode, LEN + 1, fp);
	int isDiscountPercent;
	if (!readIntFromTextFile(&isDiscountPercent, fp, "Error reading discount in percent from text file\n"))
		return 0;
	// If there wasnt a discount 
	if (!strcmp(isDiscountCode, "XXXXXX") && (isDiscountPercent == 0))
	{
		return 1;
	}
	if (!createDiscount(pCat))
		return 0;
	if (!loadDiscountFromAnyFile(pCat->pDiscount, isDiscountCode, isDiscountPercent))
		return 0;
	return 1;
}

int	saveCategoryToBinaryFile(Category* pCat, FILE* fp)
{
	WRITE_INT_BINARY_FILE_PRINT_RETURN(pCat->type, fp, "Error writing category type to binary file\n", 0);
	if (pCat->pDiscount == NULL)
	{
		// If there is no discount save to file info that can asure that there is NO discount
		WRITE_STRING_BINARY_FILE_PRINT_RETURN("XXXXXX", fp, "Error writing to text file\n", 0);
		WRITE_INT_BINARY_FILE_PRINT_RETURN(0, fp, "Error writing text file\n", 0);
	}
	else if (!saveDiscountToBinaryFile(pCat->pDiscount, fp))
		return 0;
	return 1;
}

int	loadCategoryFromBinaryFile(Category* pCat, FILE* fp)
{
	int type;
	if (!readIntFromFile(&type, fp, "Error reading category type from binary file\n"))
		return 0;
	pCat->type = type;
	char* isDiscountCode;
	isDiscountCode = readStringFromFile(fp, "Error reading discount code from binary file\n");
	int isDiscountPercent;
	if (!readIntFromFile(&isDiscountPercent, fp, "Error reading discount in percent from binary file\n"))
		return 0;
	// If there wasnt a discount 
	if (!strcmp(isDiscountCode, "XXXXXX") && (isDiscountPercent == 0))
	{
		return 1;
	}
	if (!createDiscount(pCat))
		return 0;
	if (!loadDiscountFromAnyFile(pCat->pDiscount, isDiscountCode, isDiscountPercent))
		return 0;
	return 1;
}

int createDiscount(Category* pCat)
{
	pCat->pDiscount = (Discount*)calloc(1, sizeof(Discount));
	if (!pCat->pDiscount) {
		puts("Error allocating memory for discount\n");
		freeDiscount(pCat->pDiscount);
		return 0;
	}
	return 1;
}

void printCategory(const Category* pCat)
{
	printf("Category type: %s\n", CategoryTypeStr[pCat->type]);
	if (pCat->pDiscount != NULL)
		printDiscount(pCat->pDiscount);
	else
		puts("This category of animals doesnt have an discount\n");
}

void freeCategory(Category* pCat)
{
	FREE_POINTER(pCat->pDiscount);
}


