// -------------------------------------------------------------------
// FILE:		Richardson_project_6_final.cc
// TITLE:		Project #6
// AUTHOR:		Brandon Richardson
// COURSE:		CSCI 2000 (C++)
// DATE:		November 24, 2014
//
// PURPOSE: Add commands for the user to enter. These commands will change different parameters of the game.
//          Add stochastic events that will randomly occur. These events will also change
//          different parameters of the game. Game should be playable for one scenario.
// -------------------------------------------------------------------
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Define constant for number of x mesh points
const int X_MESH = 52;  // 2 more than actual x mesh points
const int X_MESH_TRUE = 50;

// Define constants for config array access
const int DELTA_T = 1;
const int PGR = 3;
const int C_CAP = 4;
const int BETA = 5;
const int ALPHA = 6;
const int D_S = 7;
const int MU_I = 8;
const int GAMMA = 9;
const int D_I = 10;
const int MU_R = 11;
const int D_R = 12;
const int TOT_POPULATION = 13;
const int MAX_POPULATION = 14;
const int TOT_MONEY = 15;
const int TAX_RATE = 16;
const int HOSPITAL_COST = 17;

void runStep(double config[], double S[][4], double I[][4], double R[][4]);
// The guts of this code.  runStep inputs the config array, and the arrays S, I, R
// runStep performs one time step of the finite differences scheme to numerically solve the PDE system
// S[0][1], R[0][1], I[0][1] will each contain the respective population sizes

double cutOff(double input);
// cutOff inputs a double named input, returns input if input >= threshold otherwise returns 0

double maxOfThree(double input1, double input2, double input3);
// maxOfThree inputs three doubles and returns the maximum of input1, input2, & input3

void calcPopulation(double S[][4], double I[][4], double R[][4]);
// Inputs the arrays S, I, R, uses Simpson's method to numerically calculate the total population
// of each of the S, I, R populations, and returns the values in S[0][1], I[0][1], and R[0][1]

char menu();
//Opens a menu giving the user easy instructions and giving them
//an option to start the program or exit

char menu_cases();
//Runs the separate cases of the main menu (new game, instructions, and exit program)

char new_game(string disease_name);
//Prompts the user to name their disease, change scenario settings,
//play the scenario, or return to the main menu

char new_game_case();
//Runs all options after the user selects new game. These options are
//Change disease name, scenario settings, play scenario, or return to main menu.

string get_disease();
//Allows user to input their desired disease name

void instructions();
//Provides game instructions for the user

void scenario_settings();
//Provides scenario settings for the user to change

char play_scenario();
//Plays the current scenario by displaying graphs of the susceptible, infected, and
//recovered populations as well as displaying all the different parameters of the game
//such as money, diffusion rate, population, income, expense, etc.

char player_commands();
//Allows the user to choose between commands

double nuke_sector();
//Subtracts $150,000 from total money. Nukes a sector setting the population of
//S, I, and R to 0 in the selected sector

double trauma_center();
//Costs $200,000. Builds a trauma center increases gamma by 10%
//and decreases M_R by 5%

double quarantine();
//Costs $75,000. Quarantines the sick decreasing D_I by 75%.

double PPE();
//Costs $10,000. Issues Personal Protective Equipment decreasing beta by 5%

double research();
//Costs $100,000. Reduces beta by 5%, increases gamma by 5%
//and decreases M_R by 5%

void rand_events(double config[], double S[][4], double I[][4], double R[][4], int d_time);
//Function containing code that determines when and what random events happen.
//Each random event changes different parameters of the game.

void events(double config[], double S[][4], double I[][4], double R[][4], int stoch_event);
//Function containing all the random events that can occur.

int find_index(double pop_density);
//Finds indices based on the population density

int main()
{
   // Define config array
   // Config contains all the settings for the game, as well as game parameters such as tax rate, money available
   double config[20];
   config[DELTA_T] = 0.01;
   config[PGR] = 0.5;
   config[C_CAP] = 1;
   config[BETA] = 10;
   config[ALPHA] = 0.5;
   config[D_S] = 0.5;
   config[MU_I] = 2;
   config[GAMMA] = 3;
   config[D_I] = 0.1;
   config[MU_R] = 1;
   config[D_R] = 0.5;
   config[TOT_MONEY] = 1000000;
   config[TAX_RATE] = 20;
   config[HOSPITAL_COST] = 5;
   config[MAX_POPULATION] = 300000000;

   double S[X_MESH][4], I[X_MESH][4], R[X_MESH][4];

   menu_cases();

   return 0;
}

char menu()
{
   char choice;
   cout << "\n\n\t\t\t\tHASHTAG PANDEMIC\t\t\t\t\t\n\n";
   cout << "\n\n\t\t\t\t[N]ew Game\t\t\t\t\t\n\n";
   cout << "\n\n\t\t\t\t[I]nstructions\t\t\t\t\t\n\n";
   cout << "\n\n\t\t\t\t[E]xit\t\t\t\t\t\n\n";
   cin >> choice;
   while (choice != 'N' && choice != 'I' && choice != 'E')
   {
      cout << "Invalid choice. Please enter 'N' for new game,\n\n";
      cout << "'I' for instructions, or 'E' to exit the game.\n\n";
      cin >> choice;
   }
   return choice;
}

