#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Animal.h"

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

int getPrice(Animal* pAnimal)
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
	return 1;
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

int compareAnimalByName(const void* animal1, const void* animal2)
{
	const Animal* pAnimal1 = *(const Animal**)animal1;
	const Animal* pAnimal2 = *(const Animal**)animal2;
	return strcmp(pAnimal1->name, pAnimal2->name);
}

int compareAnimalByPrice(const void* animal1, const void* animal2)
{
	const Animal* pAnimal1 = *(const Animal**)animal1;
	const Animal* pAnimal2 = *(const Animal**)animal2;
	if (pAnimal1->price > pAnimal2->price)
		return 1;
	if (pAnimal1->price < pAnimal2->price)
		return -1;
	return 0;
}

int compareAnimalByBirthDate(const void* animal1, const void* animal2)
{
	const Animal* pAnimal1 = *(const Animal**)animal1;
	const Animal* pAnimal2 = *(const Animal**)animal2;
	return compareDate(&pAnimal1->birth, &pAnimal2->birth);
	return 0;
}

int	saveAnimalToTextFile(const Animal* pAnimal, FILE* fp)
{
	if (!writeStringToTextFile(pAnimal->name, fp, "Error writing name to text file\n"))
		return 0;
	if (!writeIntToTextFile(pAnimal->type, fp, "Error writing gender type to text file\n"))
		return 0;
	if (!writeFloatToTextFile(pAnimal->price, fp, "Error writing price to text file\n"))
		return 0;
	if (!saveDateToTextFile(&pAnimal->birth, fp))
		return 0;
	if (!saveCategoryToTextFile(pAnimal->pCategory, fp))
		return 0;
	if (!saveCertificateToTextFile(&pAnimal->cer, fp))
		return 0;
	if (!writeIntToTextFile(pAnimal->reviewCount, fp, "Error writing number of reviews to text file\n"))
		return 0;
	if (!saveReviewArrToTextFile(pAnimal, fp, "Error writing reviews to text file\n"))
		return 0;
	return 1;
}

int	loadAnimalFromTextFile(Animal* pAnimal, FILE* fp)
{
	pAnimal->name = readDynStringFromTextFile(fp);
	if (!readIntFromTextFile(&pAnimal->type, fp, "Error reading gender type from text file\n"))
		return 0;
	if (!readfloatFromTextFile(&pAnimal->price, fp, "Error reading price from text file\n"))
		return 0;
	if (!loadDateFromTextFile(&pAnimal->birth, fp))
		return 0;
	if (!createCategory(pAnimal))
		return 0;
	if (!loadCategoryFromTextFile(pAnimal->pCategory, fp))
		return 0;
	if (!createCertificate(pAnimal))
		return 0;
	if (!loadCertificateFromTextFile(&pAnimal->cer, fp))
		return 0;
	if (!readIntFromTextFile(&pAnimal->reviewCount, fp, "Error reading number of reviews from text file\n"))
		return 0;
	if (!createReviewArr(pAnimal))
		return 0;
	if (!loadReviewArrFromTextFile(pAnimal, fp, "Error reading reviews from text file\n"))
		return 0;
	return 1;
}

int	saveAnimalToBinaryFile(const Animal* pAnimal, FILE* fp)
{
	if (!writeStringToFile(pAnimal->name, fp, "Error writing name to binary file\n"))
		return 0;
	if (!writeIntToFile(pAnimal->type, fp, "Error writing gender type to binary file\n"))
		return 0;
	if (!writeFloatToFile(pAnimal->price, fp, "Error writing price to binary file\n"))
		return 0;
	if (!saveDateToBinaryFile(&pAnimal->birth, fp))
		return 0;
	if (!saveCategoryToBinaryFile(pAnimal->pCategory, fp))
		return 0;
	if (!saveCertificateToBinaryFile(&pAnimal->cer, fp))
		return 0;
	if (!writeIntToFile(pAnimal->reviewCount, fp, "Error writing number of reviews to binary file\n"))
		return 0;
	if (!saveReviewArrToBinaryFile(pAnimal, fp, "Error writing reviews to binary file\n"))
		return 0;
	return 1;
}

