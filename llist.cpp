/*****************************************************************
 //
 //  NAME:        Paul Snieder
 //
 //  HOMEWORK:    Project 2
 //
 //  CLASS:       ICS 212
 //
 //  INSTRUCTOR:  Ravi Narayan
 //
 //  DATE:        November 18, 2017
 //
 //  FILE:        llist.cpp
 //
 //  DESCRIPTION:
 //   This file contains the function definitions for the llist class
 //
 //
 ****************************************************************/

#include "llist.h"
#include "record.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>

#ifndef DEBUGMODE
#define DEBUGMODE
#endif

using namespace std;

/*****************************************************************
 //
 //  Function name:  llist::llist
 //
 //  DESCRIPTION:    Contructor for llist class
 //
 //  Parameters:     None
 //
 //  Return values:  None
 //
 ****************************************************************/

llist::llist()
{
    this->start = NULL;
    strcpy(this->filename,"records.txt");
    readfile();
}

/*****************************************************************
 //
 //  Function name:  llist::llist
 //
 //  DESCRIPTION:    Contructor for llist class
 //
 //  Parameters:     filename (char[]): The file to read initial
 //                                     records from
 //
 //  Return values:  None
 //
 ****************************************************************/

llist::llist(char filename[])
{
    this->start = NULL;
    strcpy(this->filename,filename);
    readfile();
}

/*****************************************************************
 //
 //  Function name:  llist::llist
 //
 //  DESCRIPTION:    Copy contructor for llist class
 //
 //  Parameters:     list (llist&) : llist object to copy
 //
 //  Return values:  None
 //
 ****************************************************************/

llist::llist(const llist & list)
{
    this->start = list.start;
    strcpy(this->filename,list.filename);
    readfile();
}

/*****************************************************************
 //
 //  Function name:  llist::~llist
 //
 //  DESCRIPTION:    Destructor for llist class
 //
 //  Parameters:     None
 //
 //  Return values:  None
 //
 ****************************************************************/

llist::~llist()
{
    writefile();
    cleanup();
}

/*****************************************************************
 //
 //  Function name: llist::addRecord
 //
 //  DESCRIPTION:   Adds a record containing an account number, name,
 //                 and address to the database
 //
 //  Parameters:    accountno (int)   : The acount number of the person
 //                 name (char[])     : The name of the person
 //                 address (char[])  : The address of the person
 //
 //  Return values:  0 : success
 //                 -1 : failure
 //
 ****************************************************************/

int llist::addRecord(int accountno, char name[], char address[])
{
    int ret;
    record * recordToAdd;
    record * temp;
    
    temp = start;
    ret = 0;
    
    #ifdef DEBUGMODE
    {
        std::cout << "**DEBUG** Function: addRecord\n**DEBUG** Account Number: " << accountno << "\n**DEBUG** Name: " << name << "\n**DEBUG** Address: " << address << "\n";
    }
    #endif
    
    while (temp != NULL)
    {
        if (accountno == (*temp).accountno)
        {
            ret = -1;
        }
        
        temp = (*temp).next;
    }
    
    if (start == NULL)
    {
        recordToAdd = new record();
        start = recordToAdd;
        (*recordToAdd).accountno = accountno;
        strcpy((*recordToAdd).name, name);
        strcpy((*recordToAdd).address, address);
        (*recordToAdd).next = NULL;
    }
    else if (ret == 0)
    {
        recordToAdd = new record();
        temp = start;
        
        while ((*temp).next != NULL)
        {
            temp = (*temp).next;
        }
        
        (*temp).next = recordToAdd;
        (*recordToAdd).accountno = accountno;
        strcpy((*recordToAdd).name, name);
        strcpy((*recordToAdd).address, address);
        (*recordToAdd).next = NULL;
    }
    else
    {
        ret = -1;
    }
    
    return ret;
}

/*****************************************************************
 //
 //  Function name: llist::printRecord
 //
 //  DESCRIPTION:   Prints the record with account number "accountno"
 //
 //  Parameters:    accountno (int) : The acount number of the person
 //
 //  Return values:  0 : success
 //                 -1 : failure
 //
 ****************************************************************/

