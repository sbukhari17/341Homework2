#include "MovieReview.h"



MovieReview::MovieReview(int mID, int uID, int mRating, string revDate)
{
	movieID = mID;
	userID = uID;
	rating = mRating;
	reviewDate = revDate;
}


MovieReview::~MovieReview()
{
}
