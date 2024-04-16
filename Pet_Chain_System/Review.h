#ifndef __REVIEW__
#define __REVIEW__

#include "Date.h"

typedef struct
{
	char* comment;
	Date date;
}Review;

int initReview(Review* pRev);
void printReview(const void* val);
void freeReview(void* pReview);

#endif // !__REVIEW__