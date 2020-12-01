#ifndef __STRING_SEARCH_I_H__
#define __STRING_SEARCH_I_H__

#include <fstream>
#include <string>
#include <list>

class Rabin_Karp {
     private :
        std::string inputString; // can be filename or string
        std::string searchString; //string you are searching for
        bool isFile; // determines if string describes the name of a file or just a search string
        std::string searchWindow;
        int t_out; // runtime duration
        std::string tag; // label of the object ex: "Rabin_Karp 1"


     public :

        // constructor
        Rabin_Karp(std::string inputString, std::string searchString, bool isFile, bool isCaseSensitive); // constructor for looking through a txt file

        // getters and setters
        std::string getSearchWindow();
        void setSearchWindow(std::string &searchWindow);
        int getRunTime();
        void setRunTime(int t_out);

        // static functions
        static std::string processFile(std::string &filename);
        static long long hash(std::string &stringToHash); //find the hash value of a string or substring
        static void output(std::string &searchString, std::list<int> &foundIndexes, int &count, std::string &tag);
        static void countObjs();

        // static variables
        static int objCount;

        // object functions
        void findRunTime(auto &t_start);
        void search(bool supressOutput); //search the file or input string for the search string
};

class Boyer_Moore {
     private :
        std::string inputString; // can be filename or string
        std::string searchString; //string you are searching for
        bool isFile; // determines if string describes the name of a file or just a search string
        int t_out; // runtime duration
        int idx;
        std::string tag; // label of the object ex: "Boyer_Moore 1"

     public :
        //constructor
        Boyer_Moore(std::string inputString, std::string searchString, bool isFile, bool isCaseSensitive); // constructor for looking through a txt file

        //getters and setters
        int getRunTime();
        void setRunTime(int t_out);

        //static functions
        static std::string processFile(std::string &filename);
        static void output(std::string &searchString, std::list<int> &foundIndexes, int &count, std::string &tag);
        static int badChar(int idx, std::string &inputString, std::string searchString, std::list<int> &foundIndexes, int &count, int searchLength);
        static int calulateShiftsBadChar(int idx, char bad, std::string &searchString, int searchIdx, int searchLength);
        static void countObjs();

        // static variables
        static int objCount;

        //object functions
        void findRunTime(auto &t_start);
        void search(bool surpressOutput); //search the file or input string for the search string
};


#endif

// searchString = "TEST"
// inputString = "2-934-290382-034TEST3498-23894-2"
//
// result "Appears at index 16"