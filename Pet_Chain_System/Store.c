#include <string.h>
#include <stdlib.h> // For rand, srand
#include <time.h>   // For time
#include <stdio.h>
#include "Store.h"

int initStore(Store* pStore, int storeNumber)
{
	pStore->storeNumber = storeNumber;
	pStore->city = getStrExactName("Enter store city");
	if (!pStore->city)
		return 0;
	pStore->animalArr = NULL;
	pStore->animalCount = 0;
	return 1;
}

int addAnimal(Store* pStore, Category* pCategory)
{
	Animal* pAnimal = (Animal*)calloc(1, sizeof(Animal));
	if (!pAnimal)
		return 0;
	Certificate* pCertificate = (Certificate*)calloc(1, sizeof(Certificate));
	if (!pCertificate)
		return 0;
	int certificateAnimalId = generateCertificateId(pStore);
	if (!initCertificate(pCertificate, certificateAnimalId))
	{
		freeCertificate(pCertificate); //will free also pStore
		return 0;
	}
	initAnimal(pAnimal, pCategory, pCertificate);
	pStore->animalArr = (Animal**)realloc(pStore->animalArr, (pStore->animalCount + 1) * sizeof(Animal*));
	if (!pStore->animalArr)
	{
		free(pAnimal);
		return 0;
	}
	pStore->animalArr[pStore->animalCount] = pAnimal;
	pStore->animalCount++;
	return 1;
}

int generateCertificateId(Store* pStore)
{
	int certificateId;
	do
	{
		// Seed the random number generator with the current time
		srand((unsigned int)time(NULL));
		// Generate a random number between MIN_CERTIFICATE_ID and MAX_CERTIFICATE_ID
		certificateId = (rand() % (MAX_CERTIFICATE_ID - MIN_CERTIFICATE_ID + 1)) + MIN_CERTIFICATE_ID;
	} while (!isCertificateIdUnique(pStore, certificateId));
	return certificateId;
}

int isCertificateIdUnique(Store* pStore, int num)
{
	for (int i = 0; i < pStore->animalCount; i++)
	{
		if (pStore->animalArr[i]->cer.animalCertificateId == num)
			return 0;
	}
	return 1;
}

Animal* findAnimal(Store* pStore, const char* animalName)
{
	if (pStore != NULL && animalName != NULL) {
		int i;
		// Iterate through the animals array to find the animal with the given name
		for (i = 0; i < pStore->animalCount; i++) {
			if (strcmp(pStore->animalArr[i]->name, animalName) == 0) {
				return pStore->animalArr[i];
			}
		}
	}
	return NULL; // Animal not found
}

Animal* getAnimal(Store* pStore)
{
	printAnimalsArr(pStore->animalArr, pStore->animalCount);
	char* name = getStrExactName("Choose animal by the animals name:\n");
	Animal* animal = findAnimal(pStore, name);
	if (!animal)
		printf("Animal not found\n");
	return animal;
}

Certificate* findCertificateByAnimalId(Store* pStore, int id)
{
	if (pStore != NULL)
	{
		for (int i = 0; i < pStore->animalCount; i++)
			if (pStore->animalArr[i]->cer.animalCertificateId == id)
				return &pStore->animalArr[i]->cer;
	}
	return NULL;
}

void printStore(const  void* val)
{
	const Store* pStore = (const Store*)val;
	printf("Store number: %d\n", pStore->storeNumber);
	printf("City: %s\n", pStore->city);
	printf("\n -------- Has %d Animals\n", pStore->animalCount);
	printAnimalsArr(pStore->animalArr, pStore->animalCount);
}

void printStoreInShort(const void* val)
{
	const Store* pStore = (const Store*)val;
	printf("Store number: %d\n", pStore->storeNumber);
	printf("City: %s\n", pStore->city);
}

void printAnimalsArr(Animal** arr, int size)
{
	generalArrayFunction(arr, size, sizeof(Animal*), printAnimal);
}

void freeStore(void* val)
{
	const Store* pStore = (const Store*)val;
	free(pStore->city);
	freeAnimalsArr(pStore->animalArr, pStore->animalCount);
	free(pStore->animalArr);
}

void freeAnimalsArr(Animal** arr, int size)
{
	generalArrayFunction(arr, size, sizeof(Animal*), freeAnimal);
}