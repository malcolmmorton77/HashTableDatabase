/*Author(s):  Malcolm Morton, Troy Davenport, Anna Fortenberry
 *Professor:  Utpal Kumar-Dey
 *Date:	      11/06/2020
 *Description:facilitates all the high level input and calls to other files
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <regex>
#include <sstream>
#include <vector>

#include "employee.h"
#include "department.h"
#include "project.h"

using namespace std;

void employee(EItem hashTable[], string &csv, string t, string &el1, string &el2, int ts, string column[])
{
    string sort, line1, dline, eid, first, last, phone, salary, job, email, dpid; 
    
    cout << endl << csv  << " " << t << endl;
    cout << "Processing " << t << " table.\n";
    ifstream dbfile(csv);

    if(dbfile.is_open()){
        getline(dbfile, sort);
        el1 = sort;
        getline(dbfile, line1);
        el2 = line1;

        //obtain the name of each column
        stringstream s1(line1);
        getline(s1, column[0], ',');
        getline(s1, column[1], ',');
        getline(s1, column[2], ',');
        getline(s1, column[3], ',');
        getline(s1, column[4], ',');
        getline(s1, column[5], ',');
        getline(s1, column[6], ',');
        getline(s1, column[7], ',');
    
        //match the string with the correct item
        while(getline(dbfile, dline)){
            stringstream ss(dline);

            for(int i = 0; i < 8; i++)
            {
                if(column[i] == "empId")
                    getline(ss, eid, ',');
                else if(column[i] == "firstName")
                    getline(ss, first, ',');
                else if(column[i] == "lastName")
                    getline(ss, last, ',');
                else if(column[i] == "phone")
                    getline(ss, phone, ',');
                else if(column[i] == "salary")
                    getline(ss, salary, ',');
                else if(column[i] == "job")
                    getline(ss, job, ',');
                else if(column[i] == "email")
                    getline(ss, email, ',');
                else if(column[i] == "departId")
                    getline(ss, dpid, ',');
            }
            Employee tem;
            EItem temp;
            temp.empId = stoi(eid);
            temp.deptId = stoi(dpid);
            temp.firstName = first;
            temp.lastName = last;
            temp.phone = phone;
            temp.salary = salary;
            temp.job = job;
            temp.email = email;
            temp.emptySinceStart = false;
            temp.s = dline;

            tem.INITIALIZE(hashTable, temp, ts);
            cout << "Inserted (" << dline << ") into " << t << endl;
        } 
    }
}

void dept(DItem dTable[], string &csv, string t, string &dline1, string &dline2, int ts, string col[]){
    string dline, depId, name, loc, mgId, admnDeptId;
    Department init;

    cout << endl << csv << " " << t << endl;
    cout << "Processing " << t << " table.\n";
    ifstream dbfile(csv);

    if(dbfile.is_open()){
        getline(dbfile, dline1);
        getline(dbfile, dline2);

        //obtain the name of each column
        stringstream s1(dline2);
        getline(s1, col[0], ',');
        getline(s1, col[1], ',');
        getline(s1, col[2], ',');
        getline(s1, col[3], ',');
        getline(s1, col[4], ',');

        while(getline(dbfile, dline)){
            stringstream ss(dline);
            for(int i = 0; i < 8; i++)
            {
                if(col[i] == "departId")
                    getline(ss, depId, ',');
                else if(col[i] == "name")
                    getline(ss, name, ',');
                else if(col[i] == "location")
                    getline(ss, loc, ',');
                else if(col[i] == "mgrId")
                    getline(ss, mgId, ',');
                else if(col[i] == "admrDepartId")
                    getline(ss, admnDeptId, ',');
            }

            DItem temp;
            temp.deptId = stoi(depId);      //create a temporary DItem variable and fill with the received values
            temp.name = name;
            temp.loc = loc;
            temp.mgId = mgId;
            temp.admnDeptId = admnDeptId;
            temp.emptySinceStart = false;   //set emptysincestart to false, so it will register as filled when searching

            cout << "Inserted (" << dline << ") into " << t << endl;

            init.initializeTable(dTable, ts, temp); //add it to the hashTable
        }
    }
}

void project(PItem pList[], string& csv, string hashTitle, int tableSize) {
    string sort, line1, dline, projId, empId, projName, startDate, endDate, empTime;    //placeholders for data pertaining to project
    Project tem;    //temporary Project item

    cout << endl << csv << " " << hashTitle << endl;
    cout << "Processing " << hashTitle << " table.\n";
    ifstream dbfile(csv);

    if (dbfile.is_open()) {
        getline(dbfile, sort);
        getline(dbfile, line1);

        while (getline(dbfile, dline)) {
            stringstream ss(dline);
            getline(ss, projId, ',');
            getline(ss, empId, ',');
            getline(ss, projName, ',');
            getline(ss, startDate, ',');
            getline(ss, endDate, ',');
            getline(ss, empTime, ',');

            PItem temp;
            temp.projId = stoi(projId);
            temp.empId = empId;
            temp.projName = projName;
            temp.startDate = startDate;
            temp.endDate = endDate;
            temp.empTime = empTime;
            temp.emptySinceStart = false;

            tem.INITIALIZE(pList, temp, tableSize);
            cout << "Inserted (" << dline << ") into " << hashTitle << endl;
        }
    }
}

int main(){

    
    int initialSize = 30;               //initial size of department hashTable
    int empTableSize = 30;              //initial size of employee hashTable
    int projTableSize = 31;             //initial size of project hashTable
    string eColumn[8];
    string dColumn[5];
    string eline1 = "", eline2 = "";
    string dline1 = "", dline2 = "";
    string fname, line, line2, table, pattern, trash;	// Name of user's file name input
    string empcsv, empTitle, deptcsv, deptTitle, projcsv, projTitle, dis;
    EItem eTable[empTableSize];
    Employee efirst;
    DItem dTable[initialSize];
    Department dFirst;
    PItem pList[projTableSize];
    Project pFirst;

    cout << "Enter file name: ";
    //User is prompted for the file they wish to load in.
    //The while loop checks the file name. Copied from previous input file.

    while(fname.empty()){
        cin >> fname;
        cin.ignore();
        ifstream inputfile(fname);
        size_t found = fname.find(".txt");

    //asks user to retype their file name if file is not in directory or a text file
    if((found == string::npos) || !(inputfile.is_open()))
    {
        fname.clear();
        cout << "INPUT FILE DOES NOT EXIST..... EXITING\n";
	    return 0;
    }

        else if(inputfile.is_open()){
            

            inputfile >> empcsv;
            inputfile >> empTitle;
            inputfile >> deptcsv;
            inputfile >> deptTitle;
            inputfile >> projcsv;
            inputfile >> projTitle;

            //call separate functions to open the other files
            employee(eTable, empcsv, empTitle, eline1, eline2, empTableSize, eColumn);
            dept(dTable, deptcsv, deptTitle, dline1, dline2, initialSize, dColumn);
            project(pList, projcsv, projTitle, projTableSize);
        
            // Parse each line and put into variables for the function to use, the regex pattern
            // and the hash table the regex pattern will be used with.
            while(getline(inputfile, line))
            {
                stringstream ss(line);
                getline(ss, dis, '(' );
                getline(ss, trash, '(');
                getline(ss, pattern,')');
                getline(ss, trash, ',');
                getline(ss, table, ')');

                // call functions based on the value of the dis variable
                // Apparently switch statements don't like using strings for their cases
                // so I just used if statements. >:(
                if(dis == "DISPLAY")
                {
                       efirst.DISPLAY(eTable, eColumn, empTableSize);
                       dFirst.DISPLAY(dTable, dColumn, initialSize);
                       pFirst.DISPLAY(pList, projTableSize);

                       cout << endl;
                }      

                //INSERT Functions
                else if( dis ==  "INSERT")
                {
                    if(table == "employee")
                    {
                        efirst.INSERT(eTable, eColumn, empTableSize, pattern);
                    }

                    else if(table == "department")
                    {
                        //call department's insert function
                        if(dFirst.INSERT(dTable, dColumn, initialSize, pattern)){
                            cout << "Inserted (" << pattern << ") into Department\n";
                        }
                        else{
                            cout << "Failed to insert (" << pattern << ") into Department\n";
                        }
                    }

                    else if(table == "project")
                    {
                        pFirst.INSERT(pList, projTableSize, pattern);
                    }
                }//INSERT
                
                //UPDATE Functions
                else if(dis == "UPDATE")
                {
                    if(table == "employee")
                    {
                        efirst.UPDATE(eTable, eColumn, empTableSize, pattern);
                    }

                    else if(table == "department")
                    {
                        if(dFirst.UPDATE(dTable, dColumn, initialSize, pattern)){
                            cout << "Updated (" << pattern << ") in Department\n";
                        }
                        else{
                            cout << "Failed to update (" << pattern << ") in Department\n";
                        }
                    }

                    else if(table == "project")
                    {
                        pFirst.UPDATE(pList, projTableSize, pattern);
                    }

                }//UPDATE
                
                //SELECT Function
                else if(dis == "SELECT")
                {
                    if(table == "employee")
                    {
                        efirst.SELECT(eTable, empTableSize, pattern);
                    }

                    else if(table == "department")
                    {
                        if(dFirst.SELECT(dTable, initialSize, pattern)){
                            cout << "Found (" << pattern << ") in Department\n";
                        }
                        else{
                            cout << "No entries match query (" << pattern << ") in Department\n";
                        }
                        
                    }

                    else if(table == "project")
                    {
                        pFirst.SELECT(pList, projTableSize, pattern);
                    }

                }//SELECT

                else if(dis == "DELETE")
                {
                    if(table == "employee")
                    {
                        efirst.DELETE(eTable, empTableSize, pattern);
                    }

                    else if(table == "department")
                    {
                        if(dFirst.DELETE(dTable, initialSize, pattern)){
                            cout << "Deleted (" << pattern << ") in Department\n";
                        }
                        else{
                            cout << "Failed to delete (" << pattern << ") in Department\n";
                        }
                    }

                    else if(table == "project")
                    {
                        //pFirst.DELETE(pList, projTableSize, pattern);
                    }
                }
               
                //Project Function
                else if(dis ==  "PROJECT")
                {
                    cout << dis << endl << endl;
                }//PROJECT
                
                //WRITE Function
                else if(dis == "WRITE")
                {
                    cout << dis << endl << endl;
                    dFirst.WRITE(dTable, initialSize, dline1, dline2); //line1_2 is so that I can output the sortBy value and column headers
                    efirst.WRITE(eTable, empTableSize, eline1, eline2);
                    cout << "Processing Complete!\n\n";
                }//WRITE

            }// inputfile while loop

        }// if input file is open
    

        inputfile.close();
    }//while fname.empty()

	return 0;
}
