#include <iostream>
#include <string>
#include "rabin_karp.h"


//Driver Code
int main() {
    std::string inputString = "123456789";
    std::string searchString = "123";
    Rabin_Karp Rabin1(inputString, searchString, false);
    Rabin1.search();
}