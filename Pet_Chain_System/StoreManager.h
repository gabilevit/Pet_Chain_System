#ifndef __STORE_MANAGER__
#define __STORE_MANAGER__

#define NAME 19

#include "list.h"
#include "Store.h"

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
void printStores(const StoreManager* pManager);
void freeManager(StoreManager* pManager);


// NOT IMPLEMENTED
int		saveManagerToFile(const StoreManager* pManager, const char* fileName);
int		loadManagerFromFile(StoreManager* pManager, const char* fileName);

#endif // !__STORE_MANAGER__