int llist::printRecord(int accountno)
{
    int ret = -1;
    record * temp = start;
    
    #ifdef DEBUGMODE
    {
        std::cout << "**DEBUG** Function: printRecord\n**DEBUG** Account Number: " << accountno << "\n";
    }
    #endif
    
    while (temp != NULL)
    {
        if (accountno == (*temp).accountno)
        {
            ret = 0;
            std::cout << "\nAccount Number: " << (*temp).accountno << "\n";
            std::cout << "Name: " << (*temp).name << "\n";
            std::cout << "Address: " << (*temp).address << "\n";
        }
        
        temp = (*temp).next;
    }
    
    return ret;
}

/*****************************************************************
 //
 //  Function name: llist::modifyRecord
 //
 //  DESCRIPTION:   Modifies the address field of the record with account
 //                 number "accountno"
 //
 //  Parameters:    accountno (int)   : The acount number of the person
 //                 address (char[])  : The address of the person
 //
 //  Return values:  0 : success
 //                 -1 : failure
 //
 ****************************************************************/

int llist::modifyRecord(int accountno, char address[])
{
    int ret = -1;
    record * temp = start;
    
    #ifdef DEBUGMODE
    {
        std::cout << "**DEBUG** Function: modifyRecord\n**DEBUG** Account Number: " << accountno << "\n**DEBUG** Address: " << address << "\n";
    }
    #endif
    
    while (temp != NULL)
    {
        if (accountno == (*temp).accountno)
        {
            ret = 0;
            strcpy((*temp).address, address);
        }
        
        temp = (*temp).next;
    }
    
    return ret;
}

/*****************************************************************
 //
 //  Function name: llist::deleteRecord
 //
 //  DESCRIPTION:   Deletes the record with account number "accountno"
 //
 //  Parameters:    accountno (int)  : The acount number of the person
 //
 //  Return values:  0 : success
 //                 -1 : failure
 //
 ****************************************************************/

int llist::deleteRecord(int accountno)
{
    #ifdef DEBUGMODE
    {
        std::cout << "**DEBUG** Function: deleteRecord\n**DEBUG** Account Number: " << accountno << "\n";
    }
    #endif
    
    int ret;
    record * recordToDelete;
    record * temp;
    
    recordToDelete = start;
    temp = start;
    ret = -1;
    
    while (recordToDelete != NULL)
    {
        if ((*recordToDelete).accountno == accountno)
        {
            ret = 0;
            
            if (recordToDelete == start)
            {
                start = (*recordToDelete).next;
                temp = start;
            }
            else
            {
                while ((*temp).next != recordToDelete)
                {
                    temp = (*temp).next;
                }
                
                (*temp).next = (*recordToDelete).next;
            }
            
            delete recordToDelete;
            recordToDelete = temp;
        }
        
        if (temp != NULL)
        {
            recordToDelete = (*recordToDelete).next;
        }
    }
    
    return ret;
}

/*****************************************************************
 //
 //  Function name:  llist::reverse
 //
 //  DESCRIPTION:    Reverse the order of this list
 //
 //  Parameters:     None
 //
 //  Return values:  None
 //
 ****************************************************************/

void llist::reverse()
{
    #ifdef DEBUGMODE
    {
        std::cout << "**DEBUG** Function: reverse\n";
    }
    #endif
    
    start = reverse(start);
    
}

/*****************************************************************
 //
 //  Function name:  operator <<
 //
 //  DESCRIPTION:    Overloads the << operator to print the entire
 //                  contents of the database
 //
 //  Parameters:     os (ostream): The output stream
 //                  list (llist): The list to print
 //
 //  Return values:  The entire contents of the database
 //
 ****************************************************************/

ostream& operator << (ostream& os, const llist& list)
{
    record * temp = list.start;
    
    while (temp != NULL)
    {
        os << "Account Number: " << (*temp).accountno << "\n";
        os << "Name: " << (*temp).name << "\n";
        os << "Address: " << (*temp).address << "\n";
        os << "\n";
        
        temp = (*temp).next;
    }
    
    return os;
}

