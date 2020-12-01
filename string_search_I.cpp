#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include "string_search_I.h"
#include <chrono>

//--------------------------------------------------------------------------------------------------------------------------------
//                                              | Rabin-Karp |
//--------------------------------------------------------------------------------------------------------------------------------
Rabin_Karp::Rabin_Karp (std::string inputString, std::string searchString, bool isFile) { // constructor
    this->inputString = inputString;
    this->searchString = searchString;
    this->isFile = isFile;

    if (isFile) { // if it is a file format instead of a string
        this->inputString = processFile(inputString);
    }

    countObjs();

    this->tag = "Rabin-Karp " + std::to_string(Rabin_Karp::objCount);

}

int Rabin_Karp::objCount = 0; // initialize static variable to 0

void Rabin_Karp::countObjs() {
    objCount++;
}

std::string Rabin_Karp::getSearchWindow() {
    return searchWindow;
}

void Rabin_Karp::setSearchWindow(std::string &searchWindow) {
    this->searchWindow = searchWindow;
}

std::string Rabin_Karp::processFile(std::string &filename) { //converts inputString into the contents of the file and stores it back in inputString
    std::ifstream inFile;

    inFile.open(filename);

    std::stringstream stringStream;
    stringStream << inFile.rdbuf(); // read the file until buffer
    std::string convertedString = stringStream.str(); // store the contents in a string

    inFile.close();

    return convertedString;

}

long long Rabin_Karp::hash(std::string &stringToHash) { // find the hash of a string or substring
    //NOTE: This is a polynomial rolling hash function
    const int p_base = 97; // prime base. since there are 95 possible characters and 97 is the closest prime number
    const int d_base = 1000000007; // dividend base (10^9 + 7, a large prime number) d_base = "m"
    int p_pow = 1; // The power of the prime number
    long long hashVal = 0;
    for (int i = 0; i < stringToHash.length(); i++) {
        hashVal = (hashVal +  (stringToHash[i] - 'a' + 1) * p_pow) % d_base;
        p_pow = (p_pow * p_base) % d_base;
    }

    return hashVal;
}

void Rabin_Karp::output(std::string &searchString, std::list<int> &foundIndexes, int &count, std::string &tag) {

    std::cout << "----------------------------------------------------------------------------" << std::endl;
    std::cout << "Search results for " << "\033[1;33m" << tag << "\033[0m:" << std::endl;
    std::cout << std::endl;

    if (foundIndexes.empty()) {
        std::cout << "The string " << "'\033[1;36m" << searchString << "\033[0m'" << " \033[1;31mwas not found\033[0m" << std::endl;
    } else if (foundIndexes.size() == 1) {
        std::cout << "The string " << "'\033[1;36m" << searchString << "\033[0m'" << " was found at index " << foundIndexes.front() << "." << std::endl;
        std::cout << "It was found " << count << " time" << std::endl; //  1 time
    } else {
        std::string outputIndexes = "The string '\033[1;36m";
        outputIndexes += searchString + "\033[0m' was found at indexes ";
        for(std::list<int>::iterator i = foundIndexes.begin(); i != foundIndexes.end(); ++i) {
            if (*i == foundIndexes.back())  {
                outputIndexes += "and " + std::to_string(*i);
            } else {
                outputIndexes += std::to_string(*i) + ", ";
            }
        }
        std::cout << outputIndexes << std::endl;
        std::cout << "It was found \033[1;32m" << count << " \033[0mtimes" << std::endl;
    }

}

void Rabin_Karp::findRunTime(auto &t_start) {
    auto t_finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t_finish - t_start ).count();
    int t_out = duration;
    this-> t_out = t_out;
    std::cout << "This search took \033[1;35m"<< t_out<< " \033[0mmicroseconds" << std::endl;
}

//Getters and Setters for Set time points
int Rabin_Karp::getRunTime() {
    return t_out;
}

void Rabin_Karp::setRunTime(int t_out) {
    this->t_out = t_out;
}



void Rabin_Karp::search(bool supressOutput) { // performs the actual string search
    //StartRuntime Here
    auto t_start = std::chrono::high_resolution_clock::now();
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

    if (!supressOutput) {
        output(searchString, foundIndexes, count, tag);
    }

    findRunTime(t_start);

}

