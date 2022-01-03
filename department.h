
/*Author(s):  Malcolm Morton
 *Professor:  Utpal Kumar-Dey
 *Date:       11/06/2020
 *Description:declares the department hashTable class
 *
 *Hash Function: Mid-square Base 2
 *Collision Stategy: Quadratic Probing
*/

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>
#include <regex>

using namespace std;

class DItem{
    public:
        int deptId;
        string name, loc, mgId, admnDeptId, s;

        bool emptySinceStart = true;
        bool emptyAfterRemoval = false;
};

class Department{
    public:
        int hashFunc(int, int);
        bool initializeTable(DItem hashTable[], int, DItem);
        void DISPLAY(DItem hashTable[], string col[], int);
        bool INSERT(DItem[], string col[], int, string);
        bool UPDATE(DItem[], string col[], int, string);
        bool SELECT(DItem[], int, string);
        bool DELETE(DItem[], int, string);
        void WRITE(DItem[], int, string, string);
};