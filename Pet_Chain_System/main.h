#ifndef __MAIN__
#define __MAIN__

#include "StoreManager.h"
#include "General.h"

typedef enum
{
	eUploadFromText, eUploadFromBinary, eNofOptionsInFileType
} eFileTypeOptions;

typedef enum
{
	eAddStore, eEnterStore, eAddDiscount, ePrintStores, eFindPopularAnimal, eFindMostAnimals, eNofOptionsInMain
} eMainMenuOptions;

typedef enum
{
	eAddAnimal, eAddReview, ePrintAnimals, eSortAnimals,
	eFindAnimal, eNoOptionsInStoreMenu
} eStoreMenu;


const char* str1[eNofOptionsInMain] = { "Upload system from text file", "Upload system from binary file"};

const char* str2[eNofOptionsInMain] = { "Add Store", "Enter a store", "Add/Update a discount to a specific category", 
										"Print all stores","Find most popular animal in the whole chain"
										, "Find store with most animals" };

const char* str3[eNoOptionsInStoreMenu] = { "Add Animal","Add a review", "Print all animals",
	"Sort Animals", "Find Animal"};

#define EXIT			-1
#define RETURN			-2
#define MANAGER_TEXT_FILE "storeChain.txt"
#define MANAGER_BINARY_FILE "storeChain.bin"
int menu();
void loadSystem(StoreManager* pManager);
int storeMenu();
void storeLobby(Store* pStore, Category* cat1, Category* cat2, Category* cat3);
void init3CategoriesHardCoded(Category* cat1, Category* cat2, Category* cat3);
Category* getSpecificCategory(eCategoryType eType, Category* cat1, Category* cat2, Category* cat3);

#endif // !__MAIN__