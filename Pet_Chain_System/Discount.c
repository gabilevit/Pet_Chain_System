#include <stdio.h>
#include "Discount.h"
#include "General.h"

void getDiscountCode(char* code)
{
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Enter airport code  - %d UPPER CASE letters\t", LEN);
		myGets(temp, MAX_STR_LEN);
		if (strlen(temp) != LEN)
		{
			printf("code should be %d letters\n", LEN);
			ok = 0;
		}
		else {
			for (int i = 0; i < LEN; i++)
			{
				if (isupper(temp[i]) == 0)
				{
					printf("Need to be upper case letter\n");
					ok = 0;
					break;
				}
			}
		}
	} while (!ok);

	strcpy(code, temp);
}

void initDiscountNoCode(Discount* pDis)
{
	pDis->discountPrice = getDiscountPrice();
	if (!pPort->country)
		return 0;
	return 1;
}

float getDiscountPrice()
{

}