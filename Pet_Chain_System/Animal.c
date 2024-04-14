#include "Animal.h"
#include "General.h"

void initAnimal(Animal* pAnimal)
{
	pAnimal->name = getStrExactName("Enter pet name");
	if (!pAnimal->name)
		return 0;
	getPrice(pAnimal);
	getCorrectDate(&pAnimal->birth);
	pAnimal.
}

getPrice(Animal* pAnimal)
{
	printf("\nEnter the cost of the pet: ");
	float price;
	do {
		scanf("%f", &price);
		if (price <= 10) {
			printf("Minimum price must be greater or equal than 10.0, try again.\n");
		}
	} while (price <= 10);
	pAnimal->price = price;
}