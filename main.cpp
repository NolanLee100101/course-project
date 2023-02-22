//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: main.cpp
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"
#include "HashChaining.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main (int argc, char* argv[])
{
    if(argv[1] != NULL && argv[2] != NULL)
    {
        string courseName2 = argv[1];
        int size = stoi(argv[2]);
        HashChaining ChashTable(size);
        HashOpenAddressing OAhashTable(size);
        char choice;
        while(choice != '5')
        {
            cout << "=== Main Menu ===" << endl;
            cout << "1. Populate the hash tables" << endl;
            cout << "2. Search for a course" << endl;
            cout << "3. Search for a professor" << endl;
            cout << "4. Display for a profesor" << endl;
            cout << "5. Exit" << endl;
            cin >> choice;
            if(choice > '5' || choice < '1' || !choice)
            {
                cout << "Invalid input, please choose a number between 1 and 5" << endl;
            }
            else if(choice == '1')
            {
                cout << endl;
                ChashTable.bulkInsert(courseName2);
                cout << endl;
                OAhashTable.bulkInsert(courseName2);
            }
            else if(choice == '2') 
            {
                int year;
                int courseNumber2;
                string ID;
                cout << "Enter the course year: " << endl;
                cin >> year;
                cout << "Enter the course number: " << endl;
                cin >> courseNumber2;
                cout << "Enter a professor's name: " << endl;
                cin >> courseNumber2;
                cout << "Enter a professor's ID: " << endl;
                cin >> ID;
                cout << "[OPEN ADDRESSING] Search for a course" << endl;
                OAhashTable.search(year, courseNumber2, ID);
                cout << endl;
                cout << "[CHAINING] Search for a course" << endl;
                ChashTable.search(year, courseNumber2, ID);
            }
            else if(choice == '3')
            {
                string ID2;
                cout << "Enter a professor's ID" << endl;
                cin >> ID2;
                cout << "[OPEN ADDRESSING] Search for a professor" << endl;
                OAhashTable.profDb.publicSearchProfessor(ID2);
                cout << "[CHAINING] Search for a professor" << endl;
                ChashTable.profDb.publicSearchProfessor(ID2);
            }
            else if(choice == '4')
            {
                char OC;
                cout << "Which hash table do you want to display the courses? (O = Open Addressing C = Chainging)" << endl;
                cin >> OC;
                if(OC == 'O')
                {
                    cout << "[OPEN ADDRESSING] displayAllCourses()" << endl;
                    OAhashTable.displayAllCourses();
                }
                else if (OC == 'C')
                {
                    cout << "[CHAINGING] displayAllCourses()" << endl;
                    ChashTable.displayAllCourses();
                }
                else
                {
                    cout << " Invalid input please enter O or C" << endl;
                }
            }
            else if(choice == '5')
            {
                cout << "Goodbye" << endl;
            }
        }
    }
    return 0;
}