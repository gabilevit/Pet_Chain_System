#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "StoreManager.h"

int initManager(StoreManager* pManager)
{
	strcpy(pManager->chainName, "Gabi & Bens PetShop chain");

	if (!L_init(&pManager->storeList))
		return 0;
	return 1;
}

int addStore(StoreManager* pManager)
{
	int storeNumber = generateStoreNumber(pManager);
	Store* pStore = (Store*)calloc(1, sizeof(Store));
	if (!pStore)
		return 0;
	if (!initStore(pStore, storeNumber))
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
				printf("error in inserting\n");
				return 0;
			}
			return 1;
		}
		pPrevNode = pN;
		pN = pN->next;
	}
	if (!L_insert(pPrevNode, pStore)) {
		printf("error in inserting\n");
		return 0;
	}
	return 1;
}

int generateStoreNumber(StoreManager* pManager)
{
	if (getStoreCount(pManager) == 0) {
		return 1;
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

Store* findStore(StoreManager* pManager, const int storeNumber)
{
	if (pManager != NULL && storeNumber != NULL) {
		NODE* current = pManager->storeList.head.next; //first Node
		while (current != NULL) {
			Store* store = (Store*)current->key;
			if (store->storeNumber == storeNumber)
				return store;
			current = current->next;
		}
	}
	return NULL; // Store not found
}

Store* enterTheStore(StoreManager* pManager)
{
	int count = getStoreCount(pManager);
	printf("There are %d stores\n", count);
	NODE* current = pManager->storeList.head.next; //first Node
	while (current != NULL) {
		Store* storeShow = (Store*)current->key;
		printStoreInShort(storeShow);
		current = current->next;
	}
	int storeNum;
	printf("Enter the store number: ");
	scanf("%d", &storeNum);
	Store* store = findStore(pManager, storeNum);
	if (!store)
		printf("Store not found\n");
	return store;
}

void printStores(const StoreManager* pManager)
{
	int count = getStoreCount(pManager);
	printf("There are %d stores\n", count);
	L_print(&pManager->storeList, printStore);
}

void	freeManager(StoreManager* pManager)
{
	L_free(&pManager->storeList, freeStore);
}