#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Main.h"

//
// Netflix Movie Review Analysis
//
// Syed Bukhari
// U. of Illinois, Chicago
// CS341, Fall 2016
// HW #02

int main() {
	cout << "** Netflix Movie Review Analysis **" << endl;
	cout << endl;
	cout << ">> Reading movies... ";
	vector<Movie> movies = parseMovies("movies.csv");
	cout << movies.size() << endl;
	cout << ">> Reading reviews... ";
	sort(movies.begin(), movies.end(), [](Movie & mov1, Movie & mov2) {
		return mov1.movieID < mov2.movieID;
	});
	vector<MovieReview>moviereviews = parseReviews("reviews-2.csv", movies);
	cout << moviereviews.size() << endl;
	cout << endl;
	calculateAverages(movies);
	sort(movies.begin(), movies.end(), [](Movie & mov1, Movie & mov2) {
		if (mov1.avgReview > mov2.avgReview)
			return true;
		else if (mov2.avgReview > mov1.avgReview)
			return false;
		else
			return mov1.movieName.compare(mov2.movieName) < 0;
	});
	cout << ">>Top-10 Movies <<" << endl;
	cout << endl;
	cout << "Rank\tID\tReviews\tAvg\tName" << endl;
	for (int i = 0; i < 10; i++) {
		cout << i + 1 <<'.'
			<< '\t' << movies.at(i).movieID
			<< '\t' << movies.at(i).numReviews
			<< '\t' << movies.at(i).avgReview
			<< '\t' << '\'' << movies.at(i).movieName << '\'' << endl;
	}
	cout << endl;
	cout << ">> Top-10 Users <<" << endl;
	cout << endl;
	vector <User> users = createUserInfo(moviereviews);
	sort(users.begin(), users.end(), [](User & user1, User & user2) {
		if (user1.numReviews > user2.numReviews)
			return true;
		else if (user2.numReviews > user1.numReviews)
			return false;
		else
			return user1.id < user2.id;
	});
	cout << "Rank\tID\tReviews" << endl;
	for (int i = 0; i < 10; i++) {
		cout << i + 1 << '.'
			<< '\t' << users.at(i).id
			<< '\t' << users.at(i).numReviews << endl;
	}
	cout << endl;
	runInteractiveLoop(movies);



	return 0;
}
vector<Movie> parseMovies(string movieFile) { //parses movie file and returns vector of movies
	vector<Movie> movies;
	ifstream movieStream(movieFile);
	string input;
	getline(movieStream, input); //skip first line
	while (getline(movieStream, input)) {
		stringstream ss(input);
		string movieid, moviename, pubyear;

		getline(ss, movieid, ',');
		getline(ss, moviename, ',');
		getline(ss, pubyear, ',');
		Movie m(stoi(movieid), moviename, stoi(pubyear));
		movies.push_back(m);
	}
	return movies;
}
vector <MovieReview> parseReviews(string reviewFile, vector<Movie> & movies) {
	vector<MovieReview> movieReviews;
	ifstream reviewStream(reviewFile);
	string input;
	getline(reviewStream, input); //skip first line
	while (getline(reviewStream, input)) {
		stringstream ss(input);
		string movieid, userid, rating, reviewdate;

		getline(ss, movieid, ',');
		getline(ss, userid, ',');
		getline(ss, rating, ',');
		getline(ss, reviewdate, ',');
		MovieReview mr(stoi(movieid), stoi(userid), stoi(rating), reviewdate);

		movies[mr.movieID-1].ratingCount[mr.rating - 1]++;
		movies[mr.movieID-1].reviewSum += mr.rating;
		movies[mr.movieID-1].numReviews++;
	
		movieReviews.push_back(mr);
	}
	sort(movieReviews.begin(), movieReviews.end(), [](const MovieReview & mov1, const MovieReview & mov2) {
		return mov1.movieID < mov2.movieID;
	});
	return movieReviews;
}

void calculateAverages(vector<Movie>& movies) {
	for (Movie & movie : movies) {
		movie.avgReview = (double)movie.reviewSum / (double)movie.numReviews;
	}
}

vector<User> createUserInfo(vector <MovieReview> & movieReviews) { //not being used
	vector<User> users;
	int currIndex = 0;
	int currID = movieReviews.at(0).movieID;
	users.push_back(User(currID));
	for (MovieReview & movReview : movieReviews) {
		if (movReview.movieID == currID) {
			users.at(currIndex).numReviews++;
		}
		else {
			currID = movReview.movieID;
			users.push_back(User(currID));
			currIndex++;
		}
	}
	return users;
}
void runInteractiveLoop(vector<Movie> & movies) {
	string input;
	cout << ">> Movie Information <<" << endl;
	cout << endl;
	string prompt = "Pleae enter a movie ID [1.." + to_string(movies.size()) + "], 0 to stop: ";
	
	cout << prompt;
	cin >> input;
	while (stoi(input) != 0){
		int entry = stoi(input);
		if (entry<0 || entry > movies.size()) {
			cout << "** Invalid movie id, please try again..." << endl;
			cout << prompt;
			cin >> input;
		}
		else {
			auto iterator = find_if(movies.begin(), movies.end(), [&entry](Movie & mov) {
				return entry == mov.movieID;
			});
			if (iterator != movies.end()) {
				auto index = distance(movies.begin(), iterator);
				cout << endl;
				cout << "Movie:\t" << '\'' << movies.at(index).movieName << '\'' << endl;
				cout << "Year:\t" << movies.at(index).pubYear << endl;
				cout << "Avg rating:\t" << movies.at(index).avgReview << endl;
				cout << "Num reviews:\t" << movies.at(index).numReviews << endl;
				cout << "Num 1's:\t" << movies.at(index).ratingCount[0] << endl;
				cout << "Num 2's:\t" << movies.at(index).ratingCount[1] << endl;
				cout << "Num 3's:\t" << movies.at(index).ratingCount[2] << endl;
				cout << "Num 4's:\t" << movies.at(index).ratingCount[3] << endl;
				cout << "Num 5's:\t" << movies.at(index).ratingCount[4] << endl;
				cout << endl;
			}
			cout << prompt;
			cin >> input;
		}
	} 
	cout << endl;
	cout << endl;
	cout << "** DONE! **" << endl;
}