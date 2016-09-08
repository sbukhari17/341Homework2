#pragma once
#include "Movie.h"
#include "MovieReview.h"
#include "User.h"
vector<Movie> parseMovies(string movieFile);
vector <MovieReview> parseReviews(string reviewFile, vector<Movie>& movies);
void calculateAverages(vector<Movie>& movies);
vector<User> createUserInfo(vector <MovieReview> & movieReviews);
void runInteractiveLoop(vector<Movie> & movies);