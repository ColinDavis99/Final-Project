#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <ctime>
#include <ratio>
#include <chrono>
#include <algorithm>
#include <cctype>
#include <vector>
#include <utility>
#include "string_search_I.h"

//--------------------------------------------------------------------------------------------------------------------------------
//                                              | Rabin-Karp |
//--------------------------------------------------------------------------------------------------------------------------------
Rabin_Karp::Rabin_Karp (std::string inputString, std::string searchString, bool isFile, bool isCaseSensitive) { // constructor
    this->inputString = inputString;
    this->searchString = searchString;
    this->isFile = isFile;

    if (isFile) { // if it is a file format instead of a string
        this->inputString = processFile(inputString);
    }

    countObjs();

    this->tag = "Rabin-Karp " + std::to_string(Rabin_Karp::objCount);

    if (!isCaseSensitive) { // transform strings into all lowercase versions of themselves
        std::transform(this->inputString.begin(), this->inputString.end(), this->inputString.begin(), [](unsigned char c) { return std::tolower(c);});
        std::transform(this->searchString.begin(), this->searchString.end(), this->searchString.begin(), [](unsigned char c) { return std::tolower(c);});
    }

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

std::string Rabin_Karp::getTag() {
    return tag;
}

void Rabin_Karp::setTag(std::string tag) {
    this->tag = tag;
}

int Rabin_Karp::getOccurrences() {
    return occurrences;
}
void Rabin_Karp::setOccurrences(int occurrences) {
    this->occurrences = occurrences;
}

std::string Rabin_Karp::getHash() {
    return this->hashToGUI;
}

void Rabin_Karp::setHash(std::string hashVal) {
    this->hashToGUI = hashVal;
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

void Rabin_Karp::findRunTime(std::chrono::steady_clock::time_point &t_start) {
    std::chrono::steady_clock::time_point t_finish = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t_finish - t_start);
    double t_out = time_span.count()*1000000; // convert to microseconds
    this-> t_out = t_out;
    std::cout << "This search took \033[1;35m"<< t_out<< " \033[0mmicroseconds" << std::endl;
}

//Getters and Setters for Set time points
double Rabin_Karp::getRunTime() {
    return t_out;
}

void Rabin_Karp::setRunTime(double t_out) {
    this->t_out = t_out;
}



void Rabin_Karp::search(bool supressOutput) { // performs the actual string search
    //StartRuntime Here
    std::chrono::steady_clock::time_point t_start = std::chrono::steady_clock::now();
    std::list<int> foundIndexes; // list of the indexes where the search string was found
    int count = 0; // count the number of times searchString is found in inputString

    long long searchHash = hash(searchString);
    hashToGUI = std::to_string(searchHash); // set object variable for output to gui
    int searchStringLength = searchString.length();
    for (int i = 0; i + searchStringLength - 1 < inputString.length(); i++) { // goes until the length of the string is smaller than a search window
        searchWindow = inputString.substr(i, searchStringLength);
        if (hash(searchWindow) == searchHash) { // if hashes equal, and therefore strings are equal.
            foundIndexes.push_back(i);
            count++;
        }
    }

    occurrences = count;
    findRunTime(t_start);

    if (!supressOutput) {
        output(searchString, foundIndexes, count, tag);
    }

}

// Destructor
Rabin_Karp::~Rabin_Karp() {
    delete this; // delete whole object
}

//--------------------------------------------------------------------------------------------------------------------------------
//                                              | Boyer-Moore |
//--------------------------------------------------------------------------------------------------------------------------------

Boyer_Moore::Boyer_Moore (std::string inputString, std::string searchString, bool isFile, bool isCaseSensitive) { // constructor
    this->inputString = inputString;
    this->searchString = searchString;
    this->isFile = isFile;

    if (isFile) { // if it is a file format instead of a string
        this->inputString = processFile(inputString);
    }

    countObjs();
    this->tag = "Boyer-Moore " + std::to_string(Boyer_Moore::objCount);

    if (!isCaseSensitive) { // transform strings into all lowercase versions of themselves
        std::transform(this->inputString.begin(), this->inputString.end(), this->inputString.begin(), [](unsigned char c) { return std::tolower(c);});
        std::transform(this->searchString.begin(), this->searchString.end(), this->searchString.begin(), [](unsigned char c) { return std::tolower(c);});
    }

}

int Boyer_Moore::objCount = 0; // initialize static variable to 0

void Boyer_Moore::countObjs() {
    objCount++;
}

std::string Boyer_Moore::getTag() {
    return tag;
}

void Boyer_Moore::setTag(std::string tag) {
    this->tag = tag;
}

int Boyer_Moore::getOccurrences() {
    return occurrences;
}

void Boyer_Moore::setOccurrences(int occurrences) {
    this->occurrences = occurrences;
}

std::string Boyer_Moore::getBadCharTableHTML() {
    return badCharTableHTML;
}

void Boyer_Moore::setBadCharTableHTML(std::string badCharTableHTML) {
    this->badCharTableHTML = badCharTableHTML;
}

std::string Boyer_Moore::processFile(std::string &filename) {
    return Rabin_Karp::processFile(filename); // calls the Rabin_Karp process file function (will be the same)
}

void Boyer_Moore::output(std::string &searchString, std::list<int> &foundIndexes, int &count, std::string &tag) { // calls the Rabin_Karp output function (will be the same)
    Rabin_Karp::output(searchString,foundIndexes,count, tag);
}

void Boyer_Moore::findRunTime(std::chrono::steady_clock::time_point &t_start) {
    std::chrono::steady_clock::time_point t_finish = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t_finish - t_start);
    double t_out = time_span.count()*1000000; // convert to microseconds
    this-> t_out = t_out;
    std::cout << "This search took \033[1;35m"<< t_out<< " \033[0mmicroseconds" << std::endl;
}


