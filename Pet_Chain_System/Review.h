#ifndef __REVIEW__
#define __REVIEW__

#include "Date.h"

typedef struct
{
	char* info;
	Date date;
}Review;

void initReview(Review* pRev);
void printReview(const Review* pRev);
void freeReview(Review* pRev);

#endif // !__REVIEW__