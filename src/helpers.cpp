/*Jason Chalom 711985
	Helper Functions 2017
*/

/*Random generator for c++11*/
/*	std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,n); // distribution in range [1, 6]*/

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include "omp.h"

using namespace std;

/*MISC*/
int random_index(int a, int b);
void halt_execution(string message);
void write_results_to_file (std::string filename, std::string results);
void write_results_to_file (std::string filename, std::string header, std::string results);
void print_cmd_heading(string app_name);

void print_usage(char *argv[]);

/*MISC*/
int random_index(int a, int b)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(a, b);

	return uni(rng);
}

void halt_execution(string message = "")
{
	cout << message << endl;
	exit(EXIT_FAILURE);
}

void write_results_to_file (std::string filename, std::string results)
{
	ofstream file;
	file.open(filename.c_str(), ios::app);
	file << results;
	file.close();
}

void write_results_to_file (std::string filename, std::string header, std::string results)
{
	ofstream file;
	file.open(filename.c_str(), ios::app);
	file << header << results << endl;
	file.close();
}

void print_cmd_heading(string app_name)
{
	printf("%s\nJason Chalom 711985\nEvan Bancroft 879192\n2017\n\n", app_name.c_str());
}

void print_usage(char *argv[])
{
	printf("At least two parameters must be selected.\n\n");
	printf("usage: %s -rr -m\n", argv[0]);
	printf("Random state -rr\n");
	printf("Full state -rf\n");
	printf("Run Stacked Based Backtracking -rb\n");
	printf("Run Recursive Backtracking -recurse\n");
	printf("Manual -r\n");
	printf("Help -h\n");
}

bool contains_string(string input, string str)
{
	if (input.find(str) != string::npos) {
		return true;
	}
	return false;
}
