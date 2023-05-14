#include <iostream>
#pragma warning (disable: 4996)

enum class Genre { Comedy, Action, Horror, Romantic };

const unsigned short MAX_NAME_LENGTH = 30;

struct Movie {

	char name[MAX_NAME_LENGTH + 1];
	unsigned int minutes;
	Genre genre;
	double rating;
};

void initMovie(Movie& movie, const char* name, const unsigned int minutes, const Genre genre, const double rating) {

	if (strlen(name) > MAX_NAME_LENGTH) {
		std::cout << name << " is way too long for a movie name!" << std::endl;
		return;
	}
	strcpy(movie.name, name);
	movie.minutes = minutes;
	movie.genre = genre;
	movie.rating = rating;
}

void printMovie(const Movie& movie) {

	std::cout << "Name: " << movie.name << ", Length: " << movie.minutes
		<< ", Rating: " << movie.rating << std::endl;
}

void printAllMovies(const Movie* movies, unsigned short moviesAmount) {

	for (unsigned short i = 0; i < moviesAmount; i++) {
		printMovie(movies[i]);
	}
}

void sortMoviesByRating(Movie* movies, unsigned short moviesAmount) {
	double highestRating = 0.0;
	int highestRatingIndex = 0;
	for (unsigned short i = 0; i < moviesAmount; i++) {
		for (unsigned short j = i + 1; j < moviesAmount; j++) {
			if (movies[j].rating > movies[i].rating) {
				Movie temp;
				temp = movies[i];
				movies[i] = movies[j];
				movies[j] = temp;
			}
		}
	}
}

void printMovieWithHighestRating(Movie* movies, unsigned short moviesAmount) {

	sortMoviesByRating(movies, moviesAmount);
	std::cout << "Movie with highest rating: ";
	printMovie(movies[0]);
}

int main() {

	Movie m1;
	initMovie(m1, "movie1", 12, Genre::Comedy, 4.6);

	Movie m2;
	initMovie(m2, "movie2", 12, Genre::Comedy, 5.4);

	Movie m3;
	initMovie(m3, "movie3", 12, Genre::Comedy, 4.9);

	Movie movies[3] = { m1, m2, m3 };
	sortMoviesByRating(movies, 3);
	printMovieWithHighestRating(movies, 3);
}