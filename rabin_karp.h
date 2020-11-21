#ifndef __RABIN_KARP_H__
#define __RABIN_KARP_H__

#include <fstream>
#include <string>

class Rabin_Karp {
     private :
        std::string inputString; // can be filename or string
        std::string searchString; //string you are searching for will not change
        bool isFile;

     public :
        Rabin_Karp(std::string inputString, std::string searchString, bool isFile); // constructor for looking through a txt file
        static int hash(std::string stringToHash); //find the hash value of a string or substring
        void search(); //search the file or input string for the search string
};

#endif

// searchString = "TEST"
// inputString = "2-934-290382-034TEST3498-23894-2"
//
// result "Appears at index 16"