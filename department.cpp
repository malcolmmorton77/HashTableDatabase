
/*Author(s):  Malcolm Morton
 *Professor:  Utpal Kumar-Dey
 *Date:       11/06/2020
 *Description:defines all funcitons used by dept hashTable
 *
 *Hash Function: Mid-square Base 2
 *Collision Stategy: Quadratic Probing
*/

#include "department.h"

int Department::hashFunc(int key, int size){
    int R = 4;                                      //4 >= log(size)
    if(R >= log10(size)){
        int index = key * key;                      //square the key
        int lBits = (32 - R) / 2;                   //gets the left bits to be shifted
        int eBits = index >> lBits;                 //shifts the number of bits to the right
        eBits = eBits & (0xFFFFFFFF >> (32 - R));   //logically ANDs the two statements together so that you keep only the R digits
        return eBits % size;                        //returns result divided by tablesize
    }
}

bool Department::initializeTable(DItem hashTable[], int ts, DItem temp){
    int index = hashFunc(temp.deptId, ts);              //locate the index using the hashFunc
    int probed = 0, i = 1;

    while(probed < ts){                             //identical to the insert function, just without the parsing of tuple
        if(hashTable[index].emptySinceStart || hashTable[index].emptyAfterRemoval){
            hashTable[index] = temp;
            hashTable[index].emptySinceStart = false;
            hashTable[index].emptyAfterRemoval = false;
            return true;			   //return true if placed in the table
        }
        index = (hashFunc(temp.deptId, ts) + i + i*i) % ts;
        i++;
        probed++;
    }
    if(probed == ts){
        return false;				  //return false if probed to the table size
    }
}

void Department::DISPLAY(DItem hashTable[], string col[], int ts)
{
    //print table name of specific table
    cout << "------------------------------------- Department -------------------------------------------\n"
         << "--------------------------------------------------------------------------------------------\n";

    // Make sure spacing is always consistent
    for(int i = 0; i < 5; i++){
        if(col[i] == "departId")
            cout << left << setw(15) << col[i];
        else if(col[i] == "name")
            cout << left << setw(15) << col[i];
        else if(col[i] == "location")
            cout << left << setw(15) << col[i];
        else if(col[i] == "mgrId")
            cout << left << setw(15) << col[i];
        else if(col[i] == "admrDepartId")
            cout << left << setw(15) << col[i]; 
    }

    cout << endl;
    //loop through the table and print out the values sequentially
    for(int i = 0; i < ts; i++){
        if(!hashTable[i].emptySinceStart && !hashTable[i].emptyAfterRemoval) {
            for(int j = 0; j < 5; j++){
                if(col[j] == "departId")
                    cout << left << setw(15) << hashTable[i].deptId;
                else if(col[j] == "name")
                    cout << left << setw(15) << hashTable[i].name;
                else if(col[j] == "location")
                    cout << left << setw(15) << hashTable[i].loc;
                else if(col[j] == "mgrId")
                    cout << left << setw(15) << hashTable[i].mgId;
                else if(col[j] == "admrDepartId"){
                    cout << left << setw(15) << hashTable[i].admnDeptId;
                }
            }
            cout << endl;
        }
    }
    
    return;
}

bool Department::INSERT(DItem hashTable[], string col[], int ts, string tuple){
    //parse tuple with regex
    int deptIdInt;
    string columns[5];

    //regex pattern for checking the validity of the tuple
    //regex pattern(".*,.*,.*,.*,.*");
    //if(regex_match(tuple, pattern)){
        smatch matcher;
	        //regex patterns for parsing the data into the DItem variable
        regex firstPatt("([^,]*),");
        regex secPatt(",([^,]*),");
        regex thrPatt(",.*,([^,]*),.*,");
        regex fourPatt(",.*,([^,]*),");
        regex fifPatt(",.*,([^,]*)");

	        //parse the first through fifth piece of data
        regex_search(tuple, matcher, firstPatt);
        columns[0] = matcher[1];
        regex_search(tuple, matcher, secPatt);
        columns[1] = matcher[1];
        regex_search(tuple, matcher, thrPatt);
        columns[2] = matcher[1];
        regex_search(tuple, matcher, fourPatt);
        columns[3] = matcher[1];
        regex_search(tuple, matcher, fifPatt);
        columns[4] = matcher[1];

        for(int i = 0; i < 5; i++)
            if(col[i] == "departId") //fix later with the value from sortBy
                deptIdInt = stoi(columns[i]);

        int index = hashFunc(deptIdInt, ts);
        int probed = 0, i = 1;

        while(probed < ts){                                         //continues as long as probed < tablesize
            if(hashTable[index].emptySinceStart || hashTable[index].emptyAfterRemoval){
                for(int j = 0; j < 5; j++){
                    if(col[j] == "departId")
                        hashTable[index].deptId = deptIdInt; //convert to the datatype that's usable for hashTable
                    else if(col[j] == "name")
                        hashTable[index].name = columns[j];
                    else if(col[j] == "location")
                        hashTable[index].loc = columns[j];
                    else if(col[j] == "mgrId")
                        hashTable[index].mgId = columns[j];
                    else if(col[j] == "admrDepartId")
                        hashTable[index].admnDeptId = columns[j];
                }
                hashTable[index].emptySinceStart = false;           //when found, change both empty values to false
                hashTable[index].emptyAfterRemoval = false;
                hashTable[index].s = tuple;			                //used as an overall tuple holder
                return true;                                        //return true for printing to main
            }
            index = (hashFunc(deptIdInt, ts) + i + i*i) % ts;
            probed++;
        }
        if(probed == ts){
            return false;
        }
    //}
    /*else*/
return false;
}

