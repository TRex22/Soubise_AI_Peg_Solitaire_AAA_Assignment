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


#include "AdjacencyItem.h"
#include "SampleOutput.h"
#include "timings.h"

/*Sample Algorithm Lab 3 Test shit*/
SampleOutput lab3_test_algorithm(std::vector<int> A, int n, int m);

/*Data structures*/
std::vector<int> create_vector(int n);
std::vector<int> create_vector(int n, int biggestSize);
std::vector<int> create_reverse_vector(int n);
std::vector<int> create_reverse_vector(int n, int biggestSize);
std::vector<int> create_rnd_vector(int n);
std::vector<int> create_rnd_vector(int n, int biggestSize);

int* copy_vect_array(int n);

std::vector<int> insert_into_vector_ordered(std::vector<int> vect, int n, int key, int pos);
std::vector<int> insert_into_vector_unique(std::vector<int> vect, int n, int key, int pos);

void print_vector(std::vector<int> vect, int n);
void print_change(std::vector<int> vect, std::vector<int> denominations);

/*Algorithms*/
int linearSearch2(std::vector<int> myList, int n, int key);
int linearSearch2(int* myList, int n, int key);

std::vector<int> swop(std::vector<int> vect, int idex1, int idex2);
std::vector<int> bubbleSort(std::vector<int> vect, int n);
timings bubbleSort_noEscape(std::vector<int> vect, int n);
timings bubbleSort_Escape(std::vector<int> vect, int n);
timings selectionSort(std::vector<int> vect, int n);
timings mergeSort(std::vector<int> vect, int left, int right);
timings improved_mergeSort(std::vector<int> vect, int left, int right);
timings quickSort(std::vector<int> vect, int left, int right);

timings activity_selection();
timings making_change();

/*MISC*/
int random_index(int a, int b);
void halt_execution(string message);
void write_results_to_file (std::string filename, std::string results);
void write_results_to_file (std::string filename, std::string header, std::string results);
void print_cmd_heading(string app_name);

void print_usage(char *argv[]);


#include "helpers.cpp"