char new_game()
{
   char option;
   string disease_name;

   cout << "\t\t\t\tDisease Name: " << disease_name << "\n\n\t\t";
   cout << "\t\t[C]hange Disease Name\n\n\t\t";
   cout << "\t\tScenario [S]ettings\n\n\t\t";
   cout << "\t\t[P]lay Scenario\n\n\t\t";
   cout << "\t\t[R]eturn to Main Menu\n\n\t\t";
   cin >> option;
   while (option != 'C' && option != 'S' && option != 'P' && option != 'R')
   {
      cout << "Invalid choice. Please enter 'C' to change disease name,\n\n";
      cout << "'S' to change settings, 'P' to play the game, \n\n";
      cout << "or 'R' to return to the main menu\n\n";
      cin >> option;
   }
   return option;
}

void instructions()
{
   char choice;
   cout << "Instructions go here.\n\n";
   cout << "Press 'R' or 'r' to return to main menu.\n";
   cin >> choice;
   while (choice != 'R' && choice != 'r')
   {
      cout << "Invalid choice. Press 'R' or 'r' to return to the main menu.";
      cin >> choice;
   }
}

char new_game_case()
{
   char option;
   char validation;
   string disease_name;

   do
   {
      option = new_game();
      switch (option)
      {
         case 'C':
            get_disease();
            break;

         case 'S':
            scenario_settings();
            break;

         case 'P':
            player_commands();
            break;

         case 'R':
            cout << "Returning to main menu.\n\n";
            break;

         default:
            cout << "Invalid option. Enter 'C' to change disease name \n";
            cout << ", 'S' for settings, 'P' to play, or 'R' to return to the main menu.\n\n";
      }
   } while (option != 'R');
}

string get_disease()
{
   char validation;
   string disease_name;

   cout << "Enter your disease name. Use an underscore if you want a space.\n\n";
   cin >> disease_name;
   do
   {
      cout << "Is " << disease_name << " correct? Type 'Y' for yes or 'N' for no.\n\n";
      cin >> validation;

      if (validation == 'N' || validation == 'n')
      {
         cout << "Enter your disease name. Use an underscore if you want a space.";
         cin >> disease_name;
      }
   } while(validation == 'N' || validation == 'n');

   return disease_name;

}

char menu_cases()
{
   char choice;
   do
   {
      choice = menu();
      switch (choice)
      {
         case 'N':
            new_game_case();
            break;

         case 'I':
            instructions();
            break;

         case 'E':
            cout << "Exiting Program.\n";
            break;

         default:
            cout << "Please enter N for new game, I for instructions \n";
            cout << ", or E to exit the game.\n";
      }
   } while (choice != 'E');
}

void scenario_settings()
{
   char choice;
   cout << "Settings can be changed here.\n\n";
   cout << "Press 'R' or 'r' to return to new game menu.\n";
   cin >> choice;
   while (choice != 'R' && choice != 'r')
   {
      cout << "Invalid choice. Press 'R' or 'r' to return to the new game menu.";
      cin >> choice;
   }
}

