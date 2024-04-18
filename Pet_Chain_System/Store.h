#ifndef __STORE__
#define __STORE__

#include "Animal.h"
#include "General.h"
#include "FileHelper.h"

typedef struct
{
	int storeNumber;
	char* city;
	int animalCount;
	Animal** animalArr;
}Store;

int initStore(Store* pStore, int storeNumber);
int addAnimal(Store* pStore, Category* pCategory);
Animal* findAnimal(Store* pStore, const char* animalName);
Animal* getAnimal(Store* pStore);
Certificate* findCertificateByAnimalId(Store* pStore, int id);


// FILE FUNCTIONS
int	saveStoreToTextFile(const Store* pStore, FILE* fp);
int	loadStoreFromTextFile(Store* pStore, FILE* fp);
int	saveStoreToBinaryFile(const Store* pStore, FILE* fp);
int	loadStoreFromBinaryFile(Store* pStore, FILE* fp);
int	createAnimalArr(Store* pStore);
int	loadAnimalArrFromTextFile(Store* pStore, FILE* fp);
int	loadAnimalArrFromBinaryFile(Store* pStore, FILE* fp);

// PRINT FUNCTIONS
void printStore(const  void* val);
void printStoreInShort(const void* val);
void printAnimalsArr(Animal** arr, int size);

// FREE FUNCTIONS
void freeStore(void* val);
void freeAnimalsArr(Animal** arr, int size);

#endif // !__STORE__