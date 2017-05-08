// -------------------------------------------------------------------
// FILE:		Richardson_project_4.cc
// TITLE:		Project #4
// AUTHOR:		Brandon Richardson
// COURSE:		CSCI 2000 (C++)
// DATE:		October 16, 2014
//
// PURPOSE:	Create a program that gathers the user's W2 information, and uses
//          the information to calculate the user's tax refund or how much the
//          user owes.
// -------------------------------------------------------------------
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MARRIED = 1, SINGLE = 0;
int menu();
//Opens a menu giving the user easy instructions and giving them
//an option to start the program or exit
void questionnaire(double& total_income, double& total_tax_interest, double& total_UC_APF, double& total_fed_income_tax, int& line_five, double& agi, double& taxable_income, double& tax, double& refund, double& amount_owed);
//Asks the user every question from the tax form
void filing (int& filing_status);
//Obtains the user's status as married or single
int standard_exemption(int filing_status);
// Returns the exemption for being married or single
double find_agi (double income, double tax_interest, double UC_APF);
// This function will calculate the adjusted gross income of the user
// by adding total_income, total_tax_interest, and total_UC_APF
double find_taxable_income (int& line_five, double& agi);
// Calculates the taxable income by subtracting the adjusted gross income
// from the exemption called line_five
double find_tax (double taxable_income, int filing_status);
// Calculates tax by multiplying the taxable income by the corresponding
// percentage based on how much taxable income the user has and whether
// the user is married or single
double validate_amount();
// Validates the users' input making sure they enter a correct number
double validate_tax_interest(double total_tax_interest);
// Validates the users' input making sure the input is between 0 and 1500
// and above 1500 giving the user one of three random messages telling the user
// that this form is not suitable for them
double user_refund(double tax, double total_fed_income_tax);
// Calculates the user's refund by subtracting their tax from their
// total federal income tax
double owed(double tax, double total_fed_income_tax);
// Calculates the amount owed by the user by subtracting their
//total federal income tax from their tax
void give_output(int filing_status, double agi, int line_five, double tax, double taxable_income, double amount_owed, double refund);
// Outputs all the gathered information back to the user
int main()
{
   int line_five, choice;
   double agi, tax, taxable_income, amount_owed, refund, total_income, total_tax_interest, total_UC_APF, total_fed_income_tax;
   int filing_status;
   do
   {
      choice = menu();
      switch (choice)
      {
      case 1:
      questionnaire(total_income, total_tax_interest, total_UC_APF, total_fed_income_tax, line_five, agi, taxable_income, tax, refund, amount_owed);
      give_output(filing_status, agi, line_five, tax, taxable_income, amount_owed, refund);
      break;

      case 2:
      cout << "Goodbye.\n";
      return 0;
      break;

      default:
         cout << "Enter 1 to begin and 2 to exit program.\n";
         cin >> choice;
      }
   }while (choice != 2);
    return 0;
}
int menu()
{
   int choice;
   cout << "Welcome and thank you for using Taxometer.\n\n";
   cout << "The questionnaire will open, and all you need to do is answer truthfully.\n\n";
   cout << "After you enter your answer to a question press enter.\n\n";
   cout << "Enter 1 to begin or 2 to exit.\n\n";
   cin >> choice;
   return choice;
}
void questionnaire(double& total_income, double& total_tax_interest, double& total_UC_APF, double& total_fed_income_tax, int& line_five, double& agi, double& taxable_income, double& tax, double& refund, double& amount_owed)
{
   int w2_num, filing_status;
   char option;
   double income, tax_interest, UC_APF;
   double fed_income_tax;
   w2_num = 0;
   total_income = 0;
   total_tax_interest = 0;
   total_UC_APF = 0;
   total_fed_income_tax = 0;
   agi = 0;
   line_five = 0;
   taxable_income = 0;
   tax = 0;
   refund = 0;
   amount_owed = 0;
   do
   {
      cout << "This is W2 number " << ++w2_num << ".\n";
      cout << "What are your total wages, salaries, and tips?\n";
      cin >> income;
      if (income < 0)
         validate_amount();
      total_income += income;
      cout << "What is your total taxable interest?\n";
      cin >> tax_interest;
      if (tax_interest < 0)
         validate_amount();
      total_tax_interest += tax_interest;
      validate_tax_interest(total_tax_interest);
      cout << "Do you earn any unemployment compensation or \n";
      cout << "Alaska Permanent Fund dividends?\n";
      cin >> UC_APF;
      if (UC_APF < 0)
         validate_amount();
      total_UC_APF += UC_APF;
      cout << "What is the amount of Federal income tax withheld from your W2(s)?\n";
      cin >> fed_income_tax;
      if (fed_income_tax < 0)
         validate_amount();
      total_fed_income_tax += fed_income_tax;
      cout << "Your total payments and credits is $ " << fed_income_tax << ".\n";
      cout << "Do you have any more W2 forms?\n";
      cout << "Type y for yes and n for no.\n";
      cin >> option;
      while (option != 'y' && option != 'Y' && option != 'n' && option != 'N')
      {
         cout << "Input y for yes or n for no.\n";
         cin >> option;
      }
   }while(option != 'n' && option != 'N');
      agi = find_agi(total_income, total_tax_interest, total_UC_APF);
      cout << "Your adjusted gross income is $ " << agi << ".\n";
      cout << "\n";
      filing (filing_status);
      line_five = standard_exemption(filing_status);
      taxable_income = find_taxable_income (line_five, agi);
      if (taxable_income < 0)
         cout << "Your taxable income is $0.\n";
      else
         cout << "This is your taxable income $" << taxable_income << ".\n";
      tax = find_tax (taxable_income, filing_status);
      cout << "This is your total tax $" << tax << ".\n";
      refund = user_refund(tax, total_fed_income_tax);
      cout << "This is your refund $" << refund << ".\n";
      amount_owed = owed (tax, total_fed_income_tax);
      cout << "This is the amount you owe $" << amount_owed << ".\n";
}
double find_agi(double total_income, double total_tax_interest, double total_UC_APF)
{
    return (total_income + total_tax_interest + total_UC_APF);
}
void filing (int& filing_status)
{
   char option;
   cout << "Are you single or married filing jointly?\n";
   cout << "\n";
   cout << "If you are single enter ""s"".\n";
   cout << "\n";
   cout << "If you are married filing jointly enter ""m"".\n";
   cout << "\n";
   cin >> option;
   if (option == 'm' || option == 'M')
      filing_status = MARRIED;
   else
      filing_status = SINGLE;
   while (option != 'm' && option != 'M' && option != 's' && option != 'S')
   {
      cout << "Please input s for single or m for married filing jointly.\n";
      cin >> option;
   }
}
int standard_exemption(int filing_status)
{
   int exemption;

   if (filing_status == SINGLE)
      exemption = 9750;
   else
      exemption = 19500;
   return (exemption);
}
double find_taxable_income (int& line_five, double& agi)
{
   return (agi - line_five);
}