char play_scenario()
{
   char displayS[12][13],displayI[12][13], displayR[12][13];
   double S[X_MESH][4], I[X_MESH][4], R[X_MESH][4], income_rate, expense_rate;
   char command = ' ';
   int d_time;

    for(int i = 1; i < X_MESH; i++)
   {
      S[i][1] = (i - 1.0) / X_MESH_TRUE;
      S[i][2] = 1;
      R[i][1] = (i - 1.0) / X_MESH_TRUE;
      R[i][2] = 0;
      I[i][1] = (i - 1.0) / X_MESH_TRUE;
      if (i < 5)
         I[i][2] = 0.5;
      else
         I[i][2] = 0;
   }
   do
   {
        for (int i = 0; i <= 11 ; i++)
   {
      for (int j = 0 ; j <= 12 ; j++)
         displayS[i][j] = ' ';
   }

   for (int i = 0; i <= 11 ; i++)
   {
   for (int j = 0 ; j <= 12 ; j++)
      displayI[i][j] = ' ';
   }

   for (int i = 0; i <= 11 ; i++)
   {
      for (int j = 0 ; j <= 12 ; j++)
         displayR[i][j] = ' ';
   }

   double config[20];
   config[DELTA_T] = 0.01;
   config[PGR] = 0.5;
   config[C_CAP] = 1;
   config[BETA] = 10;
   config[ALPHA] = 0.5;
   config[D_S] = 0.5;
   config[MU_I] = 2;
   config[GAMMA] = 3;
   config[D_I] = 0.1;
   config[MU_R] = 1;
   config[D_R] = 0.5;
   config[TOT_MONEY] = 1000000;
   config[TAX_RATE] = 20;
   config[HOSPITAL_COST] = 5;
   config[MAX_POPULATION] = 300000000;

   rand_events(config, S, I, R, d_time);

   runStep(config, S, I, R);

   for (int a = 0; a <= 10; a++)
      displayS[a][find_index(S[5*(a-1)+3][2])] = '*';
   for (int b = 0; b <= 10; b++)
      displayI[b][find_index(I[5*(b-1)+3][2])] = '*';
   for (int c = 0; c <= 10; c++)
      displayR[c][find_index(R[5*(c-1)+3][2])] = '*';

      cout << "\n\nDisease Progression\n";
      cout << setw(24) << "Susceptible" << setw(24) << "Infected" << setw(24) << "Recovered" << "\n";
      cout <<setw(5)<<"100%"<<setw(2)<<displayS[1][11]<<setw(2)<<displayS[2][11]<<setw(2)<<displayS[3][11]<<setw(2)<<displayS[4][11]<<setw(2)<<displayS[5][11]<<setw(2)<<displayS[6][11]<<setw(2)<<displayS[7][11]<<setw(2)<<displayS[8][11]<<setw(2)<<displayS[9][11]<<setw(2)<<displayS[10][11]<<setw(5)<<"100%"<<setw(2)<<displayI[1][11]<<setw(2)<<displayI[2][11]<<setw(2)<<displayI[3][11]<<setw(2)<<displayS[4][11]<<setw(2)<<displayI[5][11]<<setw(2)<<displayI[6][11]<<setw(2)<<displayI[7][11]<<setw(2)<<displayI[8][11]<<setw(2)<<displayI[9][11]<<setw(2)<<displayI[10][11]<<setw(5)<<"100%"<<setw(2)<<displayR[1][11]<<setw(2)<<displayR[2][11]<<setw(2)<<displayR[3][11]<<setw(2)<<displayR[4][11]<<setw(2)<<displayR[5][11]<<setw(2)<<displayR[6][11]<<setw(2)<<displayR[7][11]<<setw(2)<<displayR[8][11]<<setw(2)<<displayR[9][11]<<setw(2)<<displayR[10][11]<< "\n";
      cout <<setw(5)<<"90%"<<setw(2)<<displayS[1][10]<<setw(2)<<displayS[2][10]<<setw(2)<<displayS[3][10]<<setw(2)<<displayS[4][10]<<setw(2)<<displayS[5][10]<<setw(2)<<displayS[6][10]<<setw(2)<<displayS[7][10]<<setw(2)<<displayS[8][10]<<setw(2)<<displayS[9][10]<<setw(2)<<displayS[10][10]<<setw(5)<<"90%"<<setw(2)<<displayI[1][10]<<setw(2)<<displayI[2][10]<<setw(2)<<displayI[3][10]<<setw(2)<<displayS[4][10]<<setw(2)<<displayI[5][10]<<setw(2)<<displayI[6][10]<<setw(2)<<displayI[7][10]<<setw(2)<<displayI[8][10]<<setw(2)<<displayI[9][10]<<setw(2)<<displayI[10][10]<<setw(5)<<"90%"<<setw(2)<<displayR[1][10]<<setw(2)<<displayR[2][10]<<setw(2)<<displayR[3][10]<<setw(2)<<displayR[4][10]<<setw(2)<<displayR[5][10]<<setw(2)<<displayR[6][10]<<setw(2)<<displayR[7][10]<<setw(2)<<displayR[8][10]<<setw(2)<<displayR[9][10]<<setw(2)<<displayR[10][10]<< "\n";
      cout <<setw(5)<<"80%"<<setw(2)<<displayS[1][9]<<setw(2)<<displayS[2][9]<<setw(2)<<displayS[3][9]<<setw(2)<<displayS[4][9]<<setw(2)<<displayS[5][9]<<setw(2)<<displayS[6][9]<<setw(2)<<displayS[7][9]<<setw(2)<<displayS[8][9]<<setw(2)<<displayS[9][9]<<setw(2)<<displayS[10][9]<<setw(5)<<"80%"<<setw(2)<<displayI[1][9]<<setw(2)<<displayI[2][9]<<setw(2)<<displayI[3][9]<<setw(2)<<displayI[4][9]<<setw(2)<<displayI[5][9]<<setw(2)<<displayI[6][9]<<setw(2)<<displayI[7][9]<<setw(2)<<displayI[8][9]<<setw(2)<<displayI[9][9]<<setw(2)<<displayI[10][9]<<setw(5)<<"80%"<<setw(2)<<displayR[1][9]<<setw(2)<<displayR[2][9]<<setw(2)<<displayR[3][9]<<setw(2)<<displayR[4][9]<<setw(2)<<displayR[5][9]<<setw(2)<<displayR[6][9]<<setw(2)<<displayR[7][9]<<setw(2)<<displayR[8][9]<<setw(2)<<displayR[9][9]<<setw(2)<<displayR[10][9]<< "\n";
      cout <<setw(5)<<"70%"<<setw(2)<<displayS[1][8]<<setw(2)<<displayS[2][8]<<setw(2)<<displayS[3][8]<<setw(2)<<displayS[4][8]<<setw(2)<<displayS[5][8]<<setw(2)<<displayS[6][8]<<setw(2)<<displayS[7][8]<<setw(2)<<displayS[8][8]<<setw(2)<<displayS[9][8]<<setw(2)<<displayS[10][8]<<setw(5)<<"70%"<<setw(2)<<displayI[1][8]<<setw(2)<<displayI[2][8]<<setw(2)<<displayI[3][8]<<setw(2)<<displayI[4][8]<<setw(2)<<displayI[5][8]<<setw(2)<<displayI[6][8]<<setw(2)<<displayI[7][8]<<setw(2)<<displayI[8][8]<<setw(2)<<displayI[9][8]<<setw(2)<<displayI[10][8]<<setw(5)<<"70%"<<setw(2)<<displayR[1][8]<<setw(2)<<displayR[2][8]<<setw(2)<<displayR[3][8]<<setw(2)<<displayR[4][8]<<setw(2)<<displayR[5][8]<<setw(2)<<displayR[6][8]<<setw(2)<<displayR[7][8]<<setw(2)<<displayR[8][8]<<setw(2)<<displayR[9][8]<<setw(2)<<displayR[10][8]<< "\n";
      cout <<setw(5)<<"60%"<<setw(2)<<displayS[1][7]<<setw(2)<<displayS[2][7]<<setw(2)<<displayS[3][7]<<setw(2)<<displayS[4][7]<<setw(2)<<displayS[5][7]<<setw(2)<<displayS[6][7]<<setw(2)<<displayS[7][7]<<setw(2)<<displayS[8][7]<<setw(2)<<displayS[9][7]<<setw(2)<<displayS[10][7]<<setw(5)<<"60%"<<setw(2)<<displayI[1][7]<<setw(2)<<displayI[2][7]<<setw(2)<<displayI[3][7]<<setw(2)<<displayI[4][7]<<setw(2)<<displayI[5][7]<<setw(2)<<displayI[6][7]<<setw(2)<<displayI[7][7]<<setw(2)<<displayI[8][7]<<setw(2)<<displayI[9][7]<<setw(2)<<displayI[10][7]<<setw(5)<<"60%"<<setw(2)<<displayR[1][7]<<setw(2)<<displayR[2][7]<<setw(2)<<displayR[3][7]<<setw(2)<<displayR[4][7]<<setw(2)<<displayR[5][7]<<setw(2)<<displayR[6][7]<<setw(2)<<displayR[7][7]<<setw(2)<<displayR[8][7]<<setw(2)<<displayR[9][7]<<setw(2)<<displayR[10][7]<< "\n";
      cout <<setw(5)<<"50%"<<setw(2)<<displayS[1][6]<<setw(2)<<displayS[2][6]<<setw(2)<<displayS[3][6]<<setw(2)<<displayS[4][6]<<setw(2)<<displayS[5][6]<<setw(2)<<displayS[6][6]<<setw(2)<<displayS[7][6]<<setw(2)<<displayS[8][6]<<setw(2)<<displayS[9][6]<<setw(2)<<displayS[10][6]<<setw(5)<<"50%"<<setw(2)<<displayI[1][6]<<setw(2)<<displayI[2][6]<<setw(2)<<displayI[3][6]<<setw(2)<<displayI[4][6]<<setw(2)<<displayI[5][6]<<setw(2)<<displayI[6][6]<<setw(2)<<displayI[7][6]<<setw(2)<<displayI[8][6]<<setw(2)<<displayI[9][6]<<setw(2)<<displayI[10][6]<<setw(5)<<"50%"<<setw(2)<<displayR[1][6]<<setw(2)<<displayR[2][6]<<setw(2)<<displayR[3][6]<<setw(2)<<displayR[4][6]<<setw(2)<<displayR[5][6]<<setw(2)<<displayR[6][6]<<setw(2)<<displayR[7][6]<<setw(2)<<displayR[8][6]<<setw(2)<<displayR[9][6]<<setw(2)<<displayR[10][6]<< "\n";
      cout <<setw(5)<<"40%"<<setw(2)<<displayS[1][5]<<setw(2)<<displayS[2][5]<<setw(2)<<displayS[3][5]<<setw(2)<<displayS[4][5]<<setw(2)<<displayS[5][5]<<setw(2)<<displayS[6][5]<<setw(2)<<displayS[7][5]<<setw(2)<<displayS[8][5]<<setw(2)<<displayS[9][5]<<setw(2)<<displayS[10][5]<<setw(5)<<"40%"<<setw(2)<<displayI[1][5]<<setw(2)<<displayI[2][5]<<setw(2)<<displayI[3][5]<<setw(2)<<displayI[4][5]<<setw(2)<<displayI[5][5]<<setw(2)<<displayI[6][5]<<setw(2)<<displayI[7][5]<<setw(2)<<displayI[8][5]<<setw(2)<<displayI[9][5]<<setw(2)<<displayI[10][5]<<setw(5)<<"40%"<<setw(2)<<displayR[1][5]<<setw(2)<<displayR[2][5]<<setw(2)<<displayR[3][5]<<setw(2)<<displayR[4][5]<<setw(2)<<displayR[5][5]<<setw(2)<<displayR[6][5]<<setw(2)<<displayR[7][5]<<setw(2)<<displayR[8][5]<<setw(2)<<displayR[9][5]<<setw(2)<<displayR[10][5]<< "\n";
      cout <<setw(5)<<"30%"<<setw(2)<<displayS[1][4]<<setw(2)<<displayS[2][4]<<setw(2)<<displayS[3][4]<<setw(2)<<displayS[4][4]<<setw(2)<<displayS[5][4]<<setw(2)<<displayS[6][4]<<setw(2)<<displayS[7][4]<<setw(2)<<displayS[8][4]<<setw(2)<<displayS[9][4]<<setw(2)<<displayS[10][4]<<setw(5)<<"30%"<<setw(2)<<displayI[1][4]<<setw(2)<<displayI[2][4]<<setw(2)<<displayI[3][4]<<setw(2)<<displayI[4][4]<<setw(2)<<displayI[5][4]<<setw(2)<<displayI[6][4]<<setw(2)<<displayI[7][4]<<setw(2)<<displayI[8][4]<<setw(2)<<displayI[9][4]<<setw(2)<<displayI[10][4]<<setw(5)<<"30%"<<setw(2)<<displayR[1][4]<<setw(2)<<displayR[2][4]<<setw(2)<<displayR[3][4]<<setw(2)<<displayR[4][4]<<setw(2)<<displayR[5][4]<<setw(2)<<displayR[6][4]<<setw(2)<<displayR[7][4]<<setw(2)<<displayR[8][4]<<setw(2)<<displayR[9][4]<<setw(2)<<displayR[10][4]<< "\n";
      cout <<setw(5)<<"20%"<<setw(2)<<displayS[1][3]<<setw(2)<<displayS[2][3]<<setw(2)<<displayS[3][3]<<setw(2)<<displayS[4][3]<<setw(2)<<displayS[5][3]<<setw(2)<<displayS[6][3]<<setw(2)<<displayS[7][3]<<setw(2)<<displayS[8][3]<<setw(2)<<displayS[9][3]<<setw(2)<<displayS[10][3]<<setw(5)<<"20%"<<setw(2)<<displayI[1][3]<<setw(2)<<displayI[2][3]<<setw(2)<<displayI[3][3]<<setw(2)<<displayI[4][3]<<setw(2)<<displayI[5][3]<<setw(2)<<displayI[6][3]<<setw(2)<<displayI[7][3]<<setw(2)<<displayI[8][3]<<setw(2)<<displayI[9][3]<<setw(2)<<displayI[10][3]<<setw(5)<<"20%"<<setw(2)<<displayR[1][3]<<setw(2)<<displayR[2][3]<<setw(2)<<displayR[3][3]<<setw(2)<<displayR[4][3]<<setw(2)<<displayR[5][3]<<setw(2)<<displayR[6][3]<<setw(2)<<displayR[7][3]<<setw(2)<<displayR[8][3]<<setw(2)<<displayR[9][3]<<setw(2)<<displayR[10][3]<< "\n";
      cout <<setw(5)<<"10%"<<setw(2)<<displayS[1][2]<<setw(2)<<displayS[2][2]<<setw(2)<<displayS[3][2]<<setw(2)<<displayS[4][2]<<setw(2)<<displayS[5][2]<<setw(2)<<displayS[6][2]<<setw(2)<<displayS[7][2]<<setw(2)<<displayS[8][2]<<setw(2)<<displayS[9][2]<<setw(2)<<displayS[10][2]<<setw(5)<<"10%"<<setw(2)<<displayI[1][2]<<setw(2)<<displayI[2][2]<<setw(2)<<displayI[3][2]<<setw(2)<<displayI[4][2]<<setw(2)<<displayI[5][2]<<setw(2)<<displayI[6][2]<<setw(2)<<displayI[7][2]<<setw(2)<<displayI[8][2]<<setw(2)<<displayI[9][2]<<setw(2)<<displayI[10][2]<<setw(5)<<"10%"<<setw(2)<<displayR[1][2]<<setw(2)<<displayR[2][2]<<setw(2)<<displayR[3][2]<<setw(2)<<displayR[4][2]<<setw(2)<<displayR[5][2]<<setw(2)<<displayR[6][2]<<setw(2)<<displayR[7][2]<<setw(2)<<displayR[8][2]<<setw(2)<<displayR[9][2]<<setw(2)<<displayR[10][2]<< "\n";
      cout <<setw(5)<<"0%"<<setw(2)<<displayS[1][1]<<setw(2)<<displayS[2][1]<<setw(2)<<displayS[3][1]<<setw(2)<<displayS[4][1]<<setw(2)<<displayS[5][1]<<setw(2)<<displayS[6][1]<<setw(2)<<displayS[7][1]<<setw(2)<<displayS[8][1]<<setw(2)<<displayS[9][1]<<setw(2)<<displayS[10][1]<<setw(5)<<"0%"<<setw(2)<<displayI[1][1]<<setw(2)<<displayI[2][1]<<setw(2)<<displayI[3][1]<<setw(2)<<displayI[4][1]<<setw(2)<<displayI[5][1]<<setw(2)<<displayI[6][1]<<setw(2)<<displayI[7][1]<<setw(2)<<displayI[8][1]<<setw(2)<<displayI[9][1]<<setw(2)<<displayI[10][1]<<setw(5)<<"0%"<<setw(2)<<displayR[1][1]<<setw(2)<<displayR[2][1]<<setw(2)<<displayR[3][1]<<setw(2)<<displayR[4][1]<<setw(2)<<displayR[5][1]<<setw(2)<<displayR[6][1]<<setw(2)<<displayR[7][1]<<setw(2)<<displayR[8][1]<<setw(2)<<displayR[9][1]<<setw(2)<<displayR[10][1]<< "\n";
      cout <<setw(5)<<"S"<<setw(2)<<0<<setw(2)<<1<<setw(2)<<2<<setw(2)<<3<<setw(2)<<4<<setw(2)<<5<<setw(2)<<6<<setw(2)<<7<<setw(2)<<8<<setw(2)<<9<<setw(5)<<"S"<<setw(2)<<0<<setw(2)<<1<<setw(2)<<2<<setw(2)<<3<<setw(2)<<4<<setw(2)<<5<<setw(2)<<6<<setw(2)<<7<<setw(2)<<8<<setw(2)<<9<<setw(5)<<"S"<<setw(2)<<0<<setw(2)<<1<<setw(2)<<2<<setw(2)<<3<<setw(2)<<4<<setw(2)<<5<<setw(2)<<6<<setw(2)<<7<<setw(2)<<8<<setw(2)<<9;

   income_rate = (S[0][1]+R[0][1])*config[MAX_POPULATION]*1;
   expense_rate = I[0][1]*config[MAX_POPULATION]*1;
   config[TOT_MONEY] += income_rate - expense_rate;

      cout << "\n\n";
      cout << "[Disease Name] Properties: \n";
      cout << "Infection Rate: " << config[BETA] << setw(2) << "Mortality Rate: " << config[MU_I] << setw(2) << "Recovery Rate: " << config[GAMMA] << setw(2) << "Immunity Loss Rate: " << config[ALPHA] << setw(2) << "Recovered Mortality Rate: " << config[MU_R] << "\n\n";
      cout << "Population Properties:\n";
      cout << "Total Population: " << config[MAX_POPULATION]*(S[0][1] + I[0][1] + R[0][1]) << setw(2) << "Susceptible Size: " << S[0][1]*config[MAX_POPULATION] << setw(2) << "Infected Size: " << I[0][1]*config[MAX_POPULATION] << setw(2) << "Recovered Size: " << config[MAX_POPULATION]*R[0][1] << "\n\n";
      cout << "Susceptible Movement Rate: " << config[D_S] << setw(2) << "Infected Movement Rate: " << config[D_I] << setw(2) << "Recovered Movement Rate: " << config[D_R] << "\n\n";
      cout << "Financial Status:\n";
      cout << "Monetary Resources: " << config[TOT_MONEY] << setw(2) << "Total Taxpayers: " << S[0][1] + R[0][1] << setw(2) << "Income Rate: " << income_rate << setw(2) << "Expense Rate: " << expense_rate << "\n\n";
      cout << "Commands:\n";
      cout << "[enter] Run for one month" << setw(2) << "[N]uke Sector " << setw(2) << "[B]uild Trauma Center " << "\n";
      cout << "[R]esearch " << setw(2) << "[D]eclare Quarantine " << setw(2) << "[I]ssue PPE " << setw(2) << "[Q]uit Game ";
      cout << "\n";

      runStep(config, S, I, R);

      cin.get(command);
      cin.get(command);

      if (I[0][1] < 0.005)
         cout <<  "YOU WIN!!";
      if (I[0][1] > 0.95)
         cout << "95% OR MORE OF THE WORLD IS INFECTED\n\nYOU LOSE!!";
      if ((S[0][1] + I[0][1] + R[0][1]) < 0.01)
         cout << "THE TOTAL WORLD POPULATION HAS FALLEN BELOW 1%\n\nYOU LOSE!!";

   } while (command == '\n');
   return command;
}

