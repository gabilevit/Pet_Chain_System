#ifndef __ANIMAL__
#define __ANIMAL__

#include "Category.h"
#include "Certificate.h"
#include "Review.h"

typedef struct
{
	char* name;
	float price;
	Date birth;
	Category* pCategory;
	Certificate cer;
	int reviewCount;
	Review* reviewArr;
}Animal;

void initAnimal(Animal* pAnimal);
int addReview(Animal* pAnimal);
void printAnimal(const Animal* pAnimal);
void freeAnimal(Animal* pAnimal);

#endif // !__ANIMAL__
