//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashOpenAddressing.cpp
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"

using namespace std;

/*
HashOpenAddressing constructor
@param - table size
@return - none
*/
HashOpenAddressing::HashOpenAddressing(int size)
{
    this->hashTableSize = size;
    hashTable = new Course*[size];
    for(int i=0; i < size; i++)
    {
        hashTable[i] = nullptr;
    }
}

/*
HashOpenAddressing destructor
@param - none
@return - none
*/
HashOpenAddressing::~HashOpenAddressing()
{
    for(int i = 0; i < hashTableSize; i++)
    {
        hashTable[i] = nullptr;
        delete hashTable[i];
    }
    delete[] hashTable;
}

/*
Hash calculator
@param - Course Number
@return - hash key
*/
int HashOpenAddressing::hash(int courseNumber)
{
    return (courseNumber % hashTableSize);
}


/*
HashOpenAddressing bulk insert
-read file info from a line and create course instance
-populate professor data base (profDb) and use profDb to create each course instance
-use quadratic probing to fill buckets
@param - file name
@return - void
*/
void HashOpenAddressing::bulkInsert(string filename)
{
    //parse file, create course instance for every course, and insert each course one by one to respective hash table
    int i = 0;
    int collisionCount = 0;
    int searchCount = 0;
    ifstream inStream2;
    inStream2.open(filename);
    string line;
    if(!inStream2.is_open())
    {
        cout << "Unable to open file" << endl;
        return;
    }
    else
    {
        while (getline(inStream2, line) && i <=hashTableSize)
        {
            if (i > 0)
            {
                istringstream streamline;
                streamline.str(line); 

                //year
                string year;
                int year0;
                getline(streamline, year, ',');
                year0 = stoi(year);

                //dept
                string dept;
                getline(streamline, dept, ',');

                //course num
                string courseNum;
                int courseNum0;
                getline(streamline, courseNum, ',');
                courseNum0 = stoi(courseNum);

                //course name
                string courseName;
                getline(streamline, courseName, ',');

                //prof id
                string profID;
                getline(streamline, profID, ',');

                //prof first name
                string profFirstName;
                getline(streamline, profFirstName, ',');
                //prof last name

                string profLastName;
                getline(streamline, profLastName);
                string profFullName = profFirstName + " " + profLastName;

                //may segfault here, it is very rare just run the code again
                if (profDb.searchProfessor(profID) == NULL)
                {
                    profDb.addProfessor(profID, profFullName);
                }
                Professor* currNode = new Professor();
                currNode = profDb.searchProfessor(profID);
                Course* currCourse = new Course(year0, dept, courseNum0, courseName, currNode);
                currNode->coursesTaught.push_back(currCourse);

                int key = hash(currCourse->courseNum);
                int j = 1;
                if (hashTable[key] != NULL)
                {
                    collisionCount++;
                }
                while(hashTable[key] != NULL && j < hashTableSize)
                {
                    key = (key + (j * j)) % hashTableSize;
                    j++;
                    searchCount++;
                }
                if (hashTable[key] == nullptr)
                {
                    hashTable[key] = currCourse;
                }
            }
            i++;
        }
    }
    cout << "[OPEN ADDRESSING] Hash table populated" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Collisions using open addressing: " << collisionCount << endl;
    cout << "Search operations using chaining: " << searchCount << endl;
}

/*
HashOpenAddressing search for a course using quadratic probing
@param - Course year, Course number, Professor ID
@return - void
*/
void HashOpenAddressing::search(int courseYear, int courseNumber, string profId)
{
     cout << endl <<"[OPEN ADDRESSING] Search for a course" << endl;
    cout << "----------------------------------------------" << endl;
    int key = hash(courseNumber);
    int j = 0;
    int searchCount;
    while(hashTable[key]->year != courseYear || hashTable[key]->prof->profId != profId)
    {
        key = (key + (j * j)) % hashTableSize;
        j++;
        searchCount++;
        if (!hashTable[key] || j == (hashTableSize - 3))
        {
            cout << "Course not found." << endl;
            return;
        }
    }
    if (hashTable[key]->year == courseYear && hashTable[key]->prof->profId == profId && hashTable[key]->courseNum == courseNumber)
    {
        cout << "Search operations using open addressing: " << searchCount << endl;
        cout << hashTable[key]->year << " " << hashTable[key]->courseName << " " << courseNumber << " " << hashTable[key]->prof->profName << endl;
    }
    else
    {
        cout << "Course not found." << endl;
        return;
    }
}

/*
HashOpenAddressing displays all courses
@param - none
@return - void
*/
void HashOpenAddressing::displayAllCourses()
{
    cout << "[OPEN ADDRESSING] displayAllCourses()" << endl;
    cout << "----------------------------------------------" << endl;
    for(int i = 0; i < hashTableSize; i++)
    {
        if (hashTable[i])
        {
            displayCourseInfo(hashTable[i]);
        }
    }
}

/*
HashOpenAddressing displays a single course instance info
@param - Course Node
@return - void
*/
void HashOpenAddressing::displayCourseInfo(Course* c)
{
	cout << c->year << " " << c->courseName << " " << c->courseNum << " " << c->prof->profName << endl;
}