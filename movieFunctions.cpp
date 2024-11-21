
/******************************************************************************

Names: Alecxander Cooper
Date: 10/29/2024
Class: CISP 360

Version: 1.002

*******************************************************************************/
#include "movieHeader.h"

void movieMain() {
	movieStruct movie[NUM_OF_MOVIES]; // struct type movieStruct with the array movie[5]
	char userInput;
	int mid;
	std::string fileName = "MovieData.txt";
	std::ifstream inFile; // inFile is the variable where the file is stored?

	// runs through the program once, checks if quit was entered,
	// if not, keep running
	do {
		displayMovieMenu(); // menu text
		std::cin >> userInput;
		userInput = toupper(userInput);

		openFile(fileName, inFile); // opens the file
		readMoviesFromFile(inFile, movie); // stores data in the movie struct
		selectionSort(movie, NUM_OF_MOVIES); // sorts the movies by year

		switch(userInput) {
		case 'D': // display movies
			// Output the movie data
			for (int i = 0; i < 6; ++i) {
				std::cout << std::left << std::setw(30) << movie[i].title
				          << std::setw(10) << movie[i].releaseYear
				          << std::setw(24) << movie[i].director
				          << std::setw(18) << movie[i].genre
				          << std::setw(12) << movie[i].leadActor
				          << std::setw(12) << movie[i].coActor  << "\n";
			}
			break;
		case 'S': // search a specific movies
			mid = binarySearchMovieYear(movie, NUM_OF_MOVIES);
			std::cout << "movie found at index " << mid << "\n";
		case 'Q':
			std::cout << "Quiting...";
			break;
		default:
			std::cout << "does not work";
		}

	} while (userInput != 'q' && userInput != 'Q');
}

// menu
void displayMovieMenu() {
	std::cout << "\n*********************\n";
	std::cout << " Movie Selector Menu\n";
	std::cout << "*********************\n";
	std::cout << "Display Available Movies  :D\n";
	std::cout << "Search a Movie by Year    :S\n";
	std::cout << "Quit                      :Q\n";
	std::cout << "Enter your choice: ";
}

// function to open the movies file
// std::string& fileName is the name of the movie file
// std::ifstream& inFile is similar to cin, you can input values from files
// the & lets us change the value of the variables globally
void openFile(std::string& fileName, std::ifstream& inFile) {
	inFile.open(fileName); // opens movie.txt
	if (!inFile) { // check if the file opened successfully
		std::cerr << "Issue opening file: " << fileName << "\n";
	}
}

int readMoviesFromFile(std::ifstream& inFile, movieStruct movies[NUM_OF_MOVIES]) {
	int count = 0;
	std::string line;

	while (std::getline(inFile, line) && count < 6) {
		std::stringstream storeVariables(line); //gets lines of string from the text file
		movieStruct movie; // Use movieStruct type here



		// getline reads a variable and stores it as a string in a movieStruct field
		// uses the commas to tell it when there is a new line.
		std::getline(storeVariables /*where to get input from*/, movie.title, ',');
		storeVariables >> movie.releaseYear;
		storeVariables.ignore(); // ignores the comma after releaseYear
		std::getline(storeVariables, movie.director/*stored in this object*/, ',');
		std::getline(storeVariables, movie.genre, ',');
		std::getline(storeVariables, movie.leadActor, ',');
		std::getline(storeVariables, movie.coActor, ',');

		movies[count] = movie; // Store the movie in the array, this is a
		// whole new array under the movieStruct type
		count++; // each time the while statement runs, increment count.
	}

	inFile.close(); // Close the file after reading
	return count; // Return the number of movies read
}

// user will give the year of the movie they want to see, this function will go
// through the array movie year and compare each instance to the user input
int binarySearchMovieYear(movieStruct movie[NUM_OF_MOVIES], int NUM_OF_MOVIES) {
	int userMovieYear;
	std::cout << "what is the year of the movie you want to see?: ";
	std::cin >> userMovieYear;

	int left = 0;
	int right = NUM_OF_MOVIES - 1; // this is 5

	while (left <= right) { // when left is less than or equal to right
		int mid = left + (right - left) / 2; // Calculate middle index

		// Check if the target is at the middle
		if (movie[mid].releaseYear == userMovieYear) {
			return mid; // Target found, return the index
		}

		// If target is greater, ignore the left half
		if (movie[mid].releaseYear < userMovieYear) {
			left = mid + 1;
		}
		// If target is smaller, ignore the right half
		else {
			right = mid - 1;
		}
	}

	// Target not found
	return -1;
}



void selectionSort(movieStruct movie[NUM_OF_MOVIES], int NUM_OF_MOVIES) {
	// Outer loop for each position in the array
	for (int i = 0; i < NUM_OF_MOVIES - 1; i++) { // i declared in function
		// Assume the current position is the smallest
		int minIndex = i; // declared in function

		// Inner loop to find the smallest element in the unsorted part of the array
		for (int j = i + 1; j < NUM_OF_MOVIES; j++) {
			if (movie[j].releaseYear < movie[minIndex].releaseYear) {
				minIndex = j; // Update the index of the smallest element
			}
		}

		// Swap the found smallest element with the element at the current position
		if (minIndex != i) {
			int temp = movie[i].releaseYear;
			movie[i].releaseYear = movie[minIndex].releaseYear;
			movie[minIndex].releaseYear = temp;
		}
	}
}
