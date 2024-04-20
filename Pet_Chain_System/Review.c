#include "Review.h"

#include <stdio.h>
#include <stdlib.h>

int initReview(Review* pRev)
{
	pRev->comment = getStrExactName("Write a comment (max 255 string lenght):");
	if (!pRev->comment)
		return 0;
	generateCurrentDate(&pRev->date);
	return 1;
}

int	saveReviewToTextFile(const Review* pRev, FILE* fp)
{
	if (!writeStringToTextFile(pRev->comment, fp, "Error writing comment to text file\n"))
		return 0;
	if (!saveDateToTextFile(&pRev->date, fp))
		return 0;
	return 1;
}

int	loadReviewFromTextFile(Review* pRev, FILE* fp)
{
	pRev->comment = readDynStringFromTextFile(fp);
	if (!loadDateFromTextFile(&pRev->date, fp))
		return 0;
	return 1;
}

int	saveReviewToBinaryFile(const Review* pRev, FILE* fp)
{
	if (!writeStringToFile(pRev->comment, fp, "Error writing comment to binary file\n"))
		return 0;
	if (!saveDateToBinaryFileCompressed(&pRev->date, fp))
		return 0;
	return 1;
}

int	loadReviewFromBinaryFile(Review* pRev, FILE* fp)
{
	pRev->comment = readStringFromFile(fp, "Error reading comment from binary file\n");
	if (!loadDateFromBinaryFileCompressed(&pRev->date, fp))
		return 0;
	return 1;
}

void printReview(const void* val)
{
	const Review* pRev = (const Review*)val;
	printf("Comment: %s\n", pRev->comment);
	printDate(&pRev->date);
}

void freeReview(void* pReview)
{
	Review* pRev = (Review*)pReview;
	free(pRev->comment);
}