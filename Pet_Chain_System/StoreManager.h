#ifndef __STORE_MANAGER__
#define __STORE_MANAGER__

#define NAME 19

#include "list.h"
#include "Store.h"
#include "FileHelper.h"
#include "macros.h"

typedef struct
{
	char chainName[MAX_STR_LEN];
	LIST storeList;
}StoreManager;

int initManager(StoreManager* pManager);
int addStore(StoreManager* pManager);
int	insertNewStoreToList(LIST* pStoreList, Store* pStore);
int generateStoreNumber(StoreManager* pManager);
int	getStoreCount(const StoreManager* pManager);
Store* findStore(StoreManager* manager, const int storeNumber);
Store* enterTheStore(StoreManager* pManager);
void addDiscountToAllAnimalsToSpesificCategory(StoreManager* pManager, Category* pChosenCategory);
void isSameCategoryType(Animal* pAnimal, Category* pCategory);
int updateCategoriesFromData(StoreManager* pManager, Category* pCat1, Category* pCat2, Category* pCat3);

// 2 CREATIVE FUNCTIONS
void findMostPopularAnimalInTheWholeChain(StoreManager* pManager);
void findStoreWithMostAnimals(StoreManager* pMannager);

// FILE FUNCTIONS
void initManagerFromTextFile(StoreManager* storeManager, const char* fileName);
void initManagerFromBinaryFile(StoreManager* storeManager, const char* fileName);
int	saveManagerToTextFile(const StoreManager* pManager, const char* fileName);
int	loadManagerFromTextFile(StoreManager* pManager, const char* fileName);
int	saveManagerToBinaryFile(const StoreManager* pManager, const char* fileName);
int loadStoreListFromBinaryFile(StoreManager* pManager, FILE* fp);
int	loadManagerFromBinaryFile(StoreManager* pManager, const char* fileName);

// PRINT FUNCTION
void printStores(const StoreManager* pManager);

// FREE FUNCTION
void freeManager(StoreManager* pManager);

#endif // !__STORE_MANAGER__