#ifndef __MAIN__
#define __MAIN__

#include "StoreManager.h"
#include "General.h"

typedef enum
{
	eAddStore, eEnterStore, ePrintStores, eNofOptionsInMain
} eMainMenuOptions;

typedef enum
{
	eAddAnimal, eAddReview, eAddDiscount, /*eSortAnimals,
	eFindAnimal, eFindPopularAnimal, eFindExpensiveAnimal,*/ eNoOptionsInStoreMenu
} eStoreMenu;

const char* str1[eNofOptionsInMain] = { "Add Store", "Enter a store", "Print all stores"
										"Find store with most animals" };

const char* str2[eNoOptionsInStoreMenu] = { "Add Animal","Add a review",
										"Add/Update a discount to a specific category",
	/*"Sort Animals", "Find Animal", "Find most popular animal",
	"Find most expensive animal in store" */ };

#define EXIT			-1
#define RETURN			-2
int menu();
int storeMenu();
void storeLobby(Store* pStore, Category* cat1, Category* cat2, Category* cat3);
void init3CategoriesHardCoded(Category* cat1, Category* cat2, Category* cat3);
Category* getSpecificCategory(eCategoryType eType, Category* cat1, Category* cat2, Category* cat3);

#endif // !__MAIN__