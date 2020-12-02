#include <iostream>
#include <string>
#include "string_search_I.h"

//Driver Code & Test Cases

// Making an object:
// [Rabin_Karp/Boyer_Moore] [Object Name](input file or string, what you want to search for, is it a file input?, is it case sensitive?)
// Example: Rabin_Karp Rabin_Karp1("AbCdEfG", "AbCdEfG", false, false);
// Operation: Will search for "ABC" in "AbCdEfG", it is not a file, it will not worry about capial letters
// Result: It will be found 1 time
// -----------------------
// Running a Search:
// [Object Name].search(do you want to supress the output to the terminal?)
// Example Rabin_Karp1.search(true);
// Operation: Will not spam the terminal with count and indexes. (useful when calculating average runtime)

void getAverageRunTime(Boyer_Moore Boyer_Moore_Obj, int numTrials);

void getAverageRunTime(Boyer_Moore Boyer_Moore_Obj, int numTrials) {

    int mean = 0;
    int i = 0;
    Boyer_Moore_Obj.search(true);
    int temptime = Boyer_Moore_Obj.getRunTime();
    while (i != numTrials) {
        Boyer_Moore_Obj.search(true);
        if (temptime >= 1.3*Boyer_Moore_Obj.getRunTime() ){
            getAverageRunTime(Boyer_Moore_Obj, numTrials);
        }
        if (Boyer_Moore_Obj.getRunTime() <= 1.3*temptime) {
            mean += Boyer_Moore_Obj.getRunTime();
            i++;
        }

    }
    mean /= numTrials;

    std::cout << "The mean runtime for " << Boyer_Moore_Obj.getTag() << " is " << mean << " microseconds" << std::endl;
}

int main() {

    //Rabin_Karp Rabin_Karp1("WELCOMETOONLINECOLLEGE", "COLLEGE", false, true);
    //Rabin_Karp1.search(false);

    //Boyer_Moore Boyer_Moore1("WELCOMETOONLINECOLLEGE", "COLLEGE", false, true); // makes a boyer_moore object
    //Boyer_Moore1.search(false); // runs the boyer_moore search algorith on the object

    Boyer_Moore Boyer_Moore2("blackhat2014.txt", "the", true, false);
    //Boyer_Moore2.search(true);

    Rabin_Karp Rabin_Karp2("blackhat2014.txt", "the", true, false);
    //Rabin_Karp2.search(true);

    //EXAMPLE: Calculates mean runtime for Boyer_Moore 2
    getAverageRunTime(Boyer_Moore2, 10);
    // EXAMPLE: Calculates mean runtime for Rabin_Karp2
    //int mean2 = 0;
    //for (int i = 0; i < 10; i++) {
        //Rabin_Karp2.search(true);
        //mean2 += Rabin_Karp2.getRunTime();
    //}
    //mean2 /= 10;
    //std::cout << "The mean runtime for Rabin_Karp2 was " << mean2 << " microseconds" << std::endl;
}