int	loadAnimalFromBinaryFile(Animal* pAnimal, FILE* fp)
{
	pAnimal->name = readStringFromFile(fp, "Error reading name from binary file\n");
	if (!readIntFromFile(&pAnimal->type, fp, "Error reading gender type from binary file\n"))
		return 0;
	if (!readFloatFromFile(&pAnimal->price, fp, "Error reading price from binary file\n"))
		return 0;
	if (!loadDateFromBinaryFile(&pAnimal->birth, fp))
		return 0;
	if (!createCategory(pAnimal))
		return 0;
	if (!loadCategoryFromBinaryFile(pAnimal->pCategory, fp))
		return 0;
	if (!createCertificate(pAnimal))
		return 0;
	if (!loadCertificateFromBinaryFile(&pAnimal->cer, fp))
		return 0;
	if (!readIntFromFile(&pAnimal->reviewCount, fp, "Error reading number of reviews from binary file\n"))
		return 0;
	if (!createReviewArr(pAnimal))
		return 0;
	if (!loadReviewArrFromBinaryFile(pAnimal, fp, "Error reading reviews from binary file\n"))
		return 0;
	return 1;
}

int createCategory(Animal* pAnimal)
{
	pAnimal->pCategory = (Category*)calloc(1, sizeof(Category));
	if (!pAnimal->pCategory) {
		printf("Error allocating memory for category\n");
		freeCategory(pAnimal->pCategory);
		free(pAnimal->pCategory);
		return 0;
	}
	return 1;
}

int createCertificate(Animal* pAnimal)
{
	Certificate* pCer = (Certificate*)calloc(1, sizeof(Certificate));
	if (!pCer) {
		printf("Error allocating memory for certificate\n");
		freeCertificate(pCer);
		free(pCer);
		return 0;
	}
	return 1;
}

int	createReviewArr(Animal* pAnimal)
{
	pAnimal->reviewArr = (Review*)malloc(pAnimal->reviewCount * sizeof(Review));
	if (!pAnimal->reviewArr)
	{
		printf("Alocation error for reviews\n");
		freeReviewArr(pAnimal->reviewArr, pAnimal->reviewCount);
		return 0;
	}
	return 1;
}

int	saveReviewArrToTextFile(const Animal* pAnimal, FILE* fp, const char* msg)
{
	if (!generalSaveLoadArrFile(pAnimal->reviewArr, pAnimal->reviewCount, sizeof(Review), fp, saveReviewToTextFile))
	{
		puts(msg);
		return 0;
	}
	return 1;

}

int	loadReviewArrFromTextFile(Animal* pAnimal, FILE* fp, const char* msg)
{
	if (!generalSaveLoadArrFile(pAnimal->reviewArr, pAnimal->reviewCount, sizeof(Review), fp, loadReviewFromTextFile))
	{
		puts(msg);
		return 0;
	}
	return 1;
}

int	saveReviewArrToBinaryFile(const Animal* pAnimal, FILE* fp, const char* msg)
{
	if (!generalSaveLoadArrFile(pAnimal->reviewArr, pAnimal->reviewCount, sizeof(Review), fp, saveReviewToBinaryFile))
	{
		puts(msg);
		return 0;
	}
	return 1;
}

int	loadReviewArrFromBinaryFile(Animal* pAnimal, FILE* fp, const char* msg)
{
	if (!generalSaveLoadArrFile(pAnimal->reviewArr, pAnimal->reviewCount, sizeof(Review), fp, loadReviewFromBinaryFile))
	{
		puts(msg);
		return 0;
	}
	return 1;
}

void printAnimal(const  void* val)
{
	const Animal* pAnimal = *(const Animal**)val;
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
	generalArrayFunction(arr, size, sizeof(Review), printReview);
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
	generalArrayFunction(arr, size, sizeof(Review), freeReview);
}