#ifndef __DISCOUNT__
#define __DISCOUNT__

#define LEN 6

typedef struct
{
	char discountCode[LEN + 1];
	int discountPercent;
}Discount;

int initDiscountWithoutACode(Discount* pDis);
void getDiscountCode(char* code);
int getDiscountPercent(Discount* pDis);
void printDiscount(const Discount* pDis);

#endif // !__DISCOUNT__