double find_tax (double taxable_income, int filing_status)
{
   if (filing_status == SINGLE)
   {
      if (taxable_income <= 8700)
         return (taxable_income * 0.10);
      else if (taxable_income <= 35350)
         return (taxable_income * 0.15);
      else if (taxable_income <= 85650)
         return (taxable_income * 0.25);
      else if (taxable_income <= 178650)
         return (taxable_income * 0.28);
      else if (taxable_income <= 388350)
         return (taxable_income * 0.33);
      else if (taxable_income >= 388351)
         return (taxable_income * 0.35);
   }
   if (filing_status == MARRIED)
   {
      if (taxable_income <= 17400)
         return (taxable_income * 0.10);
      else if (taxable_income <= 70700)
         return (taxable_income * 0.15);
      else if (taxable_income <= 142700)
         return (taxable_income * 0.25);
      else if (taxable_income <= 217450)
         return (taxable_income * 0.28);
      else if (taxable_income <= 388350)
         return (taxable_income * 0.33);
      else if (taxable_income >= 388351)
         return (taxable_income * 0.35);
   }
}
void give_output(int filing_status, double agi, int line_five, double tax, double taxable_income, double amount_owed, double refund)
{
   if (filing_status = 1)
      cout << "\t Filing Status: Married";
   if (filing_status = 0)
      cout << "\t Filing Status: Single";
   cout << "\t\t Adjusted Gross Income: $" << agi << "\n";
   cout << "\t Standard Exemption: $" << line_five;
   cout << "\t Amount Owed: $" << amount_owed << "\n";
   cout << "\t Refund: $" << refund;
   cout << "\t\t\t Taxable Income: $" << taxable_income << "\n";
   cout << "\t Tax: $" << tax << "\n\n";
   cout << "\t\t\t Thank you for using Taxometer.\n";
}

double validate_amount()
{
   double amount = 0;
   cin >> amount;
   while (amount < 0)
   {
      cout << "Please enter an amount larger than 0.\n";
      cin >> amount;
   }
   return (amount);
}
double validate_tax_interest(double total_tax_interest)
{
   int msg;
   srand(time(0));
   if (total_tax_interest > 1500)
      {
         msg = (rand() % 3) + 1;
            if (msg == 1)
            {
               cout << "This form is not suitable for your tax situation.\n";
               return 0;
            }
            else if (msg == 2)
            {
               cout << "You need to fill out a different form.\n";
               return 0;
            }
            else if (msg == 3)
            {
               cout << "Based on your tax interest, this is not a suitable form to use.\n";
               return 0;
            }
      }
}
double user_refund (double tax, double total_fed_income_tax)
{
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
   if (total_fed_income_tax > tax)
      return(tax - total_fed_income_tax);
   else
      return 0;
}
double owed (double tax, double total_fed_income_tax)
{
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
   if (total_fed_income_tax < tax)
      return(total_fed_income_tax - tax) * -1;
   else
      return 0;
}
