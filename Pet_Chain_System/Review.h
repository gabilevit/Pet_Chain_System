#ifndef __REVIEW__
#define __REVIEW__

#include "Date.h"
#include "General.h"
#include "FileHelper.h"
#include "macros.h"

typedef struct
{
	char* comment;
	Date date;
}Review;

int initReview(Review* pRev);


// FILE FUNCTIONS
int	saveReviewToTextFile(const Review* pRev, FILE* fp);
int	loadReviewFromTextFile(Review* pRev, FILE* fp);
int	saveReviewToBinaryFile(const Review* pRev, FILE* fp);
int	loadReviewFromBinaryFile(Review* pRev, FILE* fp);

// PRINT FUNCTION
void printReview(const void* val);

// FREE FUNCTION
void freeReview(void* pReview);

#endif // !__REVIEW__