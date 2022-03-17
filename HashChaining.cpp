//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashChaining.cpp
//-----------------------------------------------------------------------------

#include "HashChaining.h"

using namespace std;

/*
HashOpenAddressing constructor
@param - table size
@return - none
*/
HashChaining::HashChaining(int size)
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
HashChaining::~HashChaining()
{
    int i = 0;
    while(i < hashTableSize)
    {
        if (hashTable[i])
        {
            Course* head = hashTable[i];
            while (head != NULL)
            {
                Course* temp = head;
                head = head->next;
                delete temp;
            }
        }
        i++;
    }
    delete[] hashTable;
}

/*
Hash calculator
@param - Course Number
@return - hash key
*/
int HashChaining::hash(int courseNumber)
{
    return (courseNumber % hashTableSize);
}

/*
HashChaining bulk insert
-read file info from a line and create course instance
-populate professor data base (profDb) and use profDb to create each course instance
-use collision chaining to fill buckets and linked lists
@param - file name
@return - void
*/
void HashChaining::bulkInsert(string filename)
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
                //course instance created

                int key = hash(currCourse->courseNum);
                if (hashTable[key] != NULL)
                {
                    collisionCount++;
                    searchCount++;
                }
                if (hashTable[key] == NULL)
                {  
                    hashTable[key] = currCourse;
                }
                else 
                {
                    Course* current = hashTable[key];
                    while (current->next != nullptr)
                    {
                        current = current->next;
                        searchCount++;
                    }
                    currCourse->previous = current;
                    current->next = currCourse;
                    currCourse->next = nullptr;
                }
            }
            i++;
        }
    }
    cout << "[CHAINING] Hash table populated" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Collisions using open addressing: " << collisionCount << endl;
    cout << "Search operations using chaining: " << searchCount << endl;
}

/*
HashChaining search for a course using collision chaining
@param - Course year, Course number, Professor ID
@return - void
*/
void HashChaining::search(int courseYear, int courseNumber, string profId)
{
    cout << "[CHAINING] Search for a course" << endl;
    cout << "----------------------------------------------" << endl;
    int key = hash(courseNumber);
    int j = 0;
    int searchCount2 = 0;
    Course* current = hashTable[key];
    if (!hashTable[key])
    {
        cout << "Course not found." << endl;
        return;
    } 
    while ((current->year != courseYear || current->prof->profId != profId) && current->next != nullptr)
    {
        current = current->next;
        searchCount2++;
    }
    if (current->year == courseYear && current->prof->profId == profId)
    {
        cout << "Search operations using chaining: " << searchCount2 << endl;
        cout << current->year << " " << current->courseName << " " << courseNumber << " " << current->prof->profName << endl;
    }
    else
    {
        cout << "Course not found." << endl;
        return;
    }
    
}

/*
HashChaining displays all courses
@param - none
@return - void
*/
void HashChaining::displayAllCourses()
{
    cout << "[CHAINING] displayAllCourses()" << endl;
    cout << "----------------------------------------------" << endl;
    int i = 0;
    while(i < hashTableSize)
    {
        if(hashTable[i])
        {
            while (hashTable[i]->next != nullptr)
            {
                displayCourseInfo(hashTable[i]);
                hashTable[i] = hashTable[i]->next;
            }
            displayCourseInfo(hashTable[i]);
        }
        i++;
    }
}

/*
HashChaining displays a single course instance info
@param - Course Node
@return - void
*/
void HashChaining::displayCourseInfo(Course* c)
{
    cout << c->year << " " << c->courseName << " " << c->courseNum << " " << c->prof->profName << endl;
}