char player_commands()
{
   char command;
   int d_time = 0;

   do
   {
      command = play_scenario();
      switch(command)
      {
         case '\n':
            play_scenario();
         break;

         case 'N':
            nuke_sector();
            cout << "\nNuke has been launched at designated sector.";
         break;

         case 'B':
            trauma_center();
            cout << "\nTrauma center has been built.";
         break;

         case 'D':
            quarantine();
            cout << "\nQuarantine has been declared.";
         break;

         case 'R':
            research();
            cout << "\nResearch has been started.";
         break;

         case 'I':
            PPE();
            cout << "\nPPE issued.";
         break;

         case 'Q':
            cout << "\nQuitting game.\n";
         break;

         default:
            cout << "Please enter N to nuke, B to build a trauma center \n";
            cout << ", D quarantine, R for research, I to issue PPE, or Q to quit.\n";
      }
   } while (command != 'Q');
}


int find_index(double pop_density)
{
   pop_density = floor(pop_density * 10 + .5);
   if (pop_density <= 1)
      return 1;
   if (pop_density <= 2)
      return 2;
   if (pop_density <= 3)
      return 3;
   if (pop_density <= 4)
      return 4;
   if (pop_density <= 5)
      return 5;
   if (pop_density <= 6)
      return 6;
   if (pop_density <= 7)
      return 7;
   if (pop_density <= 8)
      return 8;
   if (pop_density <= 9)
      return 9;
   if (pop_density <= 10)
      return 10;
   else
      return 11;

}

