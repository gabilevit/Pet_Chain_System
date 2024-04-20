#include <stdio.h>
#include <string.h>
#include <ctype.h>
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
	if (!writeStringToTextFile(pDis->discountCode, fp, "Error writing discount code to text file\n"))
		return 0;
	if (!writeIntToTextFile(pDis->discountPercent, fp, "Error writing discount in percent to text file\n"))
		return 0;
	return 1;
}

int	loadDiscountFromTextFile(Discount* pDis, FILE* fp)
{
	myGets(pDis->discountCode, LEN+1, fp);
	if (!readIntFromTextFile(&pDis->discountPercent, fp, "Error reading discount in percent from text file\n"))
		return 0;
	return 1;
}

int	saveDiscountToBinaryFileCompressed(const Discount* pDis, FILE* fp)
{
	BYTE data[2] = { 0 };
	int len = (int)strlen(pDis->discountCode);
	data[0] =  len >> 1;
	data[1] = (len & 0x1) << 7 | pDis->discountPercent;
	if (fwrite(data, sizeof(BYTE), 2, fp) != 2) 
	{
		puts("Error writing date to file");
		return 0;
	}
	if (!writeStringToFile(pDis->discountCode, fp, "Error writing discount code to binary file\n"))
		return 0;
	return 1;
}

int	loadDiscountFromBinaryFileCompressed(Discount* pDis, FILE* fp)
{
	if (!pDis)
		return 0;
	BYTE data[2];
	if (fread(&data, sizeof(BYTE), 2, fp) != 2)
	{
		puts("Error writing date to file");
		return 0;
	}
	int len = (data[0] << 1) & 0x7;
	pDis->discountPercent = data[1] & 0x7F;
	myGets(pDis->discountCode, MAX_STR_LEN, fp);
	return 1;
}

void printDiscount(const Discount* pDis)
{
	printf("The discount code is: %s\n", pDis->discountCode);
	printf("This category of animals in this type has a discount of %d%\n", pDis->discountPercent);
}


