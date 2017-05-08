#include <iostream>
#include "abs.h"
using namespace std;

int main()
{
	int number;
	int abs_number;

	cout << "This program finds the absolute value of an integer." << endl;
	cout << "Enter an integer (positive or negative): ";
	cin >> number;

	// Calling the function Abs()
	abs_number = Abs(number);
	cout << "The absolute value of " << number << " is " << abs_number;
	cout << endl;
	return 0;
}
