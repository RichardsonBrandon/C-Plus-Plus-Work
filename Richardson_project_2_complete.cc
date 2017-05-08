// -------------------------------------------------------------------
// FILE: 		[Richardson]_project_2.cc
// TITLE:		Project #2
// AUTHOR:		[Brandon Richardson]
// COURSE:		CSCI 2000 (C++)
// DATE:		[9/16/2014]
//
// PURPOSE:	The function of this code is to determine whether a number is prime or composite.
//          This code will also return a table of the factors of the numbers entered by the user.
//
// -------------------------------------------------------------------

#include <iostream>
using namespace std;

int main()
{
   int prompt, a, n, divisor, count, square_root;

   do
   {

    // Menu prompting the user for input

    cout << "\n";
    cout << "\n";
    cout << "Thank you for using Prime or Composite Tester.\n";
    cout << "\n";
    cout << "Type 1 and press enter to test a number for primality.\n";
    cout << "\n";
    cout << "Type 2 and press enter to enter a number to factor and receive the factors.\n";
    cout << "\n";
    cout << "Type 3 and press enter to exit the program.\n";
    cout << "\n";
    cin >> prompt;

   switch(prompt)
   {

   // Case 1 determines whether the number entered by the user is prime or composite.

   case 1:
    cout << "Type any number greater than 1 and press enter.\n";
    cout << "\n";
    cin >> n;

   if (n > 1)
   {
    a = 1;
    while (a * a <= n)
    a++;
    square_root = a - 1;

   count = 0;
   for (divisor = 2; divisor <= square_root; divisor++)

   if (n % divisor == 0)
    count++;

   // If the number is prime count++ would never occur making count = 0

   if (count == 0)
    cout << "Your number " << n << " is prime.\n";

   else
    cout << "Your number " << n << " is composite.\n";

   }
   else
   {
    cout << "The number entered is not greater than 1.\n";
    cout << "Try again.\n";
   }

   break;

   // Case 2 factors the number entered by the user and outputs the factors into a table.

   case 2:
    cout << "Type any number greater than 1 and press enter.\n";
    cin >> n;

   if (n > 1)
   {
    cout << "The factors of your number " << n << " are : \n";
    cout << "\n";

   // A counter here will help with creating a table because once the
   // counter hits a number divisible by 3, a new line will be created.
   // A tab has also been entered to space out each factor evenly.

   count = 0;
   for (divisor = 1; divisor <= n; divisor++)
   {
    while (n % divisor == 0)
    {
    cout << "\t" << divisor;
    count++;
    divisor++;
    if (count % 3 == 0)
    cout << "\n";
    }
   }

   }
   else
   {
    cout << "The number entered is not greater than 1.\n";
    cout << "Try again.\n";
   }
   break;

   // Case 3 exits the program

   case 3:
    cout << "Exiting Program\n";
   break;

   // Default will tell the user the number they entered is invalid.

   default:
    cout << "Invalid input.\n";
    }
   }
   while (prompt != 3);

   return 0;

}

