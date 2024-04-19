#ifndef __ANIMAL__
#define __ANIMAL__

#include "Category.h"
#include "Certificate.h"
#include "Review.h"
#include "General.h"
#include "FileHelper.h"

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
int getPrice(Animal* pAnimal);
int addReview(Animal* pAnimal);

// COMPARE FUNCTIONS
int compareAnimalByName(const void* animal1, const void* animal2);
int compareAnimalByPrice(const void* animal1, const void* animal2);
int compareAnimalByBirthDate(const void* animal1, const void* animal2);

// FILE FUNCTIONS
int	saveAnimalToTextFile(const Animal* pAnimal, FILE* fp);
int	loadAnimalFromTextFile(Animal* pAnimal, FILE* fp);
int	saveAnimalToBinaryFile(const Animal* pAnimal, FILE* fp);
int	loadAnimalFromBinaryFile(Animal* pAnimal, FILE* fp);
int	createReviewArr(Animal* pAnimal);
int	saveReviewArrToTextFile(const Animal* pAnimal, FILE* fp, const char* msg);
int	loadReviewArrFromTextFile(Animal* pAnimal, FILE* fp, const char* msg);
int	saveReviewArrToBinaryFile(const Animal* pAnimal, FILE* fp, const char* msg);
int	loadReviewArrFromBinaryFile(Animal* pAnimal, FILE* fp, const char* msg);

// PRINT FUNCTIONS
void printAnimal(const void* val);
void printReviewArr(Review* arr, int size);

// FREE FUNCTIONS
void freeAnimal(void* pAnimal);
void freeReviewArr(Review* arr, int size);

#endif // !__ANIMAL__
