#ifndef __STORE_MANAGER__
#define __STORE_MANAGER__

#define NAME 19

#include "list.h"
#include "Store.h"
#include "FileHelper.h"

typedef struct
{
	char chainName[NAME];
	LIST storeList;
}StoreManager;

int initManager(StoreManager* pManager);
int addStore(StoreManager* pManager);
int generateStoreNumber(StoreManager* pManager);
int	getStoreCount(const StoreManager* pManager);
Store* findStore(StoreManager* manager, const int storeNumber);
Store* enterTheStore(StoreManager* pManager);

// FILE FUNCTIONS
int	saveManagerToTextFile(const StoreManager* pManager, const char* fileName);
int	loadManagerFromTextFile(StoreManager* pManager, const char* fileName);
int	saveManagerToBinaryFile(const StoreManager* pManager, const char* fileName);
int	loadManagerFromBinaryFile(StoreManager* pManager, const char* fileName);

// PRINT FUNCTION
void printStores(const StoreManager* pManager);

// FREE FUNCTION
void freeManager(StoreManager* pManager);

#endif // !__STORE_MANAGER__