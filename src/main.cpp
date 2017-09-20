/*	
AAA Assignment 2017

Evan Bancroft
Jason Chalom 711985 

*/

/*TODO:
	Cleanup all the excess from my labs
    Timer class

    gnuplot c++ function
    https://stackoverflow.com/questions/2808398/easily-measure-elapsed-time
*/

/* Graph links:
    https://stackoverflow.com/questions/765408/c-free-easy-way-to-draw-graphs-and-charts
    http://www.gnuplot.info/
    http://www.gnuplot.info/links.html
    http://stahlke.org/dan/gnuplot-iostream/
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <omp.h>
#include <time.h>
#include <cmath>
#include <chrono>
#include "omp.h"

#include "helpers.h"
#include "solitaire_board.h"


/* Global variables */
#define app_name "COMS3005 Assignment 2017"
#define results1_header "amount,number_denominations,time"
#define results1_location "./results/results_exp1.csv"
bool DEBUG = false;


/* Headers */
int main(int argc, char *argv[]);
void test();
void run_experiment1();
void process_args(int argc, char *argv[]);


using namespace std;
int main(int argc, char *argv[]) 
{
    print_cmd_heading(app_name);  
    process_args(argc, argv);
cout<<"a thing";

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
}

void run_experiment1()
{
    cout << "Running experiment 1...\n\n";
    write_results_to_file(results1_location, results1_header, "");
    
    double total_start = omp_get_wtime();
    
    // increment change
    for (int i = 1; i <= 1000; i=i+100)
    {
        int amount = i;
        // select denominations from full collection
        for(int j = 1; j < 10; j++)
        {
            double start = omp_get_wtime();

            // Add what ever being timed here

            double time = omp_get_wtime() - start;

            // Output results
            cout << "amount: " << amount << " number_denominations: " << j << " time: " << time << endl << endl;

            // print file line
            ostringstream out;
            out << amount << "," << j << "," << time << endl; 
            write_results_to_file(results1_location, out.str());
        }
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

        if(contains_string(str, "t") || contains_string(str, "test"))
        {
            test();
        }  

        if(contains_string(str, "r1") || contains_string(str, "run1") || contains_string(str, "run") || contains_string(str, "r"))
        {
            run_experiment1();
        }   
    }
}