/*****************************************************************
 //
 //  Function name:  llist::reverse
 //
 //  DESCRIPTION:    Helper function for the public reverse function
 //
 //  Parameters:     record (record *) : Pointer to the record database
 //
 //  Return values:  New start of the list
 //
 ****************************************************************/

record* llist::reverse(record * head)
{
    record * ret;
    record * list;
    
    #ifdef DEBUGMODE
    {
        std::cout << "**DEBUG** Function: reverse\n**DEBUG** Pointer to database: " << head << "\n";
    }
    #endif
    
    if (head == NULL || (*head).next == NULL)
    {
        ret = head;
    }
    else
    {
        list = reverse((*head).next);
        (*(*head).next).next = head;
        (*head).next = NULL;
        ret = list;
    }
    
    return ret;

}

/*****************************************************************
 //
 //  Function name:  llist::readfile
 //
 //  DESCRIPTION:    Adds records read from a file to the database
 //
 //  Parameters:     None
 //
 //  Return values:  0 : success
 //                 -1 : failure
 //
 ****************************************************************/

int llist::readfile()
{
    int ret;
    string addressArray;
    string tempArray;
    record * recordToRead;
    record * temp;
    ifstream file;
    
    ret = 0;
    file.open(filename);
    
    #ifdef DEBUGMODE
    {
        std::cout << "**DEBUG** Function: readfile\n";
    }
    #endif
    
    if (file == NULL)
    {
        ret = -1;
    }
    
    while (file != NULL && getline(file, tempArray) != NULL)
    {
        recordToRead = new record();
        if (start == NULL)
        {
            start = recordToRead;
        }
        else
        {
            temp = start;
            while ((*temp).next != NULL)
            {
                temp = (*temp).next;
            }
            (*temp).next = recordToRead;
        }
        (*recordToRead).accountno = atoi(tempArray.c_str());
        getline(file, tempArray);
        strcpy((*recordToRead).name, tempArray.c_str());
        getline(file, addressArray);
        while ((getline(file, tempArray) != NULL) && (strcmp(tempArray.c_str(), "") != 0))
        {
            addressArray = addressArray + "\n" + tempArray;
        }
        
        strcpy((*recordToRead).address, addressArray.c_str());
        addressArray = "";
        (*recordToRead).next = NULL;
    }
    
    if (file != NULL)
    {
        file.close();
    }
    
    return ret;
}

/*****************************************************************
 //
 //  Function name:  llist::writefile
 //
 //  DESCRIPTION:    Writes records in the database to a file
 //
 //  Parameters:     None
 //
 //  Return values:  0 : success
 //                 -1 : failure
 //
 ****************************************************************/

int llist::writefile()
{
    int ret;
    record * temp;
    ofstream file;
    file.open(filename);
    
    ret = -1;
    temp = start;
    
    #ifdef DEBUGMODE
    {
        std::cout << "**DEBUG** Function: writefile\n";
    }
    #endif
    
    while (temp != NULL && file != NULL)
    {
        file << (*temp).accountno << "\n";
        file << (*temp).name << "\n";
        file << (*temp).address << "\n";
        file << "\n";
        
        temp = (*temp).next;
    }
    
    if (file != NULL)
    {
        ret = 0;
        file.close();
    }
    
    return ret;
}

/*****************************************************************
 //
 //  Function name:  llist::cleanup
 //
 //  DESCRIPTION:    Frees memory used by the list when finished
 //
 //  Parameters:     None
 //
 //  Return values:  None
 //
 ****************************************************************/

void llist::cleanup()
{
    #ifdef DEBUGMODE
    {
        std::cout << "**DEBUG** Function: cleanup\n";
    }
    #endif
    
    record * delTemp;
    
    while (start != NULL)
    {
        delTemp = (*start).next;
        delete start;
        start = delTemp;
    }
}
