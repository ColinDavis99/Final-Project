#include <iostream>
#include <string>
#include "string_search_I.h"
#include <chrono>


//Driver Code & Test Cases

// Making an object:
// [Rabin_Karp/Boyer_Moore] [Object Name](input file or string, what you want to search for, is it a file input?, is it case sensitive?)
// Example: Rabin_Karp Rabin_Karp1("ABC", "AbCdEfG", false, false);
// Operation: Will search for "ABC" in "AbCdEfG", it is not a file, it will not worry about capial letters
// Result: It will be found 1 time
// -----------------------
// Running a Search:
// [Object Name].search(do you want to supress the output to the terminal?)
// Example Rabin_Karp1.search(false);
// Operation: Will not spam the terminal with count and indexes. (useful when calculating average runtime)

int main() {

    Rabin_Karp Rabin_Karp1("11111", "2", false, false);
    Rabin_Karp1.search(false);

    Boyer_Moore Boyer_Moore1("GCTTCTGCTACCTTTTGCGCGCGCGCGGAA", "CCTTTTGC", false, true); // makes a boyer_moore object
    Boyer_Moore1.search(false); // runs the boyer_moore search algorith on the object

    Boyer_Moore Boyer_Moore2("blackhat2014.txt", "the", true, false);
    Boyer_Moore2.search(false);

    Rabin_Karp Rabin_Karp2("blackhat2014.txt", "the", true, false);
    Rabin_Karp2.search(false);

    // EXAMPLE: Calculates mean runtime for Boyer_Moore 2
    //int mean = 0;
    //for (int i = 0; i < 10; i++) {
    //    Boyer_Moore2.search(true);
    //    mean += Boyer_Moore2.getRunTime();
    //}
    //mean /= 10;
    //std::cout << "The mean runtime for Boyer_Moore2 was " << mean << " microseconds" << std::endl;

    // EXAMPLE: Calculates mean runtime for Rabin_Karp2
    //int mean2 = 0;
    //for (int i = 0; i < 10; i++) {
    //    Rabin_Karp2.search(true);
    //    mean2 += Rabin_Karp2.getRunTime();
    //}
    //mean2 /= 10;
    //std::cout << "The mean runtime for Rabin_Karp2 was " << mean2 << " microseconds" << std::endl;
}