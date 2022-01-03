
/*Author(s):    Malcolm Morton, Anna Fortenberry
 *Professor:    Utpal Kumar-Dey
 *Date:         11/06/2020
 *Description:  Declares the project hash tables class to be used to store data for the project entity.
 * 
 *              Hash Function:  Mid-Square Base 10
 *              Collision:      Linear Probing
*/

#include <iostream>
#include <assert.h>
#include <iomanip>
#include <vector>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

class PItem
{
    public:
        int projId;
        string empId, projName, startDate, endDate, empTime, s;

        bool emptySinceStart = true;
        bool emptyAfterRemoval = false;
};

class Project
{
    public:

        /* Function:    Mid Square Base 10 Hash Function
        *  Description: This Function uses the Mid Square Base 10 Hash Function to return an index to store a value
        *  Paramters:   Integer Key, Inetegr Table Size
        *  Return:      Index to Store Data Value in Hash Table
        */
        int midSquareHash(int key, int projTableSize) 
        {
            int R = 2;                                          //2 >= log(size)
            if (R >= log10(projTableSize))
            {
                int index = key * key;                          //square the key
                string sindex = to_string(index);               //convert to string
                int rdig = ceil((sindex.size() - R) / 2);       //get number of digits to remove from right of R
                sindex.erase(sindex.size() - rdig, rdig);       //erase the digits from above statement
                int ldig = sindex.size() - R;                   //get number of digits to remove from left of R
                sindex.erase(0, ldig);                          //erase the digits from above statement
                return atoi(sindex.c_str()) % projTableSize;    //return the converted string to integer divided by size of table
            }
        }
        
        void INITIALIZE(PItem pList[], PItem temp, int);
        void INSERT(PItem pList[], int projTableSize, string temp);
        void UPDATE(PItem pList[], int projTableSize, string temp);
        void SELECT(PItem pList[], int projTableSize, string temp);
        void DISPLAY(PItem pList[], int projTableSize);
};