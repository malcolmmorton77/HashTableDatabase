
/*Author(s):  Troy Davenport
 *Professor:  Utpal Kumar-Dey
 *Date:       11/06/2020
 *
 *Description:defines the hash table functions
*/

#include "employee.h"
//move initial vector items into a hash table
void Employee::INITIALIZE(EItem hashTable[], EItem temp, int ts)
{
    //place the temporary EItem inside of the employee hash table
    int pos = HASH1(temp.empId, ts);
    int probed = 0;
    while(probed < ts)
    {
        if(hashTable[pos].emptySinceStart || hashTable[pos].emptyAfterRemoval)
        {
            hashTable[pos] = temp;
            return;
        }
        pos = (HASH1(temp.empId,ts) + probed*HASH1(temp.empId,ts)) % ts;
        probed++;
    }
    return;
}

//Add new data to the employee database if the employee ID is unique
void Employee::INSERT(EItem hashTable[], string col[], int ts, string temp)
{
    int eint, dpint;
    string c[8];

    //get values from the string in the input file
    regex pattern1("([^,]*),");
    regex pattern2(",([^,]*),");
    regex pattern3(",[^,]*,([^,]*),");
    regex pattern4(",[^,]*,[^,]*,([^,]*),");
    regex pattern5(",[^,]*,[^,]*,[^,]*,([^,]*),");
    regex pattern6(",[^,]*,[^,]*,[^,]*,[^,]*,([^,]*),");
    regex pattern7(",[^,]*,[^,]*,[^,]*,[^,]*,[^,]*,([^,]*),");
    regex pattern8(",[^,]*,[^,]*,[^,]*,[^,]*,[^,]*,[^,]*,([^,]*)");

    smatch matcher;
    //populate column strings with regex pattern results
    regex_search(temp, matcher, pattern1);
    c[0] = matcher[1];
    regex_search(temp, matcher, pattern2);
    c[1] = matcher[1];
    regex_search(temp, matcher, pattern3);
    c[2] = matcher[1];
    regex_search(temp, matcher, pattern4);
    c[3] = matcher[1];
    regex_search(temp, matcher, pattern5);
    c[4] = matcher[1];
    regex_search(temp, matcher, pattern6);
    c[5] = matcher[1];
    regex_search(temp, matcher, pattern7);
    c[6] = matcher[1];
    regex_search(temp, matcher, pattern8);
    c[7] = matcher[1];

    for(int i = 0; i < 8; i++)
    {
        if(col[i] == "empId")
        {
           eint = stoi(c[i]);
        }
    }

    int pos = HASH1(eint, ts);
    int probed = 0;

    while(probed < ts)
    {
	//insert only if the table key is emptyx
        if(hashTable[pos].emptySinceStart || hashTable[pos].emptyAfterRemoval)
        {
	    for(int j = 0; j < 8; j++)
	    {
            if(col[j] == "empId")
                hashTable[pos].empId = eint;
            else if(col[j] == "firstName")
                hashTable[pos].firstName = c[j];
            else if(col[j] == "lastName")
                hashTable[pos].lastName = c[j];
            else if(col[j] == "phone")
                hashTable[pos].phone = c[j];
            else if(col[j] == "salary")
                hashTable[pos].salary = c[j];
            else if(col[j] == "job")
                hashTable[pos].job = c[j];
            else if(col[j] == "email")
                hashTable[pos].email = c[j];
            else if(col[j] == "departId")
            {
                dpint = stoi(c[j]);
                hashTable[pos].deptId = dpint;
            }
	    }
            //Update info for hash table and print out successful update
            hashTable[pos].emptySinceStart = false;
            hashTable[pos].emptyAfterRemoval = false;
            hashTable[pos].s = temp;
            cout << "Inserted (" << temp << ") into Employee" << endl;
            return;
        }

        pos = (HASH1(eint,ts) + probed*HASH2(eint,ts)) % ts;
        probed++;
    }

    cout << "Failed to insert (" << temp << ") in Employee" << endl;
    return;
}

//Alter values in the employee hashtable as long as the employee id is correct
void Employee::UPDATE(EItem hashTable[], string col[], int ts, string temp)
{
   int eint, dpint;
   string c[8];

   //get values from the string in the input file
   regex pattern1("([^,]*),");
   regex pattern2(",([^,]*),");
   regex pattern3(",[^,]*,([^,]*),");
   regex pattern4(",[^,]*,[^,]*,([^,]*),");
   regex pattern5(",[^,]*,[^,]*,[^,]*,([^,]*),");
   regex pattern6(",[^,]*,[^,]*,[^,]*,[^,]*,([^,]*),");
   regex pattern7(",[^,]*,[^,]*,[^,]*,[^,]*,[^,]*,([^,]*),");
   regex pattern8(",[^,]*,[^,]*,[^,]*,[^,]*,[^,]*,[^,]*,([^,]*)");

   smatch matcher;
   //populate column strings with regex pattern results
   regex_search(temp, matcher, pattern1);
   c[0] = matcher[1];
   regex_search(temp, matcher, pattern2);
   c[1] = matcher[1];
   regex_search(temp, matcher, pattern3);
   c[2] = matcher[1];
   regex_search(temp, matcher, pattern4);
   c[3] = matcher[1];
   regex_search(temp, matcher, pattern5);
   c[4] = matcher[1];
   regex_search(temp, matcher, pattern6);
   c[5] = matcher[1];
   regex_search(temp, matcher, pattern7);
   c[6] = matcher[1];
   regex_search(temp, matcher, pattern8);
   c[7] = matcher[1];

   //find the column that holds the key
   for(int i = 0; i < 8; i++)
   {
       if(col[i] == "empId")
       {
          eint = stoi(c[i]);
       }
   }

   //If the key exists in the table, proceed to change the other values
   for(int i = 0; i < ts; i++)
   {
       if(!(hashTable[i].emptySinceStart) && !(hashTable[i].emptyAfterRemoval))
       {
           if(hashTable[i].empId == eint)
           {
                //Iterate through the employee table's column values
                for(int j = 0; j < 8; j++)
                {
                    if(col[j] == "firstName")
                        hashTable[i].firstName = c[j];
                    else if(col[j] == "lastName")
                        hashTable[i].lastName = c[j];
                    else if(col[j] == "phone")
                        hashTable[i].phone = c[j];
                    else if(col[j] == "salary")
                        hashTable[i].salary = c[j];
                    else if(col[j] == "job")
                        hashTable[i].job = c[j];
                    else if(col[j] == "email")
                        hashTable[i].email = c[j];
                    else if(col[j] == "departId")
                    {
                        dpint = stoi(c[j]);
                    }
                }

                hashTable[i].s = temp;
                cout << "Updated (" << temp << ") in Employee" << endl;
                return;
           }
       }
   }

   cout << "Failed to update (" << temp << ") in Employee" << endl;
}

