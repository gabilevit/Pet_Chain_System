#ifndef __MYDATE__
#define __MYDATE__

#include "General.h"
#include "FileHelper.h"

#define MIN_YEAR 2000

typedef struct
{
	int			day;
	int			month;
	int			year;
}Date;

void	getCorrectDate(Date* pDate);
void	generateCurrentDate(Date* pDate);
int		checkDate(char* date, Date* pDate);

// COMPARE FUNCTION
int	compareDate(const void* d1, const void* d2);

// FILE FUNCTIONS
int		saveDateToTextFile(const Date* pDate, FILE* fp);
int		loadDateFromTextFile(Date* pDate, FILE* fp);
int		saveDateToBinaryFile(const Date* pDate, FILE* fp);
int		loadDateFromBinaryFile(Date* pDate, FILE* fp);

// PRINT FUNCTION
void	printDate(const Date* pDate);

#endif
