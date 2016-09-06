#include <string>
#pragma once
using namespace std;
class MovieReview
{
public:
	int movieID;
	int userID;
	int rating;
	string reviewDate;
	MovieReview();
	MovieReview(int mID, int uID, int mRating, string revDate);
	~MovieReview();
};