double Boyer_Moore::getRunTime() {
    return t_out;
}

void Boyer_Moore::setRunTime(double t_out) {
    this->t_out = t_out;
}

int Boyer_Moore::badChar (int idx, std::string &inputString, std::string searchString, std::list<int> &foundIndexes, int &count, int searchLength, std::vector<std::pair<char,int>> &badCharTable) {
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
            idx++;
            return idx;
        }
        tempIdx--;
    }

    //If it reaches here that means it found a bad character

    for (int i = 0; i < badCharTable.size(); i++) { // if bad character found in table look up its shift value and apply it
        if (bad == badCharTable[i].first) {
            idx += badCharTable[i].second;
            return idx;
        }
    }
    // if character not found in bad char table increase index by search string length. This is the "OTHER" part of the table
    idx += searchLength;
    return idx;

}

void Boyer_Moore::generateBadCharTable(int searchLength, std::string &searchString, std::vector<std::pair<char,int>> &badCharTable) {
    char markedChar = '*';
    std::pair<char,int> tempPair;
    for (int i = 0; i < searchLength; i++) {
        tempPair.first = searchString[i];
        tempPair.second = searchLength-i-1;
        badCharTable.push_back(tempPair);
        for (int j = i; j >= 0; j--) {
            if ((tempPair.first == badCharTable[j].first) && (i != j)) {
                  badCharTable[j].second = tempPair.second; // override duplicates
                  badCharTable[j].first = markedChar;
                  break;
            }
        }
    }

    for (int k = 0; k < badCharTable.size(); k++) { //mark character
        if (badCharTable[k].first == markedChar) {
            badCharTable.erase(badCharTable.begin()+k);
            k--;
        }
        if (searchString[searchLength-1] == badCharTable[k].first) {
            badCharTable[k].second = searchLength;
        }
    }


}

void Boyer_Moore::search(bool supressOutput) { // performs the actual string search
    // start calculating runtime
    std::chrono::steady_clock::time_point t_start = std::chrono::steady_clock::now(); // start finding runtime
    idx = searchString.length()-1; //set initial index (goes right to left)
    std::list<int> foundIndexes; // list of the indexes where the search string was found
    int count = 0; // count the number of times searchString is found in inputString

    int searchLength = searchString.length();
    int inputLength = inputString.length();

    // Preprocessing - Bad Character Table
    // shift value = search length - index - 1 | repeats override
    std::vector<std::pair<char,int>> badCharTable;
    generateBadCharTable(searchLength, searchString, badCharTable);

    // Implementation of Algorithm
    while (idx < inputLength) {
        if (idx > inputLength-1) {
            std::cout << "ERROR: BOYER-MOORE" << std::endl;
            exit(0);
        }
        idx = badChar(idx, inputString, searchString, foundIndexes, count, searchLength, badCharTable); //shifts the index based on the bad character rule
    }

    occurrences = count; // set object variable for output to gui

    findRunTime(t_start);

    //FUNCTIONAL PART OF ALGORITHM ENDS HERE. RUNTIME IS NO LONGER RECORDED

    //Generate html for QT Label
    badCharTableHTML = "<style>table,th,td{border: 1px solid black;}th, td { padding: 10px;}</style><table border=\"1\"style=\"width:100%\"><caption>Boyer-Moore Bad Character Table</caption><tr>";
    std::string tempHTML;
    for (int k = 0; k < badCharTable.size(); k++) { // character
        tempHTML += "<td>";
        tempHTML += badCharTable[k].first;
        tempHTML += "</td>";
    }
    tempHTML += "<td>OTHER</td></tr><tr>";
    badCharTableHTML += tempHTML;
    tempHTML = "";
    for (int k = 0; k < badCharTable.size(); k++) { // character
        tempHTML += "<td>";
        tempHTML += std::to_string(badCharTable[k].second);
        tempHTML += "</td>";
    }
    tempHTML += "<td>";
    tempHTML += std::to_string(searchLength);
    tempHTML += "</td></tr></table>";
    badCharTableHTML += tempHTML;

    if (!supressOutput) { // output log to terminal
        output(searchString, foundIndexes, count, tag);
    }

}

Boyer_Moore::~Boyer_Moore() {
    delete this; // delete whole object
}
