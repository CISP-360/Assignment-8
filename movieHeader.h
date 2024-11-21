
/******************************************************************************

Names: Alecxander Cooper
Date: 10/29/2024
Class: CISP 360

Version: 1.000

*******************************************************************************/
// libraries
#include <iostream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

//structs
struct movieStruct{
   std::string title;
   int releaseYear;
   std::string director;
   std::string genre;
   std::string leadActor;
   std::string coActor;
   
};

// constant variables
const int NUM_OF_MOVIES = 6;

// headers
void movieMain();
void displayMovieMenu();
void openFile(std::string& fileName, std::ifstream& inFile);
int readMoviesFromFile(std::ifstream& inFile, movieStruct movie[NUM_OF_MOVIES]);
int binarySearchMovieYear(movieStruct movie[NUM_OF_MOVIES], int NUM_OF_MOVIES);
void selectionSort(movieStruct movie[NUM_OF_MOVIES], int NUM_OF_MOVIES);
