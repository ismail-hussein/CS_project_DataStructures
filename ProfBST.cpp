//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: ProfBST.cpp
//-----------------------------------------------------------------------------

#include "ProfBST.h"

#include <iostream>

using namespace std;

/*
Constructor
@param - none
@return - none
*/
ProfBST::ProfBST()
{
    root = nullptr;
}

/*
Destructor helper function
@param - Professor node
@return - void
*/
void destroyNode(Professor *currNode)
{
    if(currNode!=NULL)
    {
        destroyNode(currNode->left);
        destroyNode(currNode->right);
        int i = 0;
        while(i < currNode->coursesTaught.size())
        {
            currNode->coursesTaught.pop_back();
            i++;
        }
         delete currNode;
    }
 }

/*
Destructor 
@param - none
@return - none
*/
ProfBST::~ProfBST()
{
    destroyNode(root);
}

/*
Add node to bst helper function
@param - Professor Root, Professor Node
@return - Professor Node
*/
Professor* addNodeHelper(Professor* root, Professor* currNode) 
{  
    if (root == NULL)   
    {
        return currNode;
    }
    if (root->profId <= currNode->profId) 
    {
        root->right = addNodeHelper(root->right, currNode);
    }
    if (root->profId >= currNode->profId)
    {
        root->left = addNodeHelper(root->left, currNode);
    }
    return root;
}

/*
Add node to bst function
@param - Professor ID, Professor Name
@return - void
*/
void ProfBST::addProfessor(string profId, string profName)
{
    Professor* currNode = new Professor(profId, profName);
    root = addNodeHelper(root, currNode);
}

/*
Search key helper function
@param - Professor Node, Professor ID
@return - Professor Node
*/
Professor* searchKeyHelper(Professor* currNode, string profId)
{
    if(currNode == NULL || currNode->profId == profId)
    {
        return currNode;
    }
    if(currNode->profId < profId)
    {
        return searchKeyHelper(currNode->right, profId);
    }
    return searchKeyHelper (currNode->left, profId);
}

/*
Search key function
@param - Professor ID
@return - Professor Node
*/
Professor* ProfBST::searchProfessor(string profId)
{
    Professor* hold = searchKeyHelper(root, profId);
    if (hold != nullptr)
    {
        return hold;
    }
    return NULL;
}

/*
Search professor function, public access
@param - Professor ID
@return - void
*/
void ProfBST::publicSearchProfessor(string profId)
{
    Professor* currProf = searchKeyHelper(root, profId);
    if (currProf == nullptr)
    {
        cout << "Professor not found." << endl;
    }
    else
    {
        displayProfessorInfo(currProf);
    }
    
}

/*
Display professor info
@param - Professor Node
@return - void
*/
void ProfBST::displayProfessorInfo(Professor* p)
{
    cout << "Name: " <<p->profName << endl;
    int i = 0;
    while (i < p->coursesTaught.size())
    {
        cout << "- " << p->coursesTaught[i]->courseNum << ": " << p->coursesTaught[i]->courseName << ", " << p->coursesTaught[i]->year << endl;
        i++;
    }
}
