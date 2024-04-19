#ifndef __STORE__
#define __STORE__

#include "Animal.h"
#include "General.h"
#include "FileHelper.h"

typedef enum { eNone, eName, ePrice, eBirth, eNofSortOpt } eSortOption;
static const char* sortOptStr[eNofSortOpt] = { "Not Sorted", "Name", "Price", "Birth date" };;

typedef struct
{
	int storeNumber;
	char* city;
	int animalCount;
	Animal** animalArr;
	eSortOption	animalSortOpt;
}Store;

int initStore(Store* pStore, int storeNumber);
int addAnimal(Store* pStore, Category* pCategory);
Animal* findAnimal(Store* pStore, const char* animalName);
Animal* getAnimal(Store* pStore);
Certificate* findCertificateByAnimalId(Store* pStore, int id);

// SORT FIND FUNCTIONS
void sortAnimals(Store* pStore);
void findAnimalWithBsearch(const Store* pStore);
eSortOption showSortMenu();

// FILE FUNCTIONS
int	saveStoreToTextFile(const Store* pStore, FILE* fp);
int	loadStoreFromTextFile(Store* pStore, FILE* fp);
int	saveStoreToBinaryFile(const Store* pStore, FILE* fp);
int	loadStoreFromBinaryFile(Store* pStore, FILE* fp);
int	createAnimalArr(Store* pStore);
int	saveAnimalArrToTextFile(const Store* pStore, FILE* fp, const char* msg);
int	loadAnimalArrFromTextFile(Store* pStore, FILE* fp, const char* msg);
int	saveAnimalArrToBinaryFile(const Store* pStore, FILE* fp, const char* msg);
int	loadAnimalArrFromBinaryFile(Store* pStore, FILE* fp, const char* msg);

// PRINT FUNCTIONS
void printStore(const  void* val);
void printStoreInShort(const void* val);
void printAnimalsArr(Animal** arr, int size);

// FREE FUNCTIONS
void freeStore(void* val);
void freeAnimalsArr(Animal** arr, int size);

#endif // !__STORE__