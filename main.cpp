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
    //Your main function should accept three command-line arguments: the program name, csv input file, and the hash table size. 
    if (!argv[1] || !argv[2] || !argv[3] || argv[4])
    {
        cout << "Invalid Number of Arguments." << endl;
        cout << "Usage: ./<program name> <csv file> <hashTable size>" << endl;
        return -1;
    }
    int M;
    M = stoi(argv[3]);
    bool loop = true;
    int response;

    HashOpenAddressing LeapCollision(M);
    HashChaining LLCollision(M);
    while (loop == true)
    {
        cout  << endl << "=======Main Menu=======" << endl;
        cout << "1. Populate hash tables" << endl;
        cout << "2. Search for a course" << endl;
        cout << "3. Search for a professor" << endl;
        cout << "4. Display all course" << endl;
        cout << "5. Exit" << endl;
        cout << endl;
        cin >> response;

        if (response == 1)
        {
                LeapCollision.bulkInsert(argv[2]);
                cout << endl; 
                LLCollision.bulkInsert(argv[2]);
        }
        if (response == 2)
        {
            string yearin;
            string numin;
            string pidin;
            cout << "Enter the course year (e.g. 2021):" << endl;
            cin >> yearin;
            cout << "Enter a course number (e.g 2270):" << endl;
            cin >> numin;
            cout << "Enter a Professor's ID (e.g. llytellf):" << endl;
            cin >> pidin;
            int year = stoi(yearin);
            int num = stoi(numin);
            LeapCollision.search(year,num,pidin);
            cout << endl;
            LLCollision.search(year,num,pidin);
        }
        if (response == 3)
        {
            string profidin;
            cout << "Enter a professor's ID (e.g.nscollan0):" << endl;
            cin >> profidin;
            LeapCollision.profDb.publicSearchProfessor(profidin);
            cout << endl;
            LLCollision.profDb.publicSearchProfessor(profidin);
        }
        if (response == 4)
        {
            string in;
            cout << "Which hash table would you like to display the courses for (O=Open Addressing, C=Chaining)?" << endl;
            cin >> in;
            if (in == "O")
            {
                LeapCollision.displayAllCourses();
            }
            if (in == "C")
            {
                LLCollision.displayAllCourses();
            }
        }
        if (response == 5)
        {
            loop = false;
        }
    }
    return 0;
}