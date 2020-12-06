#ifndef STRING_SEARCH_I_H
#define STRING_SEARCH_I_H

#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <utility>
#include <chrono>

class Rabin_Karp {
     private :
        std::string inputString; // can be filename or string
        std::string searchString; //string you are searching for
        bool isFile; // determines if string describes the name of a file or just a search string
        std::string searchWindow;
        double t_out; // runtime duration
        std::string tag; // label of the object ex: "Rabin_Karp 1"
        int occurrences;
        std::string hashToGUI; // hash of the search string for output to GUI


     public :

        // constructor
        Rabin_Karp(std::string inputString, std::string searchString, bool isFile, bool isCaseSensitive); // constructor for looking through a txt file

        // getters and setters
        std::string getSearchWindow();
        void setSearchWindow(std::string &searchWindow);
        double getRunTime();
        void setRunTime(double t_out);
        std::string getTag();
        void setTag(std::string tag);
        int getOccurrences();
        void setOccurrences(int occurrences);
        std::string getHash();
        void setHash(std::string hashVal);

        // static functions
        static std::string processFile(std::string &filename);
        static long long hash(std::string &stringToHash); //find the hash value of a string or substring
        static void output(std::string &searchString, std::list<int> &foundIndexes, int &count, std::string &tag);
        static void countObjs();

        // static variables
        static int objCount;

        // object functions
        void findRunTime(std::chrono::steady_clock::time_point &t_start);
        void search(bool supressOutput); //search the file or input string for the search string

        // destructor
       ~Rabin_Karp();
};

class Boyer_Moore {
     private :
        std::string inputString; // can be filename or string
        std::string searchString; //string you are searching for
        bool isFile; // determines if string describes the name of a file or just a search string
        double t_out; // runtime duration
        int idx;
        std::string tag; // label of the object ex: "Boyer_Moore 1"
        int occurrences;
        std::string badCharTableHTML;

     public :
        //constructor
        Boyer_Moore(std::string inputString, std::string searchString, bool isFile, bool isCaseSensitive); // constructor for looking through a txt file

        //getters and setters
        double getRunTime();
        void setRunTime(double t_out);
        std::string getTag();
        void setTag(std::string tag);
        int getOccurrences();
        void setOccurrences(int occurrences);
        std::string getBadCharTableHTML();
        void setBadCharTableHTML(std::string badCharTableHTML);

        //static functions
        static std::string processFile(std::string &filename);
        static void output(std::string &searchString, std::list<int> &foundIndexes, int &count, std::string &tag);
        static int badChar(int idx, std::string &inputString, std::string searchString, std::list<int> &foundIndexes, int &count, int searchLength, std::vector<std::pair<char,int>> &badCharTable);
        static void generateBadCharTable(int searchLength, std::string &searchString, std::vector<std::pair<char,int>> &badCharTable);
        static void countObjs();

        // static variables
        static int objCount;

        //object functions
        void findRunTime(std::chrono::steady_clock::time_point &t_start);
        void search(bool surpressOutput); //search the file or input string for the search string

        // destructor
        ~Boyer_Moore();
};


#endif // STRING_SEARCH_I_H
