//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashOpenAddressing.cpp
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"

using namespace std;

int split2(string array, char delimeter, string arr[], int size)
{
    string strPiece = "";
    int i = 0;
    int length = array.length();
    int index = 0;
    while(i != length && index != size)
    {
        if (array[i] == delimeter)
        {
            arr[index] = strPiece;
            index ++;
            strPiece = "";
        }
        else
        {
            strPiece = strPiece + array[i];
        }
        if(i == length - 1)
        {
            if(strPiece != "")
            {
                arr[index] = strPiece;
                index++;
                strPiece = "";
            }
        }
        i++;
    }
    if(i != length && index == size)
    {
        return -1;
    }
    else
    {
        return index;
    }
}

HashOpenAddressing::HashOpenAddressing(int size)
{

}

HashOpenAddressing::~HashOpenAddressing()
{
    Course* current;
    for(int i = 0; i < hashTableSize; i++)
    {
        if(hashTable[i] != NULL)
        {
            delete hashTable[i];
        }
    }
}

int HashOpenAddressing::hash(int courseNumber)
{
    int i = 0;
    bool ToF = false;
    int place;
    while(ToF == false)
    {
        int index = ((courseNumber + (i * i)) % hashTableSize);
        if(hashTable[index] != NULL)
        {
            i++;
        }
        else if(hashTable[index] == NULL)
        {
            ToF = true;
            place = index;
        }
    }
    return place;
}

void HashOpenAddressing::bulkInsert(string filename)
{
    string dpt;
    string courseName2;
    string professorName;
    string professorID;
    string line;
    ifstream file;
    string pieces[7];
    int index;
    int year;
    int courseNumber2;
    int ops = 0;
    int numOfSearches = 0;
    int numOfCollisions = 0;
    file.open(filename);
    if (file.fail())
    {
        cout << "File could not open :(" << endl;
        return;
    }
    while (getline(file, line))
    {
        if (ops != 0)
        {
            split2(line , ',' , pieces, 7);
            index = hash(stoi(pieces[2]));
            year = stoi(pieces[0]);
            dpt = pieces[1];
            courseNumber2 = stoi(pieces[2]);
            courseName2 = pieces[3];
            professorName = pieces[5] + " " + pieces[6];
            professorID = pieces[4];
            profDb.addProfessor(professorID, professorName);
            Professor* courseProfessor = profDb.searchProfessor(professorID);
            Course *newCourse = new Course;
            newCourse -> year = year;
            newCourse -> department = dpt;
            newCourse -> courseNum = courseNumber2;
            newCourse -> courseName = courseName2;
            newCourse -> prof = courseProfessor;
            courseProfessor -> coursesTaught.push_back(newCourse);
            int newHash;
            int i = 1;
            if(hashTable[index] != NULL)
            {
                numOfCollisions++;
                newHash = (index + (i*i)) % hashTableSize;
                while(hashTable[newHash])
                {
                    numOfSearches++;
                    i++;
                    newHash = (newHash + (i*i)) % hashTableSize;
                    if(newHash > hashTableSize)
                    {
                        newHash = newHash - hashTableSize;
                    }
                    hashTable[newHash] = newCourse;
                }
            }
            else
            {
                numOfSearches++;
                hashTable[index] = newCourse;
            }
        }
        ops++;
    }
    cout << "(OPEN ADDRESSING) Hash Table populated" << endl;
    cout << "Collisions using open addressing: " << numOfCollisions << endl;
    cout << "search operations using open addressing: " << numOfSearches << endl;
}

void HashOpenAddressing::search(int courseYear, int courseNumber, string profId)
{
    int i = 1;
    bool ToF = false;
    while (ToF == false)
    {
        int hash = ((courseNumber + (i * i)) % hashTableSize);
        if(hashTable[hash] -> courseNum == courseNumber && hashTable[hash] -> year == courseYear && hashTable[hash] -> prof -> profId == profId)
        {
            cout << "Search operations using open addressing: " << i << endl;
            cout << hashTable[hash] -> year << " " << hashTable[hash] -> courseName << " " << hashTable[hash] -> courseNum << " " << hashTable[hash] -> prof -> profName << endl; 
        }
        else 
        {
            i++;
        }
    }
}

void HashOpenAddressing::displayAllCourses()
{
    for(int i = 0; i < hashTableSize; i++)
    {
        if(hashTable[i] != NULL)
        {
            Course *temp = hashTable[i];
            while(temp !=  NULL)
            {
                displayCourseInfo(temp);
                temp = temp -> next;
            }
        }
    }
}

void HashOpenAddressing::displayCourseInfo(Course *c)
{
	cout << c -> year << " " << c -> courseName << " " << c -> courseNum << " " << c -> prof -> profName << endl;
}