void Employee::SELECT(EItem hashTable[], int ts, string temp)
{
    //convert the temp string into a usable pattern and store in compare for regex functions
    regex pattern("\\*");
    string compare = regex_replace(temp, pattern, ".*");

    //Iterate through the hash table use regex_match to compare the hashtable string to the compare string
    regex pattern2(compare);
    for(int i = 0; i < ts; i++)
    {
        if(regex_match(hashTable[i].s, pattern2))
        {
            cout << "Found (" << hashTable[i].s << ") in Employee" << endl;
            return;
        }
    }

    cout << "No entries match query (" << temp << ") in Employee" << endl;
}
//Output the data of the employee database
void Employee::DISPLAY(EItem hashTable[], string col[], int ts)
{
    // Output each item inside the employee hash table.
    cout << "---------------------------------------------------- Employee "
        << "---------------------------------------------------\n"
        << "-------------------------------------------------------------------------"
        << "----------------------------------------\n";

    // Make sure spacing is always consistent
    for(int i = 0; i < 8; i++)
    {
	if(col[i] == "empId")
	    cout << left << setw(9) << col[i];
	else if(col[i] == "firstName")
	    cout << left << setw(15) << col[i];
	else if(col[i] == "lastName")
	    cout << left << left << setw(15) << col[i];
	else if(col[i] == "phone")
	    cout << left << setw(15) << col[i];
	else if(col[i] == "salary")
	    cout << left << setw(15) << col[i];
	else if(col[i] == "job")
            cout << left << setw(15) << col[i];
	else if(col[i] == "email")
            cout << left << setw(21) << col[i];
	else if(col[i] == "departId")
            cout << left << setw(9) << col[i]; 
    }

    cout << endl;

    //Output the information of each object of vector made of EItems
    for(int i=0; i < ts; i++)
    {

        if(!hashTable[i].emptySinceStart && !hashTable[i].emptyAfterRemoval)
        {
            for(int j = 0; j < 8; j++)
    	    {
        	if(col[j] == "empId")
            	    cout << left << setw(9) << hashTable[i].empId;
        	else if(col[j] == "firstName")
            	    cout << left << setw(15) << hashTable[i].firstName;
        	else if(col[j] == "lastName")
            	    cout << left << left << setw(15) << hashTable[i].lastName;
        	else if(col[j] == "phone")
            	    cout << left << setw(15) << hashTable[i].phone;
       		else if(col[j] == "salary")
            	    cout << left << setw(15) << hashTable[i].salary;
        	else if(col[j] == "job")
                    cout << left << setw(15) << hashTable[i].job;
        	else if(col[j] == "email")
            	    cout << left << setw(21) << hashTable[i].email;
        	else if(col[j] == "departId")
                    cout << left << setw(9) << hashTable[i].deptId << endl;
    	    }
        }
    }

    return;
}

void Employee::DELETE(EItem hashTable[], int ts, string temp)
{
    //convert string in query into a usable regex pattern
    regex pattern("\\*");
    string compare = regex_replace(temp, pattern, ".*");

    //Look through the table to see if there is a match for the "compare regex pattern"
    regex pattern2(compare);
    for(int i = 0; i < ts; i++)
    {
        //zero out the values if the the string matches the regex pattern
        if(regex_match(hashTable[i].s, pattern2))
        {
           hashTable[i].empId = 0;
           hashTable[i].deptId = 0;
           hashTable[i].firstName = "";
           hashTable[i].lastName = "";
           hashTable[i].phone = "";
           hashTable[i].salary =  "";
           hashTable[i].job =  "";
           hashTable[i].email =  "";
           hashTable[i].emptyAfterRemoval = true;
           hashTable[i].s = "";

           //success message
           cout << "Deleted (" << hashTable[i].s << ") in Employee" << endl;
           return;
        }
    }
    //Failure  message
    cout << "Failed to delete (" << temp << ") in Employee" << endl;  
}

//Write the employee table to a new file
void Employee::WRITE(EItem hashTable[], int ts, string el1, string el2)
{   
    string data;

    //Open file called employee_out.csv
    ofstream outFile;
    outFile.open("employee_out.csv");
    
    //write the file key on the first line and the column order on the second line
    outFile << el1 << "\n";
    outFile << el2 << "\n";

    for(int i = 0; i < ts; i++)
    {
        //Make sure we don't write an empty item to the file
        if(hashTable[i].empId != 0)
        {
            outFile << hashTable[i].s << "\n";
        }
    }
    
    outFile.close();

    return;
}
