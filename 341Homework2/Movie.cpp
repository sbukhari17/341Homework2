#include "Movie.h"



Movie::Movie(int mID, string mName, int pYear)
{
	movieID = mID;
	movieName = mName;
	pubYear = pYear;
	reviewSum = 0;
	numReviews = 0;
	avgReview = 0;
	for (int & i : ratingCount) {
		i = 0;
	}
}

Movie::~Movie()
{
}


