// Author: Brandon Richardson
// Date: 3/4/15 (Resubmission)
// Project Description:
// Create a program that allows the user to add numbers to a set,
// remove numbers from a set, clear the set, return the size of the set,
// and output the set.

#include <iostream>
#include <vector>
#include "NumberSet.h"
using namespace std;

int menu();
//Prompts the user with a menu

int menu_cases();
//Runs the users' chosen operation from the menu

int main()
{

   menu_cases();

   return 0;

}

int menu()
{
   int choice;

   cout << "\t\t1) Add an element to the set\n\n\t\t2) Remove and element from the set\n\t\t3) Clear the set\n\t\t"
   "4) Return the size of the set\n\t\t5) Print the set\n\t\t To perform an operation type 1,2,3,4, or 5 (enter 0 to quit): ";

   cin >> choice;

   while (choice != 1 && choice != 2 && choice != 3 && choice != 4
          && choice != 5 && choice != 0)
   {
      cout << "Invalid input. Valid inputs are 1,2,3,4,5, or 0.\n\n";
      cin >> choice;
   }

   return choice;
}

int menu_cases()
{
   int choice, a, found;
   NumberSet a_vector;
   do
   {
      choice = menu();

      switch(choice)
      {
        case 1:
            cout << "Enter an integer to add to the set.\n\n";
            cin >> a;
            found = a_vector.searchVector(a);
            if (found > -1)
               cout << "That number is already in the set.\n";
            else
                a_vector.add(a);
            break;

        case 2:
            cout << "Enter an integer to remove from the set.\n\n";
            cin >> a;
            a_vector.remove(a);
            break;

        case 3:
            a_vector.clear();
            break;

        case 4:
            a_vector.size();
            break;

        case 5:
            a_vector.output();
            break;

        case 0:
            cout << "\n\nGoodbye";
            break;

        default:
            cout << "You have entered an invalid input. Valid inputs are \n 1,2,3,4,5, or 0\n";
            break;
      }
   } while (choice != 0);
}