double nuke_sector()
{
   int s;

   double config[20];

   char displayS[12][13],displayI[12][13], displayR[12][13];
   double S[X_MESH][4], I[X_MESH][4], R[X_MESH][4];

   for(int i = 1; i < X_MESH; i++)
   {
      S[i][1] = (i - 1.0) / X_MESH_TRUE;
      S[i][2] = 1;
      R[i][1] = (i - 1.0) / X_MESH_TRUE;
      R[i][2] = 0;
      I[i][1] = (i - 1.0) / X_MESH_TRUE;
      if (i < 5)
         I[i][2] = 0.5;
      else
         I[i][2] = 0;
   }


   config[TOT_MONEY] -= 150000;
   cout << "What sector would you like to nuke?\n\n";
   cin >> s;
   if (s > 9)
   {
      cout << "Enter a sector 1 through 9.\n\n";
      cin >> s;
   }
   else if (s < 0)
   {
      cout << "Enter a sector 1 through 9.\n\n";
      cin >> s;
   }
   S[5*(s-1)+3][2] = 0;
   I[5*(s-1)+3][2] = 0;
   R[5*(s-1)+3][2] = 0;
   S[5*(s-1)+2][2] = 0;
   I[5*(s-1)+2][2] = 0;
   R[5*(s-1)+2][2] = 0;
   S[5*(s-1)+4][2] = 0;
   I[5*(s-1)+4][2] = 0;
   R[5*(s-1)+4][2] = 0;

   return config[TOT_MONEY];
}

