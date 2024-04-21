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
			PRINT_RETURN_NUM(L_insert(pPrevNode, pStore), 0, "error in inserting\n");
			return 1;
		}
		pPrevNode = pN;
		pN = pN->next;
	}
	PRINT_RETURN_NUM(L_insert(pPrevNode, pStore), 0, "error in inserting\n");
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
	if (pManager != NULL && storeNumber != 0) {
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

void addDiscountToAllAnimalsToSpesificCategory(StoreManager* pManager, Category* pChosenCategory)
{
	if (pManager != NULL && pChosenCategory != NULL)
	{
		NODE* current = pManager->storeList.head.next; //first Node
		while (current != NULL) {
			Store* pStore = (Store*)current->key;
			for (int i = 0; i < pStore->animalCount; i++)
			{
				Animal* pAnimal = pStore->animalArr[i];
				int type1 = (int)pAnimal->pCategory->type;
				int type2 = (int)pChosenCategory->type;
				isSameCategoryType(pAnimal, pChosenCategory);
			}
			current = current->next;
		}
	}
}

void isSameCategoryType(Animal* pAnimal, Category* pCategory)
{
	if (pAnimal->pCategory->type == pCategory->type)
		*(pAnimal->pCategory->pDiscount) = *pCategory->pDiscount;
}

int updateCategoriesFromData(StoreManager* pManager, Category* pCat1, Category* pCat2, Category* pCat3)
{
	NODE* current = pManager->storeList.head.next; //first Node
	if (!current) // there are no stores in the chain so there is nothing
		return 0;
	while (current != NULL) {
		Store* pStore = (Store*)current->key;
		for (int i = 0; i < pStore->animalCount; i++)
		{
			Animal* pAnimal = pStore->animalArr[i];
			if ((pAnimal->pCategory->pDiscount) && pAnimal->pCategory->type == 0)
				*(pCat1) = *(pAnimal->pCategory);
			else if ((pAnimal->pCategory->pDiscount) && pAnimal->pCategory->type == 1)
				*(pCat2) = *(pAnimal->pCategory);
			else if ((pAnimal->pCategory->pDiscount) && pAnimal->pCategory->type == 2)
				*(pCat3) = *(pAnimal->pCategory);
		}
		current = current->next;
	}
	if (!pCat1->pDiscount)
		initCategory(pCat1, 0);
	if (!pCat2->pDiscount)
		initCategory(pCat2, 1);
	if (!pCat3->pDiscount)
		initCategory(pCat3, 2);
	return 1;
}

void findMostPopularAnimalInTheWholeChain(StoreManager* pManager)
{
	int maxReviews = 0;
	Animal* popularAnimal = NULL;
	Store* chosenStore = NULL;
	NODE* current = pManager->storeList.head.next; //first Node
	while (current != NULL) {
		Store* pStore = (Store*)current->key;
		for (int i = 0; i < pStore->animalCount; i++)
		{
			Animal* pAnimal = pStore->animalArr[i];
			if (pAnimal->reviewCount > maxReviews) 
			{
				popularAnimal = pAnimal;
				maxReviews = pAnimal->reviewCount;
				chosenStore = pStore;
			}
		}
		current = current->next;
	}
	if (!popularAnimal)
	{
		puts("There are no animals in the chain\n");
		return;
	}
	printf("The most popular animal in the store is: %s from store number: %d\n", popularAnimal->name, chosenStore->storeNumber);
	printf("The number of reviews that this animal have is: %d\n", popularAnimal->reviewCount);
	puts("I RECOMMEND OFF BUYING THIS ONE:)");	
}

void findStoreWithMostAnimals(StoreManager* pMannager)
{
	int maxAnimals = 0;
	Store* theStore = NULL;
	NODE* current = pMannager->storeList.head.next; //first Node
	while (current != NULL) {
		Store* pStore = (Store*)current->key;
		for (int i = 0; i < pStore->animalCount; i++)
		{
			if (pStore->animalCount > maxAnimals)
			{
				theStore = pStore;
				maxAnimals = pStore->animalCount;
			}
		}
		current = current->next;
	}
	if (!theStore)
	{
		puts("There are no stores in the chain\n");
		return;
	}
	printf("The store with the most animals inside is store number: %d  from the city of %s\n", theStore->storeNumber, theStore->city);
	printf("The number of animals that this store has is: %d\n", theStore->animalCount);
	puts("THIS STORE HAS THE MOST OPTIONS TO PICK I RECOMMEND ON ENTERING THIS STORE");
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
	PRINT_RETURN_NUM(fp, 0, "Error open store manager file to write\n");
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
				puts("Error write store to text file\n");
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
	PRINT_RETURN_NUM(fp, 0, "Error open store manager file to read\n");
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
	PRINT_RETURN_NUM(fp, 0, "Error open store manager file to write\n");
	int count = getStoreCount(pManager);
	WRITE_INT_BINARY_FILE_PRINT_RETURN(count, fp, "Error writing number of stores to file\n", 0);
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
	PRINT_RETURN_NUM(fp, 0, "Error open store manager file to read\n");
	L_init(&pManager->storeList);
	if (!loadStoreListFromBinaryFile(pManager, fp))
		return 0;
	return 1;
}

void printStores(const StoreManager* pManager)
{
	int count = getStoreCount(pManager);
	printf("&&&&&&&& There are %d stores &&&&&&&&\n", count);
	L_print(&pManager->storeList, printStore);
}

void	freeManager(StoreManager* pManager)
{
	L_free(&pManager->storeList, freeStore);
}