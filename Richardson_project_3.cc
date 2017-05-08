// -------------------------------------------------------------------
// FILE: 		[Richardson]_project_3.cc
// TITLE:		Project #3
// AUTHOR:		[Brandon Richardson]
// COURSE:		CSCI 2000 (C++)
// DATE:		[9/30/2014]
//
// PURPOSE:	The function of this code is to determine whether a number is prime or composite.
//          This code will also return a table of the factors of the numbers entered by the user.
//
// -------------------------------------------------------------------

#include <iostream>
using namespace std;

double validate_amount();


int main(double& money)
{
    cout << "Enter an amount: $ .\n";
    cin >> money;
    money = validate_amount(money);
}

double validate_amount(double money)
{

   while (money < 0)
   {
       cout << "Enter an amount greater than 0.\n";
       cin >> money;
   }
   return (money);
}
