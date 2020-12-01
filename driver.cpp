#include <iostream>
#include <string>
#include "string_search_I.h"
#include <chrono>


//Driver Code & Test Cases
int main() {
    std::string fileName = "blackhat2014.txt";
    std::string searchString = "the";


    //Rabin_Karp Rabin_Karp1(fileName, searchString, true);
    //Rabin_Karp1.search();

    //Rabin_Karp Rabin_Karp2("11111", "1", false);
    //Rabin_Karp2.search();

    //Boyer_Moore Boyer_Moore1("GCTTCTGCTACCTTTTGCGCGCGCGCGGAA", "CCTTTTGC", false); // makes a boyer_moore object
    //Boyer_Moore1.search(); // runs the boyer_moore search algorith on the object

    Boyer_Moore Boyer_Moore2(fileName, searchString, true);
    Boyer_Moore2.search();
    
    

}