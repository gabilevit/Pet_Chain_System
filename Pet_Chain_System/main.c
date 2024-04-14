#include <stdio.h>
#include <stdlib.h>
#include "StoreManager.h"
#include "General.h"

typedef enum
{
	eAddStore, eAddAnimal, eAddReview, eAddDiscount, ePrintStores,
	ePrintAnimalsCategoryType, eSortAnimals, eFindAnimal,
	eFindPopularAnimal, eFindExpensiveAnimal, eNofOptions
} eMenuOptions;

const char* str[eNofOptions] = { "Add Stroe","Add Animal","Add a review",
								"Add a discount", "Print all stores",
								"Print all animals with category type",
								"Sort Animals", "Find Animal", "Find most popular animal",
								"Find most expensive animal in store" };

#define EXIT			-1
int menu();

int main()
{
	AirportManager	manager;
	Airline			company;

	initManager(&manager);
	initAirline(&company);

	int option;
	int stop = 0;


	do
	{
		option = menu();
		switch (option)
		{
		case eAddStore:
			if (!addPlane(&company))
				printf("Error adding plane\n");
			break;

		case eAddAnimal:
			if (!addAirport(&manager))
				printf("Error adding airport\n");
			break;

		case eAddReview:
			if (!addFlight(&company, &manager))
				printf("Error adding flight\n");
			break;

		case eAddDiscount:
			printCompany(&company);
			break;

		case ePrintStores:
			printAirports(&manager);
			break;

		case ePrintAnimalsCategoryType:
			doPrintFlightsWithPlaneType(&company);
			break;

		case eSortAnimals:
			sortFlight(&company);
			break;

		case eFindAnimal:
			findFlight(&company);
			break;
		case eFindPopularAnimal:
			findMostPopular();
			break;
		case eFindExpensiveAnimal:
			findMostExpensive();
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

	freeManager(&manager);
	freeCompany(&company);

	return 1;
}

int menu()
{
	int option;
	printf("\n\n");
	printf("Welcome to our pet shop system\n");
	for (int i = 0; i < eNofOptions; i++)
		printf("%d - %s\n", i, str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}