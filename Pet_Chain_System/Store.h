#ifndef __STORE__
#define __STORE__

#include "Animal.h"

typedef struct
{
	int storeNumber;
	int animalCount;
	Animal** animalArr;
}Store;

int initStore(Store* pStore, int storeNumber);
int addAnimal(Store* pStore);
void printStore(const Store* pStore);
void printAnimalsArr(Animal** arr, int size);
void freeStore(Store* pStore);
void freeAnimalsArr(Animal** arr, int size);

#endif // !__STORE__