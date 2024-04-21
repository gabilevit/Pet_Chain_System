#include <string.h>
#include <stdlib.h> // For rand, srand
#include <time.h>   // For time
#include <stdio.h>
#include "Store.h"

int initStore(Store* pStore, int storeNumber)
{
	pStore->storeNumber = storeNumber;
	pStore->city = getStrExactName("Enter store city");
	if (!pStore->city)
		return 0;
	pStore->animalArr = NULL;
	pStore->animalCount = 0;
	return 1;
}

int addAnimal(Store* pStore, Category* pCategory)
{
	Animal* pAnimal = (Animal*)calloc(1, sizeof(Animal));
	if (!pAnimal)
	{
		free(pAnimal);
		return 0;
	}
	Certificate* pCertificate = (Certificate*)calloc(1, sizeof(Certificate));
	if (!pCertificate)
	{
		free(pCertificate);
		return 0;
	}
	int certificateAnimalId = generateCertificateId(pStore);
	if (!initCertificate(pCertificate, certificateAnimalId))
	{
		freeCertificate(pCertificate); //will free also pStore
		return 0;
	}
	if (!initAnimal(pAnimal, pCategory, pCertificate))
		return 0;
	pStore->animalArr = (Animal**)realloc(pStore->animalArr, (pStore->animalCount + 1) * sizeof(Animal*));
	if (!pStore->animalArr)
	{
		free(pStore->animalArr);
		return 0;
	}
	pStore->animalArr[pStore->animalCount] = pAnimal;
	pStore->animalCount++;
	return 1;
}

int generateCertificateId(Store* pStore)
{
	int certificateId;
	do
	{
		// Seed the random number generator with the current time
		srand((unsigned int)time(NULL));
		// Generate a random number between MIN_CERTIFICATE_ID and MAX_CERTIFICATE_ID
		certificateId = (rand() % (MAX_CERTIFICATE_ID - MIN_CERTIFICATE_ID + 1)) + MIN_CERTIFICATE_ID;
	} while (!isCertificateIdUnique(pStore, certificateId));
	return certificateId;
}

int isCertificateIdUnique(Store* pStore, int num)
{
	for (int i = 0; i < pStore->animalCount; i++)
	{
		if (pStore->animalArr[i]->cer.animalCertificateId == num)
			return 0;
	}
	return 1;
}

Animal* findAnimal(Store* pStore, const char* animalName)
{
	if (pStore != NULL && animalName != NULL) {
		int i;
		// Iterate through the animals array to find the animal with the given name
		for (i = 0; i < pStore->animalCount; i++) {
			if (strcmp(pStore->animalArr[i]->name, animalName) == 0) {
				return pStore->animalArr[i];
			}
		}
	}
	return NULL; // Animal not found
}

Animal* getAnimal(Store* pStore)
{
	printAnimalsArr(pStore->animalArr, pStore->animalCount);
	char* name = getStrExactName("Choose animal by the animals name:\n");
	Animal* animal = findAnimal(pStore, name);
	if (!animal)
		printf("Animal not found\n");
	return animal;
}

Certificate* findCertificateByAnimalId(Store* pStore, int id)
{
	if (pStore != NULL)
	{
		for (int i = 0; i < pStore->animalCount; i++)
			if (pStore->animalArr[i]->cer.animalCertificateId == id)
				return &pStore->animalArr[i]->cer;
	}
	return NULL;
}

void sortAnimals(Store* pStore)
{
	pStore->animalSortOpt = showSortMenu();
	int(*compare)(const void* air1, const void* air2) = NULL;

	switch (pStore->animalSortOpt)
	{
	case eName:
		compare = compareAnimalByName;
		break;
	case ePrice:
		compare = compareAnimalByPrice;
		break;
	case eBirth:
		compare = compareAnimalByBirthDate;
		break;
	}

	if (compare != NULL)
		qsort(pStore->animalArr, pStore->animalCount, sizeof(Animal*), compare);
}

void findAnimalWithBsearch(const Store* pStore)
{
	int(*compare)(const void* air1, const void* air2) = NULL;
	Animal f = { 0 };
	Animal* pAnimal = &f;

	switch (pStore->animalSortOpt)
	{
	case eName:
		pAnimal->name = getStrExactName("Enter the name of the animal: ");
		compare = compareAnimalByName;
		break;

	case ePrice:
		printf("Enter animals price:\n");
		scanf("%f", &f.price);
		compare = compareAnimalByPrice;
		break;

	case eBirth:
		getCorrectDate(&f.birth);
		compare = compareAnimalByBirthDate;
		break;

	}

	if (compare != NULL)
	{
		Animal** pF = bsearch(&pAnimal, pStore->animalArr, pStore->animalCount, sizeof(Animal*), compare);
		if (pF == NULL)
			printf("Animal was not found\n");
		else {
			printf("ANIMAL HAS BEEN FOUND:\n");
			printAnimal(pF);
		}
	}
	else {
		printf("The search cannot be performed, array not sorted\n");
	}
}

eSortOption showSortMenu()
{
	int opt;
	printf("Base on what field do you want to sort?\n");
	do {
		for (int i = 1; i < eNofSortOpt; i++)
			printf("Enter %d for %s\n", i, sortOptStr[i]);
		scanf("%d", &opt);
	} while (opt < 0 || opt >= eNofSortOpt);

	return (eSortOption)opt;
}

