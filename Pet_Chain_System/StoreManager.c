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

int		insertNewStoreToList(LIST* pStoreList, Store* pStore)
{
	NODE* pN = pStoreList->head.next; //first Node
	NODE* pPrevNode = &pStoreList->head;
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
	return insertNewStoreToList(&pManager->storeList, pStore);
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

void initManagerFromTextFile(StoreManager* storeManager, const char* fileName) 
{
	if (!loadManagerFromTextFile(storeManager, fileName))
		initManager(storeManager);
}

void initManagerFromBinaryFile(StoreManager* storeManager, const char* fileName)
{
	if (!loadManagerFromBinaryFile(storeManager, fileName))
		initManager(storeManager);
}

int	saveManagerToTextFile(const StoreManager* pManager, const char* fileName)
{
	FILE* fp;

	fp = fopen(fileName, "w");
	if (!fp) {
		printf("Error open store manager file to write\n");
		return 0;
	}
	/*if (!writeStringToTextFile(pManager->chainName, fp, "Error writing chain name to text file\n"))
		return 0;*/
	int count = getStoreCount(pManager);
	fprintf(fp, "%d\n", count);
	if (count > 0)
	{
		NODE* pN = pManager->storeList.head.next; //first Node

		Store* pTemp;
		while (pN != NULL)
		{
			pTemp = (Store*)pN->key;
			if (!saveStoreToTextFile(pTemp, fp))
			{
				printf("Error write store to text file\n");
				fclose(fp);
				return 0;
			}
			pN = pN->next;
		}

	}
	fclose(fp);
	return 1;
}

int	loadManagerFromTextFile(StoreManager* pManager, const char* fileName)
{
	strcpy(pManager->chainName, "Gabi & Bens PetShop chain");
	FILE* fp;

	fp = fopen(fileName, "r");
	if (!fp)
	{
		printf("Error open store manager file to read\n");
		return 0;
	}
	//myGets(pManager->chainName, NAME, fp);
	L_init(&pManager->storeList);
	int count;
	fscanf(fp, "%d", &count);
	//clean the buffer
	fgetc(fp);

	Store* pStore;
	for (int i = 0; i < count; i++)
	{
		pStore = (Store*)calloc(1, sizeof(Store));
		if (!pStore)
			break;
		if (!loadStoreFromTextFile(pStore, fp))
		{
			printf("Error loading sttore from text file\n");
			fclose(fp);
			return 0;
		}
		insertNewStoreToList(&pManager->storeList, pStore);
	}
	fclose(fp);
	return 1;
}

int	saveManagerToBinaryFile(const StoreManager* pManager, const char* fileName)
{
	FILE* fp;

	fp = fopen(fileName, "wb");
	if (!fp) {
		printf("Error open store manager file to write\n");
		return 0;
	}
	/*if (!writeStringToTextFile(pManager->chainName, fp, "Error writing chain name to binary file\n"))
		return 0;*/
	int count = getStoreCount(pManager);
	if (!writeIntToFile(count, fp, "Error writing number of stores to file\n"))
		return 0;
	//fprintf(fp, "%d\n", count);
	if (count > 0)
	{
		NODE* pN = pManager->storeList.head.next; //first Node

		Store* pTemp;
		while (pN != NULL)
		{
			pTemp = (Store*)pN->key;
			if (!saveStoreToBinaryFile(pTemp, fp))
			{
				printf("Error write store to text file\n");
				fclose(fp);
				return 0;
			}
			pN = pN->next;
		}

	}
	fclose(fp);
	return 1;
}

int loadStoreListFromBinaryFile(StoreManager* pManager, FILE* fp)
{
	int count;
	if (!readIntFromFile(&count, fp, "Error reading number of stores from binary file\n"))
		return 0;
	Store* pStore;
	for (int i = 0; i < count; i++) {
		pStore = (Store*)calloc(1, sizeof(Store));
		if (!pStore) {
			printf("Error allocating memory for store\n");
			freeStore(pStore);
			free(pStore);
			return 0;
		}
		if (!loadStoreFromBinaryFile(pStore, fp)) 
		{
			freeStore(pStore);
			free(pStore);
			return 0;
		}
		insertNewStoreToList(&pManager->storeList, pStore);
	}
	return 1;
}

int	loadManagerFromBinaryFile(StoreManager* pManager, const char* fileName)
{
	strcpy(pManager->chainName, "Gabi & Bens PetShop chain");
	FILE* fp;

	fp = fopen(fileName, "rb");
	if (!fp)
	{
		printf("Error open store manager file to read\n");
		return 0;
	}
	L_init(&pManager->storeList);
	//myGets(pManager->chainName, NAME, fp);
	if (!loadStoreListFromBinaryFile(pManager, fp))
		return 0;
	return 1;
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