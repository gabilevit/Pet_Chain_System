#include <stdlib.h>
#include <stdio.h>
#include "Animal.h"
#include "General.h"

void initAnimal(Animal* pAnimal, Category* pCategory, Certificate* pCertificate)
{
	pAnimal->name = getStrExactName("Enter pet name");
	if (!pAnimal->name)
		return;
	pAnimal->type = getgenderType();
	getPrice(pAnimal);
	getCorrectDate(&pAnimal->birth);
	pAnimal->pCategory = pCategory;;
	pAnimal->cer = *pCertificate;
	pAnimal->reviewArr = NULL;
	pAnimal->reviewCount = 0;
}

eGenderType getgenderType()
{
	int option;
	printf("\n\n");
	do {
		printf("Please choose one of the following types\n");
		for (int i = 0; i < eNofGenderTypes; i++)
			printf("%d for %s\n", i, GenderTypeStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofGenderTypes);
	getchar();
	return (eGenderType)option;
}

getPrice(Animal* pAnimal)
{
	printf("\nEnter the cost of the pet: ");
	float price;
	do {
		scanf("%f", &price);
		if (price <= 10) {
			printf("Minimum price must be greater or equal than 10.0, try again.\n");
		}
	} while (price <= 10);
	pAnimal->price = price;
}

int addReview(Animal* pAnimal)
{
	pAnimal->reviewArr = (Review*)realloc(pAnimal->reviewArr, (pAnimal->reviewCount + 1) * sizeof(Review));
	if (!pAnimal->reviewArr)
		return 0;
	if (!initReview(&pAnimal->reviewArr[pAnimal->reviewCount]))
	{
		freeReview(&pAnimal->reviewArr[pAnimal->reviewCount]);
		return 0;
	}
	
	pAnimal->reviewCount++;
	return 1;
}

void printAnimal(const  void* val)
{
	const Animal* pAnimal = (const Animal*)val;
	printf("Animal name: %s\n", pAnimal->name);
	printf("Animal gender: %s\n", GenderTypeStr[pAnimal->type]);
	printf("Animal price: %.2f\n", pAnimal->price);
	printf("Birth date: ");
	printDate(&pAnimal->birth);
	printf("\n");
	//printf("Animal category: %s\n", CategoryTypeStr[pAnimal->pCategory->type]);
	printCategory(pAnimal->pCategory);
	printCertificate(&pAnimal->cer);
	printf("\n -------- Has %d Reviews\n", pAnimal->reviewCount);
	printReviewArr(pAnimal->reviewArr, pAnimal->reviewCount);
}

//void printAnimalInShort(const void* val)
//{
//	const Animal* pStore = (const Animal*)val;
//	printf("Store number: %d\n", pStore->storeNumber);
//}

void printReviewArr(Review* arr, int size)
{
	generalArrayFunction(arr, size, sizeof(Review*), printReview);
}

void freeAnimal(void* pAnimal)
{
	Animal* temp = *(Animal**)pAnimal;
	freeCategory(temp->pCategory);
	freeCertificate(&temp->cer);
	freeReviewArr(temp->reviewArr, temp->reviewCount);
	free(temp->reviewArr);
	free(temp->name);
}

void freeReviewArr(Review* arr, int size)
{
	generalArrayFunction(arr, size, sizeof(Review*), freeReview);
}