#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Discount.h"

int initDiscountWithoutACode(Discount* pDis)
{
	return getDiscountPercent(pDis);
}

void getDiscountCode(char* code)
{
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Enter discount code  - %d SHOULD BE 4 UPPER CASE letters AND 2 digits\t", LEN);
		myGets(temp, MAX_STR_LEN, stdin);
		if (strlen(temp) != LEN)
		{
			printf("code should be %d in lenght\n", LEN);
			ok = 0;
		}
		else {
			for (int i = 0; i < LEN; i++)
			{
				if (i <= 3) // the first 4 uppercase letters
				{
					if (isupper(temp[i]) == 0)
					{
						printf("First 4 letters need to be upper case letters\n");
						ok = 0;
						break;
					}
				}
				else if (isdigit(temp[i]) == 0)
				{
					printf("The code needs to end with last 2 digits\n");
					ok = 0;
					break;
				}
			}
		}
	} while (!ok);

	strcpy(code, temp);
}

int getDiscountPercent(Discount* pDis)
{
	printf("Enter how much discount percent the the category of animals will have: ");
	int discountPercent;
	do {
		scanf("%d", &discountPercent);
		if (discountPercent <= 5 || discountPercent >= 70) 
			puts("The discount cant be less then 5% or greater than 70%, try again.\n");
	} while (discountPercent <= 5 || discountPercent >= 70);
	pDis->discountPercent = discountPercent;
	return 1;
}

int	saveDiscountToTextFile(const Discount* pDis, FILE* fp)
{
	WRITE_STRING_TEXT_FILE_PRINT_RETURN(pDis->discountCode, fp, "Error writing discount code to text file\n", 0);
	WRITE_INT_TEXT_FILE_PRINT_RETURN(pDis->discountPercent, fp, "Error writing discount in percent to text file\n", 0);
	return 1;
}

int	loadDiscountFromAnyFile(Discount* pDis, char* discountCode, int discountPercent)
{
	strcpy(pDis->discountCode, discountCode);
	if (!pDis->discountCode)
		return 0;
	pDis->discountPercent = discountPercent;
	return 1;
}

int	saveDiscountToBinaryFile(const Discount* pDis, FILE* fp)
{
	WRITE_STRING_BINARY_FILE_PRINT_RETURN(pDis->discountCode, fp, "Error writing discount code to binary file\n", 0);
	WRITE_INT_BINARY_FILE_PRINT_RETURN(pDis->discountPercent, fp, "Error writing discount percent to binary file\n", 0);
	return 1;
}

void printDiscount(const Discount* pDis)
{
	printf("The discount code is: %s\n", pDis->discountCode);
	printf("This category of animals in this type has a discount of %d percent\n", pDis->discountPercent);
}

void freeDiscount(Discount* pDis)
{
	FREE_POINTER(pDis);
}