double trauma_center()
{
   double config[20];

   config[TOT_MONEY] = config[TOT_MONEY] - 200000;
   config[GAMMA] *= 1.1;
   config[MU_I] *= .95;

   return config[TOT_MONEY], config[GAMMA], config[MU_I];
}

double research()
{
   double config[20];

   config[TOT_MONEY] -= 100000;
   config[BETA] = config[BETA] - config[BETA]*.05;
   config[GAMMA] = config[GAMMA]*.05 + config[GAMMA];
   config[MU_R] = config[MU_R] - config[MU_R]*.05;

   return config[TOT_MONEY], config[GAMMA], config[MU_R], config[BETA];
}

double quarantine()
{
   double config[20];

   config[TOT_MONEY] -= 75000;
   config[D_I] = config[D_I] - config[D_I]*.75;

   config[TOT_MONEY], config[D_I];
}

double PPE()
{
   double config[20];

   config[TOT_MONEY] -= 10000;
   config[BETA] = config[BETA] - config[BETA]*.05;

   config[TOT_MONEY], config[BETA];
}

void rand_events(double config[20], double S[X_MESH][4], double I[X_MESH][4], double R[X_MESH][4], int d_time)
{
   int stoch_event;

   d_time--;
   if (d_time < 0)
   {
      d_time = (rand() % 19);
      return;
   }
   else if (d_time == 0)
   {
      d_time = 1 + (rand() % 20);
      events(config, S, I, R, stoch_event);
      return;
   }
}