int	saveStoreToTextFile(const Store* pStore, FILE* fp)
{
	WRITE_INT_TEXT_FILE_PRINT_RETURN(pStore->storeNumber, fp, "Error writing store number to text file\n", 0);
	WRITE_STRING_TEXT_FILE_PRINT_RETURN(pStore->city, fp, "Error writing city to text file\n", 0);
	WRITE_INT_TEXT_FILE_PRINT_RETURN(pStore->animalCount, fp, "Error writing number of animals to text file\n", 0);
	if (!saveAnimalArrToTextFile(pStore, fp, "Error writing animals to text file\n"))
		return 0;
	return 1;
}

int	loadStoreFromTextFile(Store* pStore, FILE* fp)
{
	if (!readIntFromTextFile(&pStore->storeNumber, fp, "Error reading store number from text file\n"))
		return 0;
	pStore->city = readDynStringFromTextFile(fp);
	if (!readIntFromTextFile(&pStore->animalCount, fp, "Error reading number of animals from text file\n"))
		return 0;
	if (!createAnimalArr(pStore))
		return 0;
	if (!loadAnimalArrFromTextFile(pStore, fp, "Error reading animals from text file\n"))
		return 0;
	return 1;
}

int	saveStoreToBinaryFile(const Store* pStore, FILE* fp)
{
	WRITE_INT_BINARY_FILE_PRINT_RETURN(pStore->storeNumber, fp, "Error writing store number to binary file\n", 0);
	WRITE_STRING_BINARY_FILE_PRINT_RETURN(pStore->city, fp, "Error writing city to binary file\n", 0);
	WRITE_INT_BINARY_FILE_PRINT_RETURN(pStore->animalCount, fp, "Error writing number of animals to binary file\n", 0);
	if (!saveAnimalArrToBinaryFile(pStore, fp, "Error writing animals to binary file\n"))
		return 0;
	return 1;
}

int	loadStoreFromBinaryFile(Store* pStore, FILE* fp)
{
	if (!readIntFromFile(&pStore->storeNumber, fp, "Error reading store number from binary file\n"))
		return 0;
	pStore->city = readStringFromFile(fp, "Error reading city from binary file\n");
	if (!readIntFromFile(&pStore->animalCount, fp, "Error reading number of animals from binary file\n"))
		return 0;
	if (!createAnimalArr(pStore))
		return 0;
	if(!loadAnimalArrFromBinaryFile(pStore, fp, "Error reading animals from binary file\n"))
		return 0;
	return 1;
}

int	createAnimalArr(Store* pStore)
{
	if (pStore->animalCount > 0)
	{
		pStore->animalArr = (Animal**)realloc(pStore->animalArr, (pStore->animalCount + 1) * sizeof(Animal*));
		if (!pStore->animalArr)
		{
			free(pStore->animalArr);
			return 0;
		}
	}
	else
		pStore->animalArr = NULL;

	for (int i = 0; i < pStore->animalCount; i++)
	{
		pStore->animalArr[i] = (Animal*)calloc(1, sizeof(Animal));
		PRINT_RETURN_NUM(pStore->animalArr[i], 0, "Alocation error for animal\n")
	}
	return 1;
}

int	saveAnimalArrToTextFile(const Store* pStore, FILE* fp, const char* msg)
{
	if (!generalSaveLoadArrFile(pStore->animalArr, pStore->animalCount, sizeof(Animal*), fp, saveAnimalToTextFile))
	{
		puts(msg);
		return 0;
	}
	return 1;
}

int	loadAnimalArrFromTextFile(Store* pStore, FILE* fp, const char* msg)
{
	if (!generalSaveLoadArrFile(pStore->animalArr, pStore->animalCount, sizeof(Animal*), fp, loadAnimalFromTextFile))
	{
		puts(msg);
		return 0;
	}
	return 1;
}

int	saveAnimalArrToBinaryFile(const Store* pStore, FILE* fp, const char* msg)
{
	if (!generalSaveLoadArrFile(pStore->animalArr, pStore->animalCount, sizeof(Animal*), fp, saveAnimalToBinaryFile))
	{
		puts(msg);
		return 0;
	}
	return 1;
}

int	loadAnimalArrFromBinaryFile(Store* pStore, FILE* fp, const char* msg)
{

	if (!generalSaveLoadArrFile(pStore->animalArr, pStore->animalCount, sizeof(Animal*), fp, loadAnimalFromBinaryFile))
	{
		puts(msg);
		return 0;
	}
	return 1;
}

void printStore(const  void* val)
{
	const Store* pStore = (const Store*)val;
	printf("Store number: %d\n", pStore->storeNumber);
	printf("City: %s\n", pStore->city);
	printf("\n -------- Has %d Animals --------\n", pStore->animalCount);
	printAnimalsArr(pStore->animalArr, pStore->animalCount);
}

void printStoreInShort(const void* val)
{
	const Store* pStore = (const Store*)val;
	printf("Store number: %d\n", pStore->storeNumber);
	printf("City: %s\n", pStore->city);
}

void printAnimalsArr(Animal** arr, int size)
{
	generalArrayFunction(arr, size, sizeof(Animal*), printAnimal);
}

void freeStore(void* val)
{
	const Store* pStore = (const Store*)val;
	freeAnimalsArr(pStore->animalArr, pStore->animalCount);
	FREE_POINTER(pStore->city);
	FREE_POINTER(pStore->animalArr);
}

void freeAnimalsArr(Animal** arr, int size)
{
	generalArrayFunction(arr, size, sizeof(Animal*), freeAnimal);
}