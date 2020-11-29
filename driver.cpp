#include <iostream>
#include <string>
#include "string_search_I.h"
#include <chrono>


//Driver Code & Test Case
int main() {
    std::string fileName = "blackhat2014.txt";
    std::string searchString = "the";


    Rabin_Karp Rabin_Karp1(fileName, searchString, true);
    Rabin_Karp1.search();

    //Rabin_Karp Rabin_Karp2("file2.txt", "123", true);
    //Rabin_Karp2.search();

    //Boyer_Moore Boyer_Moore1(fileName, searchString, true); // makes a boyer_moore object
    //Boyer_Moore1.search(); // runs the boyer_moore search algorith on the object


}