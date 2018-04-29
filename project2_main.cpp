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
 //  FILE:        project2_main.cpp
 //
 //  DESCRIPTION:
 //   This file contains the user interface functions and main function
 //   for the bank database application
 //
 //
 ****************************************************************/

#include "llist.h"
#include <iostream>
#include <string.h>

#ifndef DEBUGMODE
#define DEBUGMODE
#endif

/*****************************************************************
 //
 //  Function name: getAddress
 //
 //  DESCRIPTION:   Gets the user's address from the user
 //
 //  Parameters:    address (char[])    : Array to hold the address
 //                 maxCharacters (int) : Max characters allowed in
 //                                       the address
 //
 //  Return values: None
 //
 ****************************************************************/

void getAddress (char address[], int maxCharacters)
{
    char getsAddress[80] = "";
    char ** userAddress = &address;
    
    #ifdef DEBUGMODE
    {
        std::cout << "**DEBUG** Function: getAddress\n**DEBUG** Address: " << address << "\n**DEBUG** Maximum Address Character Length: " << maxCharacters << "\n";
    }
    #endif
    
    std::cout << "Please enter your address. When you are finished, enter 0 on a new line: ";
    
    std::cin.get(address, maxCharacters);
    std::cin.clear();
    std::cin.ignore(256, '\n');
    
    if (strlen(address) >= (unsigned)(maxCharacters - 1))
    {
        std::cout << "The address you entered is too long.\nPlease enter your address. When you are finished, enter 0 on a new line: ";
        
        memset(address, '\0', 80);
        std::cin.get(address, maxCharacters);
        std::cin.clear();
        std::cin.ignore(256, '\n');
    }
    
    while (strcmp(getsAddress, "0") != 0)
    {
        strcat(address, getsAddress);
        memset(getsAddress, '\0', 80);
        
        if (strlen(address) >= (unsigned)(maxCharacters - 1))
        {
            std::cout << "The address you entered is too long.\nPlease enter your address. When you are finished, enter 0 on a new line: ";
            
            memset(address, '\0', 80);
            std::cin.get(address, maxCharacters);
            std::cin.clear();
            std::cin.ignore(256, '\n');
        }
        
        std::cin.get(getsAddress, maxCharacters - strlen(address));
        std::cin.clear();
        std::cin.ignore(256, '\n');
        
        if (strcmp(getsAddress, "0") != 0)
        {
            strcat(address, "\n");
        }
    }
    *userAddress = address;
}

/*****************************************************************
 //
 //  Function name: getName
 //
 //  DESCRIPTION:   Gets the user's name from the user
 //
 //  Parameters:    name (char[])       : Array to hold the name
 //                 maxCharacters (int) : Max characters allowed in
 //                                       the address
 //
 //  Return values: none
 //
 ****************************************************************/

void getName (char name[], int maxCharacters)
{
    char ** userName = &name;
    
    #ifdef DEBUGMODE
    {
        std::cout << "**DEBUG** Function: getName\n**DEBUG** Name: " << name << "\n**DEBUG** Maximum Name Character Length: " << maxCharacters << "\n";
    }
    #endif
    
    std::cout << "Please enter your name: ";

    std::cin.get(name, maxCharacters);
    std::cin.clear();
    std::cin.ignore(256, '\n');
    
    while (strlen(name) >= (unsigned)(maxCharacters - 1))
    {
        std::cout << "The name you entered is too long.\nPlease enter your name: ";
        
        memset(name, '\0', 25);
        std::cin.get(name, maxCharacters);
        std::cin.clear();
        std::cin.ignore(256, '\n');
    }
    *userName = name;
}

/*****************************************************************
 //
 //  Function name: getAccountno
 //
 //  DESCRIPTION:   Gets the user's account number from the user
 //
 //  Parameters:    accountno (int &) : The user's account number
 //                                     that they entered
 //
 //  Return values: none
 //
 ****************************************************************/

