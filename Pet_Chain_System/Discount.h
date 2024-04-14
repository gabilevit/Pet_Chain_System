#ifndef __DISCOUNT__
#define __DISCOUNT__

#define LEN 3

typedef struct
{
	char discountCode[LEN + 1];
	float discountPrice;
}Discount;

void getDiscountCode(char* code);
float getDiscountPrice();
void initDiscountNoCode(Discount* pDis);
void printDiscount(const Discount* pDis);

#endif // !__DISCOUNT__