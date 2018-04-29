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
 //  FILE:        llist.h
 //
 //  DESCRIPTION:
 //   This file contains the llist class definition
 //
 //
 ****************************************************************/

#ifndef llist_h
#define llist_h

#include <iostream>
#include "record.h"

using namespace std;

class llist
{
private:
    record *    start;
    char        filename[16];
    int         readfile();
    int         writefile();
    record *    reverse(record * );
    void        cleanup();
    
public:
    llist();
    llist(char[]);
    llist(const llist&);
    ~llist();
    int addRecord (int, char [ ],char [ ]);
    int printRecord (int);
    int modifyRecord ( int, char [ ]);
    friend ostream& operator << (ostream&, const llist&);
    int deleteRecord(int);
    void reverse();
};

#endif /* llist_h */
