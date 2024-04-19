#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main()
{
	StoreManager	manager;
	Store* theStore;
	Category* dogCategory = (Category*)calloc(1, sizeof(Category));
	Category* catCategory = (Category*)calloc(1, sizeof(Category));
	Category* birdCategory = (Category*)calloc(1, sizeof(Category));
	init3CategoriesHardCoded(dogCategory, catCategory, birdCategory);
	initManager(&manager);
	loadSystem(&manager);
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

		case ePrintStores:
			printStores(&manager);
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
	//if (pStore == NULL) return;
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

		case eAddDiscount:
			chosenCategory = getSpecificCategory(getCategoryType(), cat1, cat2, cat3);
			if (!addDiscountOrUpdateDiscount(chosenCategory))
				printf("Error adding a discount\n");
			break;

		case eSortAnimals:
			sortAnimals(pStore);
			break;

		case eFindAnimal:
			findAnimalWithBsearch(pStore);
			break;

		/*case eFindPopularAnimal:
			findMostPopular();
			break;

		case eFindExpensiveAnimal:
			findMostExpensive();
			break;*/

		case RETURN:
			choice = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!choice);
}

int menu()
{
	int option;
	printf("\n\n");
	for (int i = 0; i < eNofOptionsInMain; i++)
		printf("%d - %s\n", i, str2[i]);
	printf("%d - Quit\n", EXIT);
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

void init3CategoriesHardCoded(Category* cat1, Category* cat2, Category* cat3)
{
	initCategory(cat1, 0);
	initCategory(cat2, 1);
	initCategory(cat3, 2);
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