void events(double config[], double S[][4], double I[][4], double R[][4], int stoch_event)
{
   int x, y, s1, s2, s3;

   srand(time(0));

   for(x = 1; x < 20; x++)
      stoch_event = 1 + (rand() % 6);


   switch (stoch_event)
   {
      case 1:
         for (y = 0; y < 10; y++)
         {
            s1 = (rand() % 9);
            s2 = (rand() % 9);
            s3 = (rand() % 9);
         }

         S[5*(s1-1)+3][2] *= .75;
         I[5*(s1-1)+3][2] *= .75;
         R[5*(s1-1)+3][2] *= .75;
         S[5*(s2-1)+3][2] *= .75;
         I[5*(s2-1)+3][2] *= .75;
         R[5*(s2-1)+3][2] *= .75;
         S[5*(s3-1)+3][2] *= .75;
         I[5*(s3-1)+3][2] *= .75;
         R[5*(s3-1)+3][2] *= .75;
      break;

      case 2:
         for (y = 0; y < 10; y++)
         {
            s1 = (rand() % 9);
            s2 = (rand() % 9);
            s3 = (rand() % 9);
         }

         S[5*(s1-1)+3][2] += .05;
         I[5*(s1-1)+3][2] += .05;
         R[5*(s1-1)+3][2] += .05;
         S[5*(s2-1)+3][2] += .05;
         I[5*(s2-1)+3][2] += .05;
         R[5*(s2-1)+3][2] += .05;
         S[5*(s3-1)+3][2] += .05;
         I[5*(s3-1)+3][2] += .05;
         R[5*(s3-1)+3][2] += .05;
      break;

      case 3:
         config[BETA] *= 1.05;
         config[GAMMA] *= .95;
      break;

      case 4:
         S[0][1] *= .9;
         I[0][1] *= .9;
         R[0][1] *= .9;
      break;

      case 5:
         R[0][1] += (I[0][1]*.5);
      break;

      case 6:
         config[TOT_MONEY] *= .8;

   }
}

