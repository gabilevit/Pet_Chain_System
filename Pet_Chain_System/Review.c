#include "Review.h"
#include "General.h"

#include <stdio.h>
#include <stdlib.h>

int initReview(Review* pRev)
{
	pRev->comment = getStrExactName("Write a comment (max 255 string lenght):");
	if (!pRev->comment)
		return 0;
	generateCurrentDate(&pRev->date);
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