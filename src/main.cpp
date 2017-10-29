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

#include "move.h"
#include "helpers.h"
#include "solitaire_board.h"
#include "backtracking.cpp"


/* Global variables */
#define app_name "COMS3005 Assignment 2017"
#define results1_header "amount,path length,time,found"
#define results1_location "./results/results_exp1_stack.csv"
#define results2_header "amount,path length,time,found,end state"
#define results2_location "./results/results_exp2_recurse.csv"
#define results3_header "amount,time,end state"
#define results3_location "./results/results_exp3_recurse.csv"
GameBoard gb;
bool DEBUG = 0;


/* Headers */
int main(int argc, char *argv[]);
void test();
void printPath(vector<vector<int>> path);
void run_stack_backtracking();
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
	int numValidMoves =0;
   // int totalNumPegs =0;
	cout<<"TESTS...."<<endl;
    GameBoard gb_new;
    //gb_new.euroConfig_Start();
    gb_new.board[2][2]=1;
    gb_new.board[3][2]=1;
    gb_new.board[4][3]=1;
    gb_new.board[5][4]=1;
    gb_new.board[3][5]=1;
    cout<<"Result: "<<endl;
    gb_new.printBoard();

    std::vector<std::vector<int>> path;
    gb_new = backtracking_stack(gb_new, path,numValidMoves);
    bool found = gb_new.checkGameWin();
    gb_new.printBoard();
    int numPegs=gb_new.numPegs(); 
    cout << "amount: " << numPegs << " path_length: " << path.size() << endl <<"Found: "<<found<< endl; 
    printPath(path);  
}

void runBestCase(int num)
{
	cout << "Running experiment 3...\n\n";
	
	//bc.printBoard();
	//cout<<"Num: "<<bc.numPegs()<<endl;
	int numValidMoves =0;
    int totalNumPegs =0;
    write_results_to_file(results3_location, results3_header, "");
    
    double total_start = omp_get_wtime();
    
    // increment number of experiments
    for (int i = 1; i <= 36; i=i+1)
    {
    	totalNumPegs=totalNumPegs+i;
        int amount = i;//redundant?
        GameBoard bc=bestCase(amount);;
        if (DEBUG)
        {
        	cout<<"Start State:"<<std::endl;
        	bc.printBoard();
        }
        std::vector<std::vector<int>> path;
        double start = omp_get_wtime();

        // Add what ever being timed here
		bc = backtracking_stack(bc, path,numValidMoves);
        double time = omp_get_wtime() - start;

        bool found = bc.checkGameWin();
        if (DEBUG)
        {
        	cout<<"End State:"<<std::endl;
        	bc.printBoard();
        }



		// Output results
        cout << "amount: " << amount << " path_length: " << path.size() << " time: " << time << " Found: "<< found << endl;
        cout<<"totalNumPegs: "<<totalNumPegs<<"\t numValidMoves: "<<numValidMoves<< endl<<endl;

        // print file line
        ostringstream out;
        //cout<<"Printing"<<std::endl;
        out << amount << "," << path.size() << "," << time << "," <<  found << endl; 
        write_results_to_file(results3_location, out.str());
    }

}
void run_BetterCase(int num)
{

}

void printPath(vector<vector<int>> path)
{
    for (int i = 0; i < (int)path.size(); ++i)
    {
        cout<<"I: "<<i<<'\t'<<"("<<path[i][2]<<","<<path[i][0]<<","<<path[i][1]<<")"<<std::endl;
    }
}

void run_stack_backtracking()
{
    cout << "Running experiment 1...\n\n";
    int numValidMoves =0;
    int totalNumPegs =0;
    write_results_to_file(results1_location, results1_header, "");
    
    double total_start = omp_get_wtime();
    
    // increment number of experiments
    for (int i = 1; i <= 36; i=i+1)
    {
    	totalNumPegs=totalNumPegs+i;
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
		gb_new = backtracking_stack(gb_new, path,numValidMoves);
        double time = omp_get_wtime() - start;

        bool found = gb_new.checkGameWin();
        if (DEBUG)
        {
        	cout<<"End State:"<<std::endl;
        	gb_new.printBoard();
        }



        // Output results
        cout << "amount: " << amount << " path_length: " << path.size() << " time: " << time << " Found: "<< found << endl;
        cout<<"totalNumPegs: "<<totalNumPegs<<"\t numValidMoves: "<<numValidMoves<< endl<<endl;

        // print file line
        ostringstream out;
        //cout<<"Printing"<<std::endl;
        out << amount << "," << path.size() << "," << time << "," <<  found << endl; 
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
        double start = 0.0, time = 0.0;

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
            path = std::vector<Move>();
            start = omp_get_wtime();
            // Add what ever being timed here
            found = backtracking_recursive(gb_new, final_2, path);
            time = omp_get_wtime() - start;
            end_state=2;
        }

        if(found == false)
        {
            gb_new = GameBoard(amount);
            path = std::vector<Move>();
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
        cout << "amount: " << amount << " path_length: " << path.size() << " time: " << time << " Found: " << found << " End State: " << end_state << endl << endl;

        // print file line
        ostringstream out;
        //cout<<"Printing"<<std::endl;
        out << amount << "," << path.size() << "," << time << "," << found << "," << end_state << endl; 
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
            run_stack_backtracking();
        }
        if(contains_string(str, "-bc"))
        {
            runBestCase(24);
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