void runStep(double config[], double S[][4], double I[][4], double R[][4])
{
   // Create a temp set of arrays
   double S1[X_MESH][4], I1[X_MESH][4], R1[X_MESH][4];

   // Determine the number of time steps in order to preserve stability of the FD method
   int tSteps = 0;

   tSteps = ceil(2 * maxOfThree(config[D_S], config[D_I], config[D_R]) * config[DELTA_T] * X_MESH_TRUE * X_MESH_TRUE + 1);

   // Run FD Method tSteps times to traverse config[DETLA_T] units of time
   for(int j = 1; j <= tSteps; j++)
   {
      for(int i = 2; i <= X_MESH_TRUE; i++)
      {
         S1[i][1] = (i - 1.0) / X_MESH_TRUE;
         S1[i][2] = cutOff(config[D_S] * config[DELTA_T] / tSteps * X_MESH_TRUE * X_MESH_TRUE * S[i + 1][2] + (1 - 2 * config[D_S] * config[DELTA_T] / tSteps * X_MESH_TRUE * X_MESH_TRUE) * S[i][2] + config[D_S] * config[DELTA_T] / tSteps * X_MESH_TRUE * X_MESH_TRUE * S[i - 1][2] + config[DELTA_T] / tSteps * (config[PGR] * (S[i][2] + R[i][2]) - config[PGR] / config[C_CAP] * (S[i][2] + R[i][2]) * (S[i][2] + R[i][2]) - config[BETA] * S[i][2] * I[i][2] + config[ALPHA] * R[i][2]));

         I1[i][1] = (i - 1.0) / X_MESH_TRUE;
         I1[i][2] = cutOff(config[D_I] * config[DELTA_T] / tSteps * X_MESH_TRUE * X_MESH_TRUE * I[i + 1][2] + (1 - 2 * config[D_I] * config[DELTA_T] / tSteps * X_MESH_TRUE * X_MESH_TRUE) * I[i][2] + config[D_I] * config[DELTA_T] / tSteps * X_MESH_TRUE * X_MESH_TRUE * I[i - 1][2] + config[DELTA_T] / tSteps * (config[BETA] * S[i][2] * I[i][2] - config[MU_I] * I[i][2] - config[GAMMA] * I[i][2]));

         R1[i][1] = (i - 1.0) / X_MESH_TRUE;
         R1[i][2] = cutOff(config[D_R] * config[DELTA_T] / tSteps * X_MESH_TRUE * X_MESH_TRUE * R[i + 1][2] + (1 - 2 * config[D_R] * config[DELTA_T] / tSteps * X_MESH_TRUE * X_MESH_TRUE) * R[i][2] + config[D_R] * config[DELTA_T] / tSteps * X_MESH_TRUE * X_MESH_TRUE * R[i - 1][2] + config[DELTA_T] / tSteps * (config[GAMMA] * I[i][2] - config[MU_R] * R[i][2] - config[ALPHA] * R[2][i]));
      }

      // Code for the Neumann BC
      S1[1][1] = 0;
      S1[1][2] = S1[2][2];
      S1[X_MESH_TRUE + 1][1] = 1;
      S1[X_MESH_TRUE + 1][2] = S1[X_MESH_TRUE][2];
      I1[1][1] = 0;
      I1[1][2] = I1[2][2];
      I1[X_MESH_TRUE + 1][1] = 1;
      I1[X_MESH_TRUE + 1][2] = I1[X_MESH_TRUE][2];
      R1[1][1] = 0;
      R1[1][2] = R1[2][2];
      R1[X_MESH_TRUE + 1][1] = 1;
      R1[X_MESH_TRUE + 1][2] = R1[X_MESH_TRUE][2];

      for(int i = 1; i < X_MESH; i++)
      {
         S[i][1] = S1[i][1];
         S[i][2] = S1[i][2];
         I[i][1] = I1[i][1];
         I[i][2] = I1[i][2];
         R[i][1] = R1[i][1];
         R[i][2] = R1[i][2];
      }
   }
    calcPopulation(S, I, R);
}
double cutOff(double input)
{
   const double THRESHOLD = 0.00000001;

   if (input >= THRESHOLD)
      return input;
   else
      return 0;
}

double maxOfThree(double input1, double input2, double input3)
{
   double max_value = input1;

   if (max_value < input2)
      max_value = input2;
   if (max_value < input3)
      max_value = input3;

   return max_value;
}

void calcPopulation(double S[][4], double I[][4], double R[][4])
{
   // Estimate total populations for S, I, & R & place in [0][1]
   double tempS = (S[1][2] + S[X_MESH_TRUE][2]), tempI = (I[1][2] + I[X_MESH_TRUE][2]), tempR = (R[1][2] + R[X_MESH_TRUE][2]);
   for(int i = 2; i < X_MESH_TRUE; i++)
   {
      if (i % 2 == 1)
      {
         tempS += 2 * S[i][2];
         tempI += 2 * I[i][2];
         tempR += 2 * R[i][2];
      }
      else
      {
         tempS += 4 * S[i][2];
         tempI += 4 * I[i][2];
         tempR += 4 * R[i][2];
      }
   }
   S[0][1] = tempS * 1 / (3 * X_MESH_TRUE);
   I[0][1] = tempI * 1 / (3 * X_MESH_TRUE);
   R[0][1] = tempR * 1 / (3 * X_MESH_TRUE);
}


