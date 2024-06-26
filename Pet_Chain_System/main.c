#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "main.h"

int main()
{
	StoreManager manager;
	Store* theStore;
	Category* dogCategory = (Category*)calloc(1, sizeof(Category));
	Category* catCategory = (Category*)calloc(1, sizeof(Category));
	Category* birdCategory = (Category*)calloc(1, sizeof(Category));
	Category* chosenCategory;
	loadSystem(&manager);
	initCategoriesFromData(&manager, dogCategory, catCategory, birdCategory);
	int option;
	int stop = 0;

	do
	{
		printf("Welcome to %s!", manager.chainName);
		option = menu();
		switch (option)
		{
		case eAddStore:
			if (!addStore(&manager))
				printf("Error adding store\n");
			break;

		case eEnterStore:
			theStore = enterTheStore(&manager);
			if (!theStore)
				break;
			storeLobby(theStore, dogCategory, catCategory, birdCategory);
			break;

		case eAddDiscount:
			chosenCategory = getSpecificCategory(getCategoryType(), dogCategory, catCategory, birdCategory);
			if (addDiscountOrUpdateDiscount(chosenCategory))
			{
				addDiscountToAllAnimalsToSpesificCategory(&manager, chosenCategory);
			}
			else 	printf("Error adding a discount\n");
			break;

		case ePrintStores:
			printStores(&manager);
			break;

		case eFindPopularAnimal:
			findMostPopularAnimalInTheWholeChain(&manager);
			break;

		case eFindMostAnimals:
			findStoreWithMostAnimals(&manager);
			break;

		case EXIT:
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);

	saveManagerToTextFile(&manager, MANAGER_TEXT_FILE);
	saveManagerToBinaryFile(&manager, MANAGER_BINARY_FILE);
	freeManager(&manager);
	return 1;
}

void storeLobby(Store* pStore, Category* cat1, Category* cat2, Category* cat3) {
	Category* chosenCategory;
	Animal* chosenAnimal;
	int choice = 0;
	do {
		printf("Welcome to store number %d!", pStore->storeNumber);
		choice = storeMenu();
		switch (choice)
		{
		case eAddAnimal:
			chosenCategory = getSpecificCategory(getCategoryType(), cat1, cat2, cat3);
			if (!addAnimal(pStore, chosenCategory))
				printf("Error adding animal\n");
			break;

		case eAddReview:
			chosenAnimal = getAnimal(pStore);
			if (!chosenAnimal)
				break;
			if (!addReview(chosenAnimal))
				printf("Error adding a review\n");
			break;

		case ePrintAnimals:
			printStore(pStore);
			break;

		case eSortAnimals:
			sortAnimals(pStore);
			break;

		case eFindAnimal:
			findAnimalWithBsearch(pStore);
			break;

		case RETURN:
			choice = -2;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (choice != -2);
}

int menu()
{
	int option;
	printf("\n\n");
	for (int i = 0; i < eNofOptionsInMain; i++)
		printf("%d - %s\n", i, str2[i]);
	printf("%d - Quit and save data\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}

void loadSystem(StoreManager* pManager)
{
	int option;
	printf("From which file type you want to upload the system?\n");
	printf("\n\n");
	for (int i = 0; i < eNofOptionsInFileType; i++)
		printf("%d - %s\n", i, str1[i]);
	printf("%d - Return to main menu\n", RETURN);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	switch (option)
	{
	case eUploadFromText:
		initManagerFromTextFile(pManager, MANAGER_TEXT_FILE);
		break;

	case eUploadFromBinary:
		initManagerFromBinaryFile(pManager, MANAGER_BINARY_FILE);
		break;
	}
}

int storeMenu()
{
	int option;
	printf("\n\n");
	for (int i = 0; i < eNoOptionsInStoreMenu; i++)
		printf("%d - %s\n", i, str3[i]);
	printf("%d - Return to main menu\n", RETURN);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}

void initCategoriesFromData(StoreManager* manager, Category* dogCategory, Category* catCategory, Category* birdCategory)
{
	if (!updateCategoriesFromData(manager, dogCategory, catCategory, birdCategory))
		puts("There are no stores in the system\n");
}

Category* getSpecificCategory(eCategoryType eType, Category* dog, Category* cat, Category* bird)
{
	if (dog->type == eType)
		return dog;
	else if (cat->type == eType)
		return cat;
	else 
		return bird;
}