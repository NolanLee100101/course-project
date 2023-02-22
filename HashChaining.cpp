//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashChaining.cpp
//-----------------------------------------------------------------------------

#include "HashChaining.h"
 
using namespace std;

int split(string array, char delimeter, string arr[], int size)
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
 
HashChaining::HashChaining(int size)
{
    this -> hashTableSize = size;
    hashTable = new Course*[hashTableSize];
    for(int i = 0; i < hashTableSize; i++)  
    {
        hashTable[i] =  NULL;
    }
    int numOfCollisions = 0;
    int numItems = 0;
}
 
HashChaining::~HashChaining()
{ 
    Course* current;
    Course* current2;
        for(int i =  0; i < hashTableSize; i++)
        {
            if(hashTable[i] !=  NULL)
            {
                current  =  hashTable[i];
                while(current !=  NULL)
                {
                    current2 = current;
                    current =  current -> next;
                    delete current2;
                    current2 = NULL;
                }
            }
        }
}
 
int HashChaining::hash(int courseNumber)
{
    int hashI = (courseNumber % hashTableSize);
    return hashI;
}
 
void HashChaining::bulkInsert(string filename)
{
    int index;
    int numOfCollisions;
    int numOfSearches;
    int year;
    int courseNumber2;
    int ops;
    string courseName2;
    string professorName;
    string professorID;
    string category;
    string line;
    string pieces[7];
    ifstream fileName;
 
    fileName.open(filename);
    if(fileName.fail()){
        cout << "error opening file." << endl;
        return;
    }
    while(getline(fileName, line))
    {
        if(ops !=  0)
        {
           
            split(line, ',',pieces,7);
            index = hash(stoi(pieces[2]));
            profDb.addProfessor(professorID,professorName);
            Professor* classProf  =  profDb.searchProfessor(professorID);
            professorID = pieces[4];
            professorName =  pieces[5]+ " " + pieces[6];
            courseName2 = pieces[3];
            courseNumber2 = stoi(pieces[2]);
            category = pieces[1];
            year =  stoi(pieces[0]);
            Course* current1;
            Course* newClass = new Course;
            newClass -> prof = classProf;
            newClass -> courseName =  courseName2;
            newClass -> courseNum =  courseNumber2;
            newClass -> department =  category;
            classProf -> coursesTaught.push_back(newClass);
 
 
            if(hashTable[index])
            {
                numOfCollisions++;
                current1  = hashTable[index];
                while(current1 -> next != NULL)
                {
                    numOfSearches++;
                    current1 =  current1 -> next;
                }
                current1 -> next = newClass;
                newClass -> previous =  current1;
            }
            else
            {
                numOfSearches++;
                hashTable[index] = newClass;
            }
        }
        ops++;
    }
    cout << "[OPEN ADDRESSING] Hash table populated" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "Collisions using open addressing: " << numOfCollisions << endl;
    cout << "Search operations using open addressing: " << numOfSearches << endl;
    fileName.close();
}
 
void HashChaining::search(int courseYear, int courseNumber, string profId)
{
    int index = hash(courseNumber);
    int numSearch = 0;
     Course* temp  =  hashTable[index];
    if(hashTable[index] == NULL)
    {
        cout  <<  " No course(s) was/were found" << endl;
    }
        bool ToF = false;
        while(ToF == false)
        {
            if(temp -> courseNum  ==  courseNumber && temp -> year  ==  courseYear && temp -> prof -> profId  == profId){
                numSearch++;
                cout << "Search operations using chaining: " << numSearch << endl;
                cout << temp -> year  << " " << temp ->  courseName << " " << temp -> courseNum <<  " " << temp -> prof -> profName << endl;
                ToF = true;
            }
            else
            {
                temp = temp -> next;
                numSearch++;
                if(temp == NULL){
                    cout << "No course(s) was/were found " << endl;
                    ToF = true;
                }
            }
        }
}
 
 
void HashChaining::displayAllCourses()
{
    for(int i = 0; i< hashTableSize; i++)
    {
        if(hashTable[i] != NULL)
        {
            Course* temp = hashTable[i];
            while(temp !=  NULL)
            {
                displayCourseInfo(temp);
                temp = temp -> next;
            }
        }
    }
}
 
void HashChaining::displayCourseInfo(Course* c)
{
    cout <<  c -> year  << " " << c -> courseName << " " << c -> courseNum << " " << c -> prof -> profName << endl;
}

