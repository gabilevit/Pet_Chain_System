#include <string.h>

#include "Store.h"
#include "General.h"

int initStore(Store* pStore, int storeNumber)
{
	pStore->storeNumber = storeNumber;
	pStore->animalArr = NULL;
	pStore->animalCount = 0;
}

int addAnimal(Store* pStore)
{
	Animal* pAnimal = (Animal*)calloc(1, sizeof(Animal));
	if (!pAnimal)
		return 0;

	initAnimal(pAnimal);
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

void printStore(const Store* pStore)
{
	printf("Store number: %d\n", pStore->storeNumber);
	printf("\n -------- Has %d Animals\n", pStore->animalCount);
	printAnimalsArr(pStore->animalArr, pStore->animalCount);
}

void printAnimalsArr(Animal** arr, int size)
{
	generalArrayFunction(arr, size, sizeof(Animal*), printAnimalPtr);
}

void freeStore(Store* pStore)
{
	freeAnimalsArr(pStore->animalArr, pStore->animalCount);
	free(pStore->animalArr);
}

void freeAnimalsArr(Animal** arr, int size)
{
	generalArrayFunction(arr, size, sizeof(Animal*), freeAnimalPtr);
}