void getAccountno (int & accountno)
{
    #ifdef DEBUGMODE
    {
        std::cout << "**DEBUG** Function: getAccountno\n**DEBUG** Account Number : " << accountno << "\n";
    }
    #endif
    
    std::cout << "Please enter your account number: ";
    
    std::cin >> accountno;
    std::cin.clear();
    std::cin.ignore(256, '\n');
    
    while (std::cin.fail() || accountno < 1)
    {
        std::cout << "You entered an invalid account number. Please enter a positive integer account number: ";
        std::cin >> accountno;
        std::cin.clear();
        std::cin.ignore(256, '\n');
        
    }
    
}

/*****************************************************************
 //
 //  Function name: main
 //
 //  DESCRIPTION:   Main function to run the program, a bank database
 //                 application
 //
 //  Parameters:    argc (int)    : the number of arguments passed
 //                 argv[] (char*): pointer array which points to each
 //                                 argument passed to the program
 //
 //  Return values:  0 : success
 //
 ****************************************************************/

int main(int argc, char* argv[])
{
    int userAccountNo = 0;
    char userName[25] = "";
    char userAddress[80] = "";
    int maxCharName = 25;
    int maxCharAddress = 80;
    int userMenuChoice = 10;
    char recordFile[] = "records.txt";
    char message[] = "Please select an option below by typing the corresponding number, followed by the enter key:\n 1: Add a record\n 2: Modify an existing record\n 3: Print a record\n 4: Print all records in the database\n 5: Delete an existing record\n 6: Reverse the order of the list\n 0: Quit the application\n\n";

    #ifdef DEBUGMODE
    {
        std::cout << "**DEBUG** Function: main\n**DEBUG** argc: " << argc << "\n**DEBUG** argv: " << argv << "\n";
    }
    #endif
    
    std::cout << "\nWelcome to the ICS212 Bank Database Application. Please look closely because our menu options may have changed.\n\n";
    
    llist list(recordFile);
    
    while (userMenuChoice != 0)
    {
        std::cout << message << "\n";
        std::cin >> userMenuChoice;
        std::cin.clear();
        
        switch (userMenuChoice)
        {
            case 1:
                getAccountno(userAccountNo);
                getName(userName, maxCharName);
                getAddress(userAddress, maxCharAddress);
                if (list.addRecord(userAccountNo, userName, userAddress) == 0)
                {
                    std::cout << "\nSuccessfully added your record!\n\n";
                }
                else
                {
                    std::cout << "\nThe account number you entered already exists. Please use a different account number and try again.\n\n";
                }
                break;
            case 2:
                getAccountno(userAccountNo);
                getAddress(userAddress, maxCharAddress);
                if (list.modifyRecord(userAccountNo, userAddress) == 0)
                {
                    std::cout << "\nSuccessfully updated your record!\n";
                    std::cout << "Your updated record is as follows:\n";
                    list.printRecord(userAccountNo);
                }
                else
                {
                    std::cout << "\nThere was an error trying to find your record to modify. Please make sure the account number you entered is correct and try again.\n";
                }
                std::cout << "\n";
                break;
            case 3:
                getAccountno(userAccountNo);
                if (list.printRecord(userAccountNo) == 0)
                {
                    std::cout << "\nSuccessfully printed your record!\n";
                }
                else
                {
                    std::cout << "\nThere was an error trying to find your record to print. Please make sure the account number you entered is correct and try again.\n";
                }
                std::cout << "\n";
                break;
            case 4:
                std::cout << "The contents of the database are as follows:\n\n";
                cout << list;
                break;
            case 5:
                getAccountno(userAccountNo);
                if (list.deleteRecord(userAccountNo) == 0)
                {
                    std::cout << "\nSuccessfully deleted your record!\n\n";
                }
                else
                {
                    std::cout << "\nThere was an error trying to find your record to delete. Please make sure the account number you entered is correct and try again.\n\n";
                }
                break;
            case 6:
                list.reverse();
                std::cout << "The order of records has been reversed.\n\n";
                break;
            case 0:
                std::cout << "Thank you for using the ICS212 Bank Database Application! Have a great day!\n";
                break;
            default:
                std:: cout<< "You entered an invalid menu option.\n";
                break;
        }
    }
    return 0;
}
