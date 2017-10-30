/*Jason Chalom 711985
	Helper Functions 2017
*/

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


#include "helpers.cpp"