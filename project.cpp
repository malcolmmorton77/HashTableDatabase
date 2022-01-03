
/*Author(s):  Anna Fortenberry, Malcolm Morton
 *Professor:  Utpal Kumar-Dey
 *Date:       11/06/2020
 *Description:defines the functions used by project hashTable
*/

#include "project.h"

void Project::INITIALIZE(PItem pList[], PItem temp, int projTableSize)
{
    int pos = midSquareHash(temp.projId, projTableSize);
    int probed = 0;
    while (probed < projTableSize)
    {
        if (pList[pos].emptySinceStart || pList[pos].emptyAfterRemoval)
        {
            pList[pos] = temp;  //note: emptySinceStart set to "false" in temp
            return;
        }
        pos = (pos + 1) % projTableSize;
        probed++;
    }
    return;
}

void Project::INSERT(PItem pList[], int projTableSize, string temp)
{
    //Need to convert project ID to integer for hash calculations
    int p_int;
    string p_id;

    //Get the Project ID from CSV File
    regex pattern1("([^,]*),");
    smatch matcher;
    regex_search(temp, matcher, pattern1);
    p_id = matcher[1];
    p_int = stoi(p_id);

    //Calculate Index
    int index = midSquareHash(p_int, projTableSize);
    int probed = 0;

    //Will iterate length of hash table
    while (probed < projTableSize)
    {
        if (pList[index].emptySinceStart || pList[index].emptyAfterRemoval)
        {
            //Storing data from file into patterns
            regex pattern2(",([^,]*),");
            regex pattern3(",[^,]*,([^,]*),");
            regex pattern4(",[^,]*,[^,]*,([^,]*),");
            regex pattern5(",[^,]*,[^,]*,[^,]*,([^,]*),");
            regex pattern6(",[^,]*,[^,]*,[^,]*,[^,]*,([^,]*)");

            //Store Project ID in Project Item
            pList[index].projId = p_int;

            //Store Employee ID in Project Item
            regex_search(temp, matcher, pattern2);
            pList[index].empId = matcher[1];

            //Store Project Name in Project Item
            regex_search(temp, matcher, pattern3);
            pList[index].projName = matcher[1];

            //Store Project Start Date in Project Item
            regex_search(temp, matcher, pattern4);
            pList[index].startDate = matcher[1];

            //Store Project End Date in Project Item
            regex_search(temp, matcher, pattern5);
            pList[index].endDate = matcher[1];

            //Store Employee Time in Project Item
            regex_search(temp, matcher, pattern6);
            pList[index].empTime = matcher[1];

            //Update Item Status and Output Success Message
            pList[index].emptySinceStart = false;
            pList[index].emptyAfterRemoval = false;
            pList[index].s = temp;
            cout << "Inserted (" << temp << ") into Project" << endl;
            return;
        }

        index = (index + 1) % projTableSize;
        probed++;
    }
    
    cout << "Failed to insert (" << temp << ") in Project" << endl;
    return;
}

void Project::UPDATE(PItem pList[], int projTableSize, string temp)
{
    //Need to convert project ID to integer for hash calculations
    int p_int;
    string p_id;

    //Get first item from the string inside the query
    regex pattern1("([^,]*),");
    smatch matcher;
    regex_search(temp, matcher, pattern1);
    p_id = matcher[1];
    p_int = stoi(p_id);

    int index = midSquareHash(p_int, projTableSize);
    int probed = 0;

    for (int i = 0; i < projTableSize; i++)
    {
        if (!(pList[i].emptySinceStart) && !(pList[i].emptyAfterRemoval))
        {
            if (pList[i].projId == p_int)
            {
                //Storing data from file into patterns
                regex pattern2(",([^,]*),");
                regex pattern3(",[^,]*,([^,]*),");
                regex pattern4(",[^,]*,[^,]*,([^,]*),");
                regex pattern5(",[^,]*,[^,]*,[^,]*,([^,]*),");
                regex pattern6(",[^,]*,[^,]*,[^,]*,[^,]*,([^,]*)");

                //Store Project ID in Project Item
                pList[index].projId = p_int;

                //Store Employee ID in Project Item
                regex_search(temp, matcher, pattern2);
                pList[index].empId = matcher[1];

                //Store Project Name in Project Item
                regex_search(temp, matcher, pattern3);
                pList[index].projName = matcher[1];

                //Store Project Start Date in Project Item
                regex_search(temp, matcher, pattern4);
                pList[index].startDate = matcher[1];

                //Store Project End Date in Project Item
                regex_search(temp, matcher, pattern5);
                pList[index].endDate = matcher[1];

                //Store Employee Time in Project Item
                regex_search(temp, matcher, pattern6);
                pList[index].empTime = matcher[1];

                //Update Item Status and Output Success Message
                pList[index].emptySinceStart = false;
                pList[index].emptyAfterRemoval = false;
                pList[index].s = temp;
                
                cout << "Updated (" << temp << ") in Project" << endl;
                return;
            }
        }
    }

    cout << "Failed to update (" << temp << ") in Project" << endl;
}

void Project::SELECT(PItem pList[], int projTableSize, string temp)
{
    //convert the temp string into a usable pattern and store in compare for regex functions
    regex pattern("\\*");
    string compare = regex_replace(temp, pattern, ".*");

    //Iterate through the hash table use regex_match to compare the hashtable string to the compare string
    regex pattern2(compare);
    for (int i = 0; i < projTableSize; i++)
    {
        if (regex_match(pList[i].s, pattern2))
        {
            cout << "Found (" << pList[i].s << ") in Project" << endl;
            return;
        }
    }

    cout << "No entries match query (" << temp << ") in Project" << endl;
}

void Project::DISPLAY(PItem pList[], int projTableSize)
{
    cout << "---------------------------------------- Project ---------------------------------------\n"
         << "----------------------------------------------------------------------------------------\n";
    
    cout << left << setw(15) << "Project Id" << left << setw(15) << "Employee Id"
         << left << setw(15) << "Project Name" << left << setw(15) << "Start Date"
         << left << setw(15) << "End Date" << left << setw(15) << "Employee Time";
    cout << endl;

    for(int i = 0; i < projTableSize; i++){

        if(!pList[i].emptySinceStart && !pList[i].emptyAfterRemoval) 
        {
            cout << left << setw(15) << pList[i].projId << left << setw(15) << pList[i].empId
                 << left << setw(15) << pList[i].projName << left << setw(15) << pList[i].startDate
                 << left << setw(15) << pList[i].endDate << left << setw(15) << pList[i].empTime << endl;
            //cout << "Hash Index: " << i << endl; uncomment to see where data is stored in hash table
        }
    }

    return;
}