bool Department::UPDATE(DItem hashTable[], string col[], int ts, string tuple){
    //for updating, locate the tuple that needs to be updated
    int deptIdi;
    string cols[5];

    //get values from the string in the input files
    regex pattern1("([^,]*),");
    regex pattern2(",([^,]*),");
    regex pattern3(",.*,([^,]*),.*,");
    regex pattern4(",.*,([^,]*),");
    regex pattern5(",.*,([^,]*)");

    //poplulate the columns array with the matches from regex
    smatch matcher;
    regex_search(tuple, matcher, pattern1);
    cols[0] = matcher[0];
    regex_search(tuple, matcher, pattern2);
    cols[1] = matcher[0];
    regex_search(tuple, matcher, pattern3);
    cols[2] = matcher[0];
    regex_search(tuple, matcher, pattern4);
    cols[3] = matcher[0];
    regex_search(tuple, matcher, pattern5);
    cols[4] = matcher[0];

    for(int i = 0; i < 5; i++)
       if(col[i] == "departId") //fix later with the value from the sortBy
          deptIdi = stoi(cols[i]);

    for(int i = 0; i < ts; i++){
        //if key exists, proceed to change the other values
        if(!(hashTable[i].emptySinceStart) && !(hashTable[i].emptyAfterRemoval)){
            if(hashTable[i].deptId == deptIdi){
                //iterate through the department table's column values
                for(int j = 0; j < 5; j++){
                    if(col[j] == "departId")
                        hashTable[i].deptId = stoi(cols[j]);
                    else if(col[j] == "name")
                        hashTable[i].name = cols[j];
                    else if(col[j] == "location")
                        hashTable[i].loc = cols[j];
                    else if(col[j] == "mgrId")
                        hashTable[i].mgId = cols[j];
                    else if(col[j] == "admrDepartId")
                        hashTable[i].admnDeptId = cols[j];
                    
                    hashTable[i].s = tuple;
                    return true;
                }
            }
        }
    }
    //else return false because the value wasn't found
    return false;
}

bool Department::SELECT(DItem hashTable[], int ts, string tuple){
    //convert the temp string into a usable pattern and store in compare for regex functions
    regex pattern("\\*");
    string compare = regex_replace(tuple, pattern, ".*");

    //Iterate through the hash table use regex_match to compare the hashtable string to the compare string
    regex pattern2(compare);
    for(int i = 0; i < ts; i++){
        if(regex_match(hashTable[i].s, pattern2)){
            return true;		//if the tuple matches the compare tuple, return true
        }
    }
    return false;			//return false if the tuple doesn't match
}

bool Department::DELETE(DItem hashTable[], int ts, string tuple){
    //convert the temp into a usable pattern and store in compare
    regex patternConvert("\\*");
    string compare = regex_replace(tuple, patternConvert, ".*");

    //Iterate through the hashTable use regex_match to compare the hashTable string to compare string
    regex patternCompare(compare);
    for(int i = 0; i < ts; i++){
        if(regex_match(hashTable[i].s, patternCompare)){
            hashTable[i].deptId = 0;
            hashTable[i].loc = "";
            hashTable[i].name = "";
            hashTable[i].mgId = "";
            hashTable[i].admnDeptId = "";
            hashTable[i].emptyAfterRemoval = true; //set this value to true so it's available when hashing later on
            return true; //returns true for the print to main
        }
    }
    return false; //returns false if no tuple match
}

void Department::WRITE(DItem hashTable[], int ts, string line1, string line2){
    //open up an out stream for department_out.csv
    std::ofstream outFile("department_out.csv", std::ofstream::out);    //open an outstream
    outFile << line1 << "\n" << line2 << endl;
    string row, deptIds;

    //loop through array of data
    for(int i = 0; i < ts; i++){
        if(hashTable[i].deptId != 0){
            deptIds = std::to_string(hashTable[i].deptId);              //convert integer to string for data manipulation
            row = deptIds + "," + hashTable[i].name + ","               //create each row of data to be added to the stream
                    + hashTable[i].loc + "," + hashTable[i].mgId + ","
                    + hashTable[i].admnDeptId;
            outFile << row << "\n";                                     //add the row of data and a newline char
        }
    }

    outFile.close();                                                    //close the outstream
    return;
}
