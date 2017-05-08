#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int menu();

int menu_cases();

class NumberSet
{
public:
   NumberSet();
   void add(int A);
   int searchVector(int A);
   void remove(int A);
   void clear();
   int size();
   void output();
private:
   vector<int> v;
};

int main()
{
    menu_cases();

    return 0;
}

int menu()
{
   int choice;

   cout << "1) Add an element to the set\n2) Remove and element from the set\n3) Clear the set\n"
   "4) Return the size of the set\n5) Print the set\nTo perform an operation type 1,2,3,4,"
   "or 5 (enter 0 to quit): \n";

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

NumberSet::NumberSet() : v(0)
{
// empty
}

void NumberSet::add(int A)
{
   v.push_back(A);
}

int NumberSet::searchVector(int A)
{
   for (int x = 0; x < v.size(); x++)
      if (v[x] == A)
         return x;
   return -1;
}

void NumberSet::remove(int A)
{
     for (int x = 0; x < v.size(); x++)

      if (v[x] == A)
        v.erase(v.begin() + x);

   cout << "\n";
}

void NumberSet::clear()
{
   v.clear();
}

int NumberSet::size()
{
   cout << v.size() << "\n\n";
}

void NumberSet::output()
{
   for (int x = 0; x < v.size(); x++)
      cout << v[x] << " ";
   cout << "\n";
}



