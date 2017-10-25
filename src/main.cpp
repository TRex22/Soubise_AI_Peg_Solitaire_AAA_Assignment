/*	
AAA Assignment 2017

Evan Bancroft 879192
Jason Chalom 711985 

*/

/*TODO:

    http://courses.csail.mit.edu/6.884/spring10/labs/lab5.pdf

    NEW Evan
    =====


    Json:
    =====
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
#define results2_header "amount,number_denominations,time,found,end state"
#define results2_location "./results/results_exp2_recurse.csv"
GameBoard gb;
bool DEBUG = 0;


/* Headers */
int main(int argc, char *argv[]);
void test();
void run_backtracking();
void run_recursive_backtracking();
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
    GameBoard gb_new(101);
    cout<<"Result: "<<endl;
    gb_new.printBoard();    
}

void run_backtracking()
{
    cout << "Running experiment 1...\n\n";
    write_results_to_file(results1_location, results1_header, "");
    
    double total_start = omp_get_wtime();
    
    // increment number of experiments
    for (int i = 1; i <= 37; i=i+1)
    {
        int amount = i;//redundant?
        GameBoard gb_new(amount);
        if (DEBUG)
        {
        	cout<<"Start State:"<<std::endl;
        	gb_new.printBoard();
        }

        std::vector<std::vector<int>> path;
        double start = omp_get_wtime();

        // Add what ever being timed here
		gb_new = backtracking_stack(gb_new, path);
        double time = omp_get_wtime() - start;
        if (DEBUG)
        {
        	cout<<"End State:"<<std::endl;
        	gb_new.printBoard();
        }



        // Output results
        cout << "amount: " << amount << " path_length: " << path.size() << " time: " << time << endl << endl;

        // print file line
        ostringstream out;
        //cout<<"Printing"<<std::endl;
        out << amount << "," << path.size() << "," << time << endl; 
        write_results_to_file(results1_location, out.str());
    }

    double total_time = omp_get_wtime() - total_start;    
    cout << "\n\ntotal time: " << total_time << " seconds." << endl;
}

void run_recursive_backtracking()
{
    cout << "Running experiment 2 (recursive)...\n\n";
    write_results_to_file(results2_location, results2_header, "");
    
    double total_start = omp_get_wtime();
    
    // end states for European
    // 3:   0,2
    //      1,3
    //      2,3
    GameBoard final_1;
    final_1.board[0][2] = 1; //final peg

    GameBoard final_2;
    final_2.board[1][3] = 1; //final peg

    GameBoard final_3;
    final_3.board[2][3] = 1; //final peg

    // increment number of experiments
    for (int i = 1; i <= 37; i=i+1)
    {
        int amount = i;//redundant?
        std::vector<Move> path;
        bool found = false;
        int end_state = 1;
        double start =0.0, end = 0.0;

        GameBoard gb_new(amount);
        if (DEBUG)
        {
            cout<<"Start State:"<<std::endl;
            gb_new.printBoard();
        }

        start = omp_get_wtime();
        // Add what ever being timed here
        found = backtracking_recursive(gb_new, final_1, path);
        time = omp_get_wtime() - start;

        if(found == false)
        {
            gb_new = GameBoard(amount);
            start = omp_get_wtime();
            // Add what ever being timed here
            found = backtracking_recursive(gb_new, final_2, path);
            time = omp_get_wtime() - start;
            end_state=2;
        }

        if(found == false)
        {
            gb_new = GameBoard(amount);
            start = omp_get_wtime();
            // Add what ever being timed here
            found = backtracking_recursive(gb_new, final_3, path);
            time = omp_get_wtime() - start;
            end_state=3;
        }


        if (DEBUG)
        {
            cout<<"End State:"<<std::endl;
            gb_new.printBoard();
        }

        // Output results
        // "amount,number_denominations,time,found,end state"
        cout << "amount: " << amount << " path_length: " << path.size() << " time: " << time << " Found: " << found << "End State: " << end_state << endl << endl;

        // print file line
        ostringstream out;
        //cout<<"Printing"<<std::endl;
        out << amount << "," << path.size() << "," << time << found << end_state << endl; 
        write_results_to_file(results2_location, out.str());
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

        if(contains_string(str, "-recurse"))
        {
            run_recursive_backtracking();
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
