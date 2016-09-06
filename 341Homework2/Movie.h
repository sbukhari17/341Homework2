#pragma once
#include <string>

using namespace std;
class Movie
{
public:
	int movieID;
	string movieName;
	int pubYear;
	double avgReview;
	int numReviews;
	int ratingCount [5];
	int reviewSum;

	Movie();
	Movie(int mID, string mName, int pYear);
	~Movie();
};

