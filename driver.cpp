#include <iostream>
#include <string>
#include "string_search_I.h"
#include <chrono>


//Driver Code & Test Cases
int main() {

    std::string fileName = "blackhat2014.txt";
    std::string searchString = "the";


    Rabin_Karp Rabin_Karp1("11111", "2", false);
    Rabin_Karp1.search(false);

    Boyer_Moore Boyer_Moore1("GCTTCTGCTACCTTTTGCGCGCGCGCGGAA", "CCTTTTGC", false); // makes a boyer_moore object
    Boyer_Moore1.search(false); // runs the boyer_moore search algorith on the object

    // EXAMPLE: Calculates mean runtime for
    Boyer_Moore Boyer_Moore2(fileName, searchString, true);
    int mean = 0;
    for (int i = 0; i < 10; i++) {
        Boyer_Moore2.search(true);
        mean += Boyer_Moore2.getRunTime();
    }
    mean /= 10;

    std::cout << "The mean runtime for Boyer_Moore2 was " << mean << " microseconds" << std::endl;

    Rabin_Karp Rabin_Karp2(fileName, searchString, true);
    int mean2 = 0;
    for (int i = 0; i < 10; i++) {
        Rabin_Karp2.search(true);
        mean2 += Rabin_Karp2.getRunTime();
    }
    mean2 /= 10;

    std::cout << "The mean runtime for Rabin_Karp2 was " << mean2 << " microseconds" << std::endl;
}