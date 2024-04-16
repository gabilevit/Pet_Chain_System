#ifndef __STORE__
#define __STORE__

#include "Animal.h"

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
void printStore(const  void* val);
void printStoreInShort(const void* val);
void printAnimalsArr(Animal** arr, int size);
void freeStore(void* val);
void freeAnimalsArr(Animal** arr, int size);

// NOT IMPLEMENTED
int		saveAnimalToFile(const Animal* pAir, FILE* fp);
int		loadAnimalFromFile(Animal* pAir, FILE* fp);

#endif // !__STORE__