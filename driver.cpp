#include <iostream>
#include <string>
#include "rabin_karp.h"


//Driver Code
int main() {
    std::string fileName = "file.txt";
    std::string searchString = "123";
    Rabin_Karp Rabin1(fileName, searchString, true);
    Rabin1.search();
}