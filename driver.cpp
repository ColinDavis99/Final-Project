#include <iostream>
#include <string>
#include "string_search_I.h"


//Driver Code & Test Case
int main() {
    std::string fileName = "file.txt";
    std::string searchString = "1233";

    //Rabin_Karp Rabin1(fileName, searchString, true);
    //Rabin1.search();

    Boyer_Moore Boyer_Moore1(fileName, searchString, true); // makes a boyer_moore object
    Boyer_Moore1.search(); // runs the boyer_moore search algorith on the object
}