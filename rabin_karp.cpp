#include <iostream>
#include <fstream>
#include <string>
#include "rabin_karp.h"

Rabin_Karp::Rabin_Karp (std::string inputString, std::string searchString, bool isFile) { // constructor
    this->inputString = inputString;
    this->searchString = searchString;
    this->isFile = isFile;
}

// Rabin1 = Rabin_Karp("aoee", "wfoiwjef", false); // example of searching for a string in a string
// Rabin2 = Rabin_Karp("file.txt", "sedjfw", true); // example of searching for a string in a file
// Rabin1.search();
// Rabin2.search();

int Rabin_Karp::hash(std::string stringToHash) { // find the hash of a string or substring
    return 23;
}

void Rabin_Karp::search() { // performs the actual string search
    std::cout << "Hello World" << std::endl;
}

//Rabin_Karp::hash("asiejfwojef")
//std::cout