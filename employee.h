/* Malcolm Morton, Troy Davenport
 * 11/9/20
 * CSCE 2110.004
 *
 * Hash Function: Modulo hash function
 * Collision Stategy: Double hash
 *
 * Declaration of the Employee hash functions.
 * employee.h
 */
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <regex>
using namespace std;

class EItem
{
    public:
        int empId, deptId;
        string firstName, lastName, phone, salary, job, email, s;
   
        bool emptySinceStart = true;
        bool emptyAfterRemoval = false;
};

class Employee
{
    public:
        int HASH1(int key, int ts)
        {
            return key % 100;
        }
        int HASH2(int key, int ts)
        {
            return 110 - key % 110;
        }

        void INITIALIZE( EItem hashTable[], EItem temp, int);
        void INSERT(EItem hashTable[],string col[], int, string);
        void UPDATE(EItem hashTable[],string col[],int, string);
        void SELECT(EItem hashTable[], int, string);
        void DISPLAY(EItem hashTable[],string col[], int);
        void DELETE(EItem hashTable[], int, string);
        void WRITE(EItem hashTable[], int, string, string);
        
};
