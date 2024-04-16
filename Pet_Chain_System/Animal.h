#ifndef __ANIMAL__
#define __ANIMAL__

#include "Category.h"
#include "Certificate.h"
#include "Review.h"

typedef enum {
	eMale, eFemlae, eNofGenderTypes
} eGenderType;

static const char* GenderTypeStr[eNofGenderTypes]
= { "Male", "Female"};


typedef struct
{
	char* name;
	eGenderType type;
	float price;
	Date birth;
	Category* pCategory;
	Certificate cer;
	int reviewCount;
	Review* reviewArr;
}Animal;

void initAnimal(Animal* pAnimal, Category* pCategory, Certificate* pCertificate);
eGenderType getgenderType();
int addReview(Animal* pAnimal);
void printAnimal(const void* val);
void printReviewArr(Review* arr, int size);
void freeAnimal(void* pAnimal);
void freeReviewArr(Review* arr, int size);

#endif // !__ANIMAL__