//--------------------------------------------------------------------------------------------------------------------------------
//                                              | Boyer-Moore |
//--------------------------------------------------------------------------------------------------------------------------------

Boyer_Moore::Boyer_Moore (std::string inputString, std::string searchString, bool isFile) { // constructor
    this->inputString = inputString;
    this->searchString = searchString;
    this->isFile = isFile;

    if (isFile) { // if it is a file format instead of a string
        this->inputString = processFile(inputString);
    }

    countObjs();
    this->tag = "Boyer-Moore " + std::to_string(Boyer_Moore::objCount);

}

int Boyer_Moore::objCount = 0; // initialize static variable to 0

void Boyer_Moore::countObjs() {
    objCount++;
}

std::string Boyer_Moore::processFile(std::string &filename) {
    return Rabin_Karp::processFile(filename); // calls the Rabin_Karp process file function (will be the same)
}

void Boyer_Moore::output(std::string &searchString, std::list<int> &foundIndexes, int &count, std::string &tag) { // calls the Rabin_Karp output function (will be the same)
    Rabin_Karp::output(searchString,foundIndexes,count, tag);
}

void Boyer_Moore::findRunTime(auto &t_start) {
    auto t_finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t_finish - t_start ).count();
    int t_out = duration;
    this-> t_out = t_out;
    std::cout << "This search took \033[1;35m"<< t_out<< " \033[0mmicroseconds";
    std::cout << std::endl;
}


int Boyer_Moore::getRunTime() {
    return t_out;
}

void Boyer_Moore::setRunTime(int t_out) {
    this->t_out = t_out;
}

int Boyer_Moore::calulateShiftsBadChar(int idx, char bad, std::string &searchString, int searchIdx, int searchLength) {
    if (searchIdx == 0) {
        if (searchString[0] == bad) {
            idx++;
        } else {
            idx += searchLength-1;
        }
    } else {
        int shifts = 0;
        for (int i = searchIdx-1; i >= 0; i--) {
            shifts++;
            if (searchString[i] == bad) { // bad char found in searchString
                idx += shifts;
                break;
            } else if (i == 0) { // bad char not found in searchString
                idx += searchLength-1;
            }
        }
    }

    return idx;
}

int Boyer_Moore::badChar (int idx, std::string &inputString, std::string searchString, std::list<int> &foundIndexes, int &count, int searchLength) {
    int stopper = 0;
    int tempIdx = idx; // bad char index if applicable
    char bad;
    int searchIdx; // index of search that matches where the bad char occurs
    while (stopper - searchLength != 0) {
        stopper++;
        if (inputString[tempIdx] != searchString[searchLength-stopper]) { // if bad character
            bad = inputString[tempIdx];
            searchIdx = searchLength - stopper;
            break;
        } else if (stopper - searchLength == 0) { // on last iteration, if everything is a match
            foundIndexes.push_back(idx-searchLength+1);
            count++;
            idx++; // shift over 1
            break;
        }
        tempIdx--;
    }

    return calulateShiftsBadChar(idx, bad, searchString, searchIdx, searchLength);
}


void Boyer_Moore::search(bool supressOutput) { // performs the actual string search

    idx = searchString.length()-1; //set initial index (goes right to left)

    // start calculating runtime
    auto t_start = std::chrono::high_resolution_clock::now(); // start recording runtime
    std::list<int> foundIndexes; // list of the indexes where the search string was found
    int count = 0; // count the number of times searchString is found in inputString

    // Preprocessing
        // is where the lookup tables for boyer moore will be generated
        // no idea how to do this yet.. all examples use like 5 characters not entire ASCII ????

    // Implementation of Algorithm
    int searchLength = searchString.length();
    int inputLength = inputString.length();
    if (inputLength < searchLength) { // check for error with input
        std::cout << "error with length of input" << std::endl;
    } else {
        while (idx < inputLength - searchLength) {
            idx = badChar(idx, inputString, searchString, foundIndexes, count, searchLength);
        }
    }

    if (!supressOutput) {
        output(searchString, foundIndexes, count, tag);
    }

    findRunTime(t_start);

}