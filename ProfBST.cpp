//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: ProfBST.cpp
//-----------------------------------------------------------------------------

#include "ProfBST.h"

#include <iostream>

using namespace std;

Professor* ProfBST:: searchKeyHelper(Professor* currentNode, string professorID)
{
    if(currentNode == NULL)
        return NULL;

    if(currentNode -> profId == professorID)
        return currentNode;

    if(currentNode -> profId > professorID)
        return searchKeyHelper(currentNode -> right, professorID);

    return searchKeyHelper(currentNode -> right, professorID);

}

Professor* ProfBST:: addNewNodeHelper(Professor* currentNode, string professorID, string professorName)
{   
    if(currentNode == NULL)
    {
        return createNode(professorID, professorName);
    }
    else if(currentNode -> profId < professorID)
    {
        currentNode -> right = addNewNodeHelper(currentNode->right, professorID, professorName);
    }
    else if(currentNode -> profId > professorID)
    {
        currentNode -> left = addNewNodeHelper(currentNode -> left, professorID, professorName);
    }
    return currentNode;
}

void ProfBST::deleteNode(Professor* currentNode)
{
    if(currentNode != NULL)
    {
        deleteNode(currentNode -> left);
        deleteNode(currentNode -> right);
        delete currentNode;
        currentNode= NULL;
    }
}

Professor* ProfBST:: createNode(string professorID, string professorName)
{
    Professor* newNode = new Professor;
    newNode -> profId = professorID;
    newNode -> profName = professorName; 
    newNode -> left = NULL;
    newNode -> right = NULL;
    return newNode;
}

ProfBST::ProfBST()
{
}

ProfBST::~ProfBST()
{
    deleteNode(root);
}

void ProfBST::addProfessor(string profId, string profName)
{
    root = addNewNodeHelper(root, profId, profName);
}

Professor* ProfBST::searchProfessor(string profId)
{
    Professor* tree = searchKeyHelper(root, profId);
    if(tree != NULL)
    {
        return tree;
    }
    else
    {
        return NULL;    
    }
}

void ProfBST::publicSearchProfessor(string profId)
{
    Professor* professor = searchProfessor(profId);
    if(professor != NULL)
    {
        displayProfessorInfo(professor);
    }
    else if(professor == NULL)
    {
        cout << "Professor ID does not mathc any professors" << endl;
    }
}

void ProfBST::displayProfessorInfo(Professor* p)
{
    cout << "Professor Name: " << p -> profName << endl;
    for(int i = 0; i < p -> coursesTaught.size(); i++)
    {
        cout << "-" << p -> coursesTaught[i] -> courseNum;
        cout << ":" << p -> coursesTaught[i] -> courseName;
        cout << "," << p -> coursesTaught[i] -> year << endl;
    }
}
