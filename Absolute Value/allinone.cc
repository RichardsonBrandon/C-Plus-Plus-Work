/*Break down the program into 3 pieces - main.cpp, abs.cpp, abs.h similar to
the SomeApp.cpp example.  Also compile the codes by a make file
*/

#include <iostream>
using namespace std;


int Abs(int i); // Function prototype
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
// Function definition
int Abs(int i)
{
	if( i >= 0)
		return i;
	else
		return -i;
}
