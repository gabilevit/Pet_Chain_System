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
int addStore(StoreManager* pManager, Store* pStore);
int generateStoreNumber(StoreManager* pManager);
int	getStoreCount(const StoreManager* pManager);
void printStores(const StoreManager* pManager);
void freeManager(StoreManager* pManager);

#endif // !__STORE_MANAGER__