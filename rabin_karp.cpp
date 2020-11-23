#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include "rabin_karp.h"

Rabin_Karp::Rabin_Karp (std::string inputString, std::string searchString, bool isFile) { // constructor
    this->inputString = inputString;
    this->searchString = searchString;
    this->isFile = isFile;

    if (isFile) { // if it is a file format instead of a string
        this->inputString = processFile(inputString);
        std::cout << inputString << std::endl;
    }

}

// Rabin1 = Rabin_Karp("aoee", "wfoiwjef", false); // example of searching for a string in a string
// Rabin2 = Rabin_Karp("file.txt", "sedjfw", true); // example of searching for a string in a file
// Rabin1.search();
// Rabin2.search();

std::string Rabin_Karp::getSearchWindow() {
    return searchWindow;
}

void Rabin_Karp::setSearchWindow(std::string searchWindow) {
    this->searchWindow = searchWindow;
}

std::string Rabin_Karp::processFile(std::string filename) { //converts inputString into the contents of the file and stores it back in inputString
    std::ifstream inFile;

    inFile.open(filename);

    std::stringstream stringStream;
    stringStream << inFile.rdbuf(); // read the file until buffer
    std::string convertedString = stringStream.str(); // store the contents in a string

    inFile.close();

    return convertedString;

}

long long Rabin_Karp::hash(std::string stringToHash) { // find the hash of a string or substring
    //NOTE: This is a polynomial rolling hash function
    const int p_base = 97; // prime base. since there are 95 possible characters and 97 is the closest prime number
    const int d_base = 1000000007; // dividend base (10^9 + 7, a large prime number)
    int p_pow = 1; // The power of the prime number
    long long hashVal = 0;
    for (int i = 0; i < stringToHash.length(); i++) {
        hashVal = (hashVal +  (stringToHash[i] - 'a' + 1) * p_pow) % d_base;
        p_pow = (p_pow * p_base) % d_base;
    }

    return hashVal;
}

void Rabin_Karp::output(std::string searchString, std::list<int> foundIndexes, int count) {
    if (foundIndexes.empty()) {
        std::cout << "The string " << "'" << searchString << "'" << " was not found.";
    } else if (foundIndexes.size() == 1) {
        std::cout << "The string " << "'" << searchString << "'" << " was found at index " << foundIndexes.front() << "." << std::endl;
        std::cout << "It was found " << count << " time." << std::endl;
    } else {
        std::string outputIndexes = "The string '";
        outputIndexes += searchString + "' was found at indexes ";
        for(std::list<int>::iterator i = foundIndexes.begin(); i != foundIndexes.end(); ++i) {
            if (*i == foundIndexes.back())  {
                outputIndexes += "and " + std::to_string(*i);
            } else {
                outputIndexes += std::to_string(*i) + ", ";
            }
        }
        std::cout << outputIndexes << std::endl;
        std::cout << "It was found " << count << " times." << std::endl;
    }

}


void Rabin_Karp::search() { // performs the actual string search
    std::list<int> foundIndexes; // list of the indexes where the search string was found
    int count = 0; // count the number of times searchString is found in inputString

    long long searchHash = hash(searchString);
    int searchStringLength = searchString.length();
    for (int i = 0; i + searchStringLength - 1 < inputString.length(); i++) { // goes until the length of the string is smaller than a search window
        searchWindow = inputString.substr(i, searchStringLength);
        if (hash(searchWindow) == searchHash) { // if hashes equal, and therefore strings are equal.
            foundIndexes.push_back(i);
            count++;
        }
    }

    output(searchString, foundIndexes, count);
}


//Rabin_Karp::hash("asiejfwojef")
//std::cout