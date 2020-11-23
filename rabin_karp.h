#ifndef __RABIN_KARP_H__
#define __RABIN_KARP_H__

#include <fstream>
#include <string>
#include <list>

class Rabin_Karp {
     private :
        std::string inputString; // can be filename or string
        std::string searchString; //string you are searching for
        bool isFile; // determines if string describes the name of a file or just a search string
        std::string searchWindow;

     public :
        Rabin_Karp(std::string inputString, std::string searchString, bool isFile); // constructor for looking through a txt file
        std::string getSearchWindow();
        void setSearchWindow(std::string searchWindow);
        static long long hash(std::string stringToHash); //find the hash value of a string or substring
        static void output(std::string searchString, std::list<int> foundIndexes, int count);
        void search(); //search the file or input string for the search string
};

#endif

// searchString = "TEST"
// inputString = "2-934-290382-034TEST3498-23894-2"
//
// result "Appears at index 16"