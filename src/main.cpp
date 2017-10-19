/*	
AAA Assignment 2017

Evan Bancroft 879192
Jason Chalom 711985 

*/

/*TODO:

    http://courses.csail.mit.edu/6.884/spring10/labs/lab5.pdf

    NEW Evan
    =====
    4. check if found solution


    Json:
    =====
    1. Stack based backtracking
    3. visualization
    4. latex
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <omp.h>
#include <time.h>
#include <cmath>
#include <chrono>
#include "omp.h"

#include "move_enum.h"
#include "move.h"
#include "helpers.h"
#include "solitaire_board.h"
#include "backtracking.cpp"


/* Global variables */
#define app_name "COMS3005 Assignment 2017"
#define results1_header "amount,number_denominations,time"
#define results1_location "./results/results_exp1.csv"
GameBoard gb;
bool DEBUG = 1;


/* Headers */
int main(int argc, char *argv[]);
void test();
void run_backtracking();
void process_args(int argc, char *argv[]);


using namespace std;
int main(int argc, char *argv[]) 
{
    print_cmd_heading(app_name);  
    process_args(argc, argv);


    /*Board testing*/
    if (DEBUG)
    {
    
    //gb.printBoard();
    }


    if(argc == 1)
    {
        print_usage(argv);
        halt_execution();
    }
    
    return EXIT_SUCCESS;
}

void test()
{
    cout<<"TESTS...."<<endl;

    gb.euroConfig_Random();
    GameBoard prev;
    std::vector<std::vector<int>> path;
    // gb = backtracking_recursive(gb, prev, path);
    cout<<"Print before BT...."<<endl;
    gb.printBoard();
    // cout<<"after...."<<endl;
    gb = backtracking_stack(gb);

    cout<<"Result: "<<endl;
    gb.printBoard();
}

void run_backtracking()
{
    cout << "Running experiment 1...\n\n";
    write_results_to_file(results1_location, results1_header, "");
    
    double total_start = omp_get_wtime();
    
    // increment number of experiments
    for (int i = 1; i <= 1000; i=i+100)
    {
        int amount = i;
        GameBoard gb_new(amount);
        gb_new.euroConfig_Random();
        gb_new.printBoard();
        GameBoard prev;
        std::vector<std::vector<int>> path;
        double start = omp_get_wtime();

        // Add what ever being timed here
        gb_new = backtracking_recursive(gb_new, prev, path);

        double time = omp_get_wtime() - start;
        gb_new.printBoard();


        // Output results
        cout << "amount: " << amount << " path_length: " << path.size() << " time: " << time << endl << endl;

        // print file line
        ostringstream out;
        out << amount << "," << path.size() << "," << time << endl; 
        write_results_to_file(results1_location, out.str());
    }

    double total_time = omp_get_wtime() - total_start;    
    cout << "\n\ntotal time: " << total_time << " seconds." << endl;
}

void process_args(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        string str = string(argv[i]);
        if(contains_string(str, "h") || contains_string(str, "help"))
        {
            print_usage(argv);
            halt_execution();
        }  

        if(contains_string(str, "-t") || contains_string(str, "tests"))
        {
            test();
        }       

        if(contains_string(str, "-rf") || contains_string(str, "run_full"))
        {
          	gb.euroConfig_Start();
    		gb.printBoard();
        }  

        if(contains_string(str, "-rr") || contains_string(str, "run_rand") || contains_string(str, "runr"))
        {
            gb.euroConfig_Random();
    		gb.printBoard();
        }

        if(contains_string(str, "-rb") || contains_string(str, "run_back") || contains_string(str, "runb"))
        {
            run_backtracking();
        }

        if(contains_string(str, "-m") || contains_string(str, "manual"))
        {

          	int id =0;
          	int x=0;
          	int y=0;
          	cin >> id;
          	while(id!=-1)
          	{
	          	cin >> x;
	          	cin >> y;
	          	if(gb.checkIfMoveValid(id,x,y))
	          	{
	          		cout<<gb.makeMove(id,x,y)<<'\n';
	          	}
	          	gb.printBoard();
	          	cout<<"Num Pegs:"<<gb.numPegs()<<'\n';
	          	cin>>id;
          	}
	      	
        }

    }
}