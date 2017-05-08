#include<iostream>
using namespace std;

class NumberSet;

class ListElement
{
  private:
     int datum;
     ListElement* next;

  public:
     ListElement (int, ListElement*);

     int getDatum () const;
     ListElement const* getNext () const;

     friend class NumberSet;
};


class NumberSet
{
  private:
     ListElement* head;

  public:
     NumberSet ();
     void makeList();
     void add (int A);  //add integer to the set
     int searchSet(int A); //searches the set
     void remove (int A);  //deletes an integer from the set
     void printList ();   //print the set
     int count(); //counts the amount of values stored in the set
};

int menu();

int main()
{

   int choice, a, values, found;
   NumberSet x;

   x.makeList();
   do
   {
      choice = menu();

      switch(choice)
      {
      case 1:
	    cout << "\n\nEnter an integer to add to the set.\n\n";
	    cin >> a;
	    found = x.searchSet(a);
	    if (found == -1)
           x.add(a);
        else
           cout << "Number is already in the set.\n";
        break;

	  case 2:
        cout << "\n\nEnter an integer to remove from the set.\n\n";
        cin >> a;
	    x.remove(a);
	    break;

	  case 3:
        values = x.count();
        cout << "The set contains " << values << " values.\n";
	    break;

	  case 4:
	    cout << "\nThe set contains:";
	    x.printList();
	    cout << "\n\n";
	    break;

	  case 0:
        cout << "Goodbye.\n";
        break;

	  default:
	    cout<<"\n Invalid choice. Please try again.\n";
	    break;
      }
   } while (choice != 0);

   return 0;
}

int menu()
{
   int choice;

   cout << "1) Add an element to the set\n2) Remove and element from the set\n3) Return the size of the set\n"
   "4) Print the set\nTo perform an operation type 1,2,3, or 4 (enter 0 to quit): \n";

   cin >> choice;

   while (choice != 1 && choice != 2 && choice != 3 && choice != 4
           && choice != 0)
   {
      cout << "Invalid input. Valid inputs are 1,2,3,4,5, or 0.\n\n";
      cin >> choice;
   }

   return choice;
}

NumberSet::NumberSet():
    head (0)
{
// empty
}

ListElement::ListElement(int _datum, ListElement * _next):
   datum (_datum), next (_next)
{}

int ListElement::getDatum()const
{
   return datum;
}

ListElement const* ListElement::getNext()const
{
   return next;
}

int NumberSet::searchSet(int A)
{
   ListElement *currPtr = head;
   do
    {
       if (currPtr->datum == A)
       {
          return 1;
       }
      currPtr=currPtr->next;
    } while(currPtr->next!=NULL);
   return -1;
}


void NumberSet::add(int A)
{
  ListElement *tail = head;
  while(tail!=NULL)
  {
    if (tail->next==NULL) break;
    tail = tail->next;
  }
  tail->next = new ListElement(A, NULL);
}

void NumberSet::remove(int A)
{
  ListElement *PrevPtr = head;
  ListElement *currPtr = head->next;

  while(currPtr != NULL)
  {
        if(currPtr->datum == A)
        {
            break;
        }
        else
        {
            PrevPtr = currPtr;
            currPtr = currPtr->next;
        }
  }
   if(currPtr == NULL)
    {
        cout << "The number entered is not in the set.\n";
    }
   else
    {
        PrevPtr->next = currPtr->next;
        delete currPtr;
    }
}

void NumberSet::printList()
{
  ListElement *currPtr = head;
  cout << "\n";
  while (currPtr!=NULL)
  {
    cout << currPtr->datum<<" ";
    currPtr = currPtr->next;
  }
}

int NumberSet::count()
{
 ListElement *currPtr = head;
 int length = 0;

 while(currPtr != NULL)
 {
    length++;
    currPtr = currPtr->next;
 }
 return (length);
}

void NumberSet::makeList()
{
   int InValue;
   ListElement *currPtr;
   ListElement *newNodePtr;

   cout << "Enter values for your set. After entering a number press enter,\nand input your next number.\n";
   cout << "Enter -1 to end the list.\n";

   cin >> InValue;

   newNodePtr = new ListElement(InValue, NULL);
   head = newNodePtr;
   currPtr = head;
   cin >> InValue;

   while ( InValue != -1)
   {
     newNodePtr = new ListElement(InValue, NULL);
      currPtr->next = newNodePtr;
      currPtr = newNodePtr;
      cin >> InValue;
   }
}
