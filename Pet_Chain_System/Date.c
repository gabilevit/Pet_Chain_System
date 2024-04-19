#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Date.h"

const int DAY_MONTHS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
#define SPECIAL_TAV '#'

void getCorrectDate(Date* pDate)
{
	char date[MAX_STR_LEN];
	int ok = 1;

	do {
		printf("Enter birth Date dd%c%cmm%c%cyyyy  minimum year %d\t",
			SPECIAL_TAV, SPECIAL_TAV, SPECIAL_TAV, SPECIAL_TAV, MIN_YEAR);
		myGets(date, MAX_STR_LEN, stdin);
		ok = checkDate(date, pDate);
		if (!ok)
			printf("Error try again\n");
	} while (!ok);
}

void	generateCurrentDate(Date* pDate)
{
	time_t currentTime;
	struct tm* localTime;

	// Get current time
	currentTime = time(NULL);
	localTime = localtime(&currentTime);

	// Assign current date components
	pDate->day = localTime->tm_mday;
	pDate->month = localTime->tm_mon + 1; // Months are zero-based
	pDate->year = localTime->tm_year + 1900; // Years since 1900
}

int	 checkDate(char* date, Date* pDate)
{
	int day, month, year;
	if (strlen(date) != 12)
		return 0;
	if ((date[2] != SPECIAL_TAV) || (date[3] != SPECIAL_TAV)
		|| (date[6] != SPECIAL_TAV) || (date[7] != SPECIAL_TAV))
		return 0;
	sscanf(date, "%d%*c%*c%d%*c%*c%d", &day, &month, &year);
	if (day < 1 || month < 1 || month > 12 || year < MIN_YEAR)
		return 0;

	if (day > DAY_MONTHS[month - 1])
		return 0;

	pDate->day = day;
	pDate->month = month;
	pDate->year = year;

	return 1;
}

int	compareDate(const void* d1, const void* d2)
{
	const Date* pDate1 = (const Date*)d1;
	const Date* pDate2 = (const Date*)d2;
	if (pDate1->year > pDate2->year)
		return 1;
	if (pDate1->year < pDate2->year)
		return -1;
	if (pDate1->month > pDate2->month)
		return 1;
	if (pDate1->month < pDate2->month)
		return -1;
	if (pDate1->day > pDate2->day)
		return 1;
	if (pDate1->day < pDate2->day)
		return -1;
	return 0;
}

int		saveDateToTextFile(const Date* pDate, FILE* fp)
{
	if (!writeIntToTextFile(pDate->day, fp, "Error writing day to text file\n"))
		return 0;
	if (!writeIntToTextFile(pDate->month, fp, "Error writing month to text file\n"))
		return 0;
	if (!writeIntToTextFile(pDate->year, fp, "Error writing year to text file\n"))
		return 0;
	return 1;
}

int		loadDateFromTextFile(Date* pDate, FILE* fp)
{
	if (!readIntFromTextFile(&pDate->day, fp, "Error reading day from text file\n"))
		return 0;
	if (!readIntFromTextFile(&pDate->month, fp, "Error reading month from text file\n"))
		return 0;
	if (!readIntFromTextFile(&pDate->year, fp, "Error reading year from text file\n"))
		return 0;
	return 1;
}

int		saveDateToBinaryFile(const Date* pDate, FILE* fp)
{
	if (!writeIntToFile(pDate->day, fp, "Error writing day to binary file\n"))
		return 0;
	if (!writeIntToFile(pDate->month, fp, "Error writing month to binary file\n"))
		return 0;
	if (!writeIntToFile(pDate->year, fp, "Error writing year to binary file\n"))
		return 0;
	return 1;
}

int		loadDateFromBinaryFile(Date* pDate, FILE* fp)
{
	if (!readIntFromFile(&pDate->day, fp, "Error reading day from binary file\n"))
		return 0;
	if (!readIntFromFile(&pDate->month, fp, "Error reading month from binary file\n"))
		return 0;
	if (!readIntFromFile(&pDate->year, fp, "Error reading year from binary file\n"))
		return 0;
	return 1;
}

void printDate(const Date* pDate)
{
	printf("Date: %d/%d/%d\n", pDate->day, pDate->month, pDate->year);
}

int saveDateToFile(FILE* f, Date* pDate)
{
	if (fwrite(pDate, sizeof(Date), 1, f) != 1)
		return 0;
	return 1;
}
