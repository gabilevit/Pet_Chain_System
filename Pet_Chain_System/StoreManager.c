#include <string.h>

#include "StoreManager.h"

int initManager(StoreManager* pManager)
{
	strcpy(pManager->chainName, "Gabi & Bens PetShop");

	if (!L_init(&pManager->storeList))
		return 0;
	return 1;
}

int addStore(StoreManager* pManager, Store* pStore)
{
	int storeNumber = generateStoreNumber(pManager);
	Store* pStore = (Store*)calloc(1, sizeof(Store));
	if (!pStore)
		return 0;

	if (!initStore(pStore, storeNumber));
	{
		freeStore(pStore); //will free also pStore
		return 0;
	}

	NODE* pN = pManager->storeList.head.next; //first Node
	NODE* pPrevNode = &pManager->storeList.head;
	Store* pTemp;
	while (pN != NULL)
	{
		pTemp = (Store*)pN->key;
		if ((pTemp->storeNumber > pStore->storeNumber))
		{
			if (!L_insert(pPrevNode, pStore)) {
				printf("error in inserting the store to the list\n");
				return 0;
			}
			return 1;
		}
		pPrevNode = pN;
		pN = pN->next;
	}
	if (!L_insert(pPrevNode, pStore)) {
		printf("error in inserting the invoice to the list\n");
		return 0;
	}
	return 1;
}

int generateStoreNumber(StoreManager* pManager)
{
	if (getStorecount(pManager) == 0) {
		return 0;
	}
	int id = 0;
	NODE* pN = pManager->storeList.head.next; //first Node
	Store* pTemp;
	while (pN != NULL)
	{
		pTemp = (Store*)pN->key;
		if (pTemp->storeNumber > id) {
			id = pTemp->storeNumber;
		}
		pN = pN->next;
	}
	return id + 1;
}

int	getStoreCount(const StoreManager* pManager)
{
	int count = 0;
	NODE* pN = pManager->storeList.head.next; //first Node

	while (pN != NULL)
	{
		count++;
		pN = pN->next;
	}
	return count;
}

void printStores(const StoreManager* pManager)
{
	int count = getStoreCount(pManager);
	printf("there are %d stores\n", count);
	L_print(&pManager->storeList, printStoreV);
}

void	freeManager(StoreManager* pManager)
{
	L_free(&pManager->storeList, freeStoreV);
}