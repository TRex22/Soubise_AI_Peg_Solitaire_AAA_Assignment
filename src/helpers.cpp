/*Jason Chalom 711985
	Helper Functions 2017
*/

/*Random generator for c++11*/
/*	std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,n); // distribution in range [1, 6]*/


/*Sample Algorithm Lab 3 Test shit*/
SampleOutput lab3_test_algorithm(std::vector<int> A, int n, int m)
{
	SampleOutput out(n, m);
	out.C.reserve(m);
	out.B.reserve(n);

	for (int i = 0; i < n; i++)
	{
		out.B[i] = -33;
		// out.C[i] = -33;
	}

	for (int i = 0; i < m; i++)
	{
		out.C[i] = 0;
	}

	for (int i = 0; i < n; i++)
	{
		out.C[A[i]-1] = out.C[A[i]-1] + 1;
	}

	for (int i = 1; i < m; i++)
	{
		out.C[i] = out.C[i] + out.C[i-1];
	}

	for (int i = n-1; i >= 0; i--)
	{
		out.B[out.C[A[i]-1]] = A[i]-1;
		out.C[A[i]-1] = out.C[A[i]-1] - 1;
	}

	return out;
}

/*Data structures*/
std::vector<int> create_vector(int n)
{
	std::vector<int> vect(n);

	if (n < 1)
		return vect;

    vect.reserve(n);

	//distinct
	for (int i = 0; i < n; i++)
	{
		vect[i] = i+1;
	}

	return vect;
}

std::vector<int> create_vector(int n, int biggestSize)
{
	std::vector<int> vect(n);

	if (n < 1)
		return vect;

    vect.reserve(biggestSize);

	//distinct
	for (int i = 0; i < n; i++)
	{
		vect[i] = i+1;
	}

	return vect;
}

std::vector<int> create_reverse_vector(int n)
{
	std::vector<int> vect(n);

	if (n < 1)
		return vect;

    vect.reserve(n);

	//distinct
	for (int i = 0; i < n; i++)
	{
		vect[i] = n-i;
	}

	return vect;
}

std::vector<int> create_reverse_vector(int n, int biggestSize)
{
	std::vector<int> vect(n);

	if (n < 1)
		return vect;

    vect.reserve(biggestSize);

	//distinct
	for (int i = 0; i < n; i++)
	{
		vect[i] = n-i;
	}

	return vect;
}

std::vector<int> create_rnd_vector(int n)
{
	std::vector<int> vect(n);

	if (n < 1)
		return vect;

    vect.reserve(n);

	for (int i = 0; i < n; i++)
	{
		vect[i] = i+1;
	}
	
	std::random_shuffle (vect.begin(), vect.end());

	return vect;
}

std::vector<int> create_rnd_vector(int n, int biggestSize)
{
	std::vector<int> vect(n);
	if (n < 1)
		return vect;

    vect.reserve(biggestSize);

	for (int i = 0; i < n; i++)
	{
		vect[i] = i+1;
	}
	
	std::random_shuffle (vect.begin(), vect.end());

	return vect;
}

std::vector<int> insert_into_vector_ordered(std::vector<int> vect, int n, int key, int pos)
{
	if(pos < n)
	{
		vect[key] = vect[pos];
		vect[pos] = key;
	}

	return vect;
}

std::vector<int> insert_into_vector_unique(std::vector<int> vect, int n, int key, int pos)
{
	if(pos < n)
	{
		//find the other element and swap with current position
		for (int i = 0; i < n; i++)
		{
			if(vect[i] == key)
			{
				vect[i] = vect[pos];
			}
		}

		vect[pos] = key;
	}

	return vect;
}

void print_vector(std::vector<int> vect, int n)
{
	ostringstream out;
    
	for (int i = 0; i < n; i++)
	{
		out << vect[i] << " ";
	}

	out << endl;
	cout << out.str();
}

void print_change(std::vector<int> vect, std::vector<int> denominations)
{
	for (unsigned int i = 0; i<denominations.size(); i++)
    {
        cout<<denominations[i]<<" ";
    }
    cout<<endl;

    print_vector(vect, vect.size());
}

/*Algorithms*/

int linearSearch2(std::vector<int> myList, int n, int key)
{
	int index = 0;

	while (key != myList[index] && index < n)
	{
		index = index + 1;
	}

	return index;
}

int linearSearch2(int* myList, int n, int key)
{
	int index = 0;

	while (key != myList[index] && index < n)
	{
		index = index + 1;
	}

	return index;
}

std::vector<int> swop(std::vector<int> vect, int idex1, int idex2)
{
	int temp = vect[idex1];
	vect[idex1] = vect[idex2];
	vect[idex2] = temp;

	return vect;
}

std::vector<int> bubbleSort(std::vector<int> vect, int n)
{
	for (int i = n-1; i != 0; i--)
	{
		for (int j = 0; j != i; j++)
		{
			if (vect[j] > vect[j+1])
			{
				// iter_swap(vect.begin() + j, vect.begin() + j+1);
				vect = swop(vect, j, j+1);
			}
		}
	}

	return vect;
}

timings bubbleSort_noEscape(std::vector<int> vect, int n)
{
	timings results;

	double swap_time = 0.0;
	double comparison_time = 0.0;
	results.num_times = 2; 

	for (int i = n-1; i != 0; i--)
	{
		for (int j = 0; j != i; j++)
		{
			double start_c = omp_get_wtime();
			if (vect[j] > vect[j+1])
			{
				double start_s = omp_get_wtime();
				// iter_swap(vect.begin() + j, vect.begin() + j+1);
				vect = swop(vect, j, j+1);
				swap_time += omp_get_wtime() - start_s;
			}
			comparison_time += omp_get_wtime() - start_c;
		}
	}

	comparison_time -= swap_time;
	// cout << "swap: " << swap_time << "comp: " << comparison_time << endl;
	results.timing_results.push_back(swap_time);
	results.timing_results.push_back(comparison_time);
	results.vect = vect;
	return results;
}

timings bubbleSort_Escape(std::vector<int> vect, int n)
{
	timings results;

	double swap_time = 0.0;
	double comparison_time = 0.0;
	results.num_times = 2; 

	int i = n-1;
	bool sorting = true;
	bool swopped = false;

	while (i >= 1 && sorting == true)
	{
		swopped = false;

		for (int j = 0; j != i; j++)
		{
			double start_c = omp_get_wtime();
			if(vect[j] > vect[j+1])
			{
				double start_s = omp_get_wtime();
				// iter_swap(vect.begin() + j, vect.begin() + j+1);
				vect = swop(vect, j, j+1);
				swap_time += omp_get_wtime() - start_s;

				swopped = true;
			}
			comparison_time += omp_get_wtime() - start_c;
		}

		if(swopped == false)
		{
			sorting = false;
			// cout << "BREAK!" << endl;
		}
		else
		{
			i--;
		}
	}

	comparison_time -= swap_time;
	results.timing_results.push_back(swap_time);
	results.timing_results.push_back(comparison_time);
	results.vect = vect;
	return results;
}

timings selectionSort(std::vector<int> vect, int n)
{
	timings results;

	double swap_time = 0.0;
	double comparison_time = 0.0;
	results.num_times = 2; 

	for (int i = n-1; i >= 1; i--)
	{
		for (int j = 0; j <= i-1; j++)
		{
			if(vect[j] > vect[j+1])
			{
				int tmp = vect[j];
				vect[j] = vect[j+1];
				vect[j+1] = tmp;
			}
		}
	}

	comparison_time -= swap_time;
	results.timing_results.push_back(swap_time);
	results.timing_results.push_back(comparison_time);
	results.vect = vect;
	return results;
}

//0, n-1
timings mergeSort(std::vector<int> vect, int left, int right)
{
	timings results;

	double swap_time = 0.0;
	double comparison_time = 0.0;
	results.num_times = 2; 

	if(right-left > 0)
	{
		vector<int> temp(vect.size());
		int mid = (left + right)/2;
		mergeSort(vect, left, mid);
		mergeSort(vect, mid + 1, right);

		for(int i = mid;i >= left;i--)
		{
			temp[i] = vect[i];
		}

		for(int j = mid+1;j <= right;j++)
		{
			temp[right + mid+1 - j] = vect[j];
		}

		int i = left;
		int j = right;

		for(int k = left;k <= right;k++)
		{
			if(temp[i] < temp[j])
			{
				vect[k] = temp[i];
				i++;
			}

			else
			{
				vect[k] = temp[j];
				j--;
			}
		}
	}

	comparison_time -= swap_time;
	results.timing_results.push_back(swap_time);
	results.timing_results.push_back(comparison_time);
	results.vect = vect;
	return results;
}

timings improved_mergeSort(std::vector<int> vect, int left, int right)
{
	timings results;

	double swap_time = 0.0;
	double comparison_time = 0.0;
	results.num_times = 2; 

	if(right-left > 0)
	{
		vector<int> temp(vect.size());
		int mid = (left + right)/2;
		improved_mergeSort(vect, left, mid);
		improved_mergeSort(vect, mid + 1, right);

		for(int i = mid;i >= left;i--)
		{
			temp[i] = vect[i];
		}

		for(int j = mid+1;j <= right;j++)
		{
			temp[right + mid+1 - j] = vect[j];
		}

		int i = left;
		int j = right;
		if(temp[mid] > temp[right])
		{  //the merge does not need to happen if the end of the first sub vect of smaller than the beginning of the second sub vect.
			for(int k = left;k <= right;k++)
			{
				if(temp[i] < temp[j])
				{
					vect[k] = temp[i];
					i++;
				}

				else
				{
					vect[k] = temp[j];
					j--;
				}
			}
		}
	}

	comparison_time -= swap_time;
	results.timing_results.push_back(swap_time);
	results.timing_results.push_back(comparison_time);
	results.vect = vect;
	return results;
}

timings quickSort(std::vector<int> vect, int left, int right)
{
	timings results;

	double swap_time = 0.0;
	double comparison_time = 0.0;
	results.num_times = 2; 

	if(right > left)
	{
		int v = vect[right];
		int i = left;
		int j = right;
		int t;
		
		while(i < j)
		{
		
			while(vect[i] < v)
			{
				i++;
			}
			
			while(j > i && vect[j] >= v)
			{
				j--;
			}
			
			if(j > i)
			{
				t = vect[i];
				vect[i] = vect[j];
				vect[j] = t;
			}
		}
		
		t = vect[i];
		vect[i] = vect[right];
		vect[right] = t;
	
		quickSort(vect, left, i-1);
		quickSort(vect, i+1, right);
	}

	comparison_time -= swap_time;
	results.timing_results.push_back(swap_time);
	results.timing_results.push_back(comparison_time);
	results.vect = vect;
	return results;
}

timings activity_selection()
{
	timings results;
	results.num_times = 2; 

	std::vector<AdjacencyItem> list;
	AdjacencyItem ai(0, 5);
	list.push_back(ai);
	AdjacencyItem ai2(3, 7);
	list.push_back(ai2);
	AdjacencyItem ai3(5, 9);
	list.push_back(ai3);
	AdjacencyItem ai4(4, 10);
	list.push_back(ai4);

	AdjacencyItem activity = list[0];
	int max = 1;

	for(unsigned int i = 1; i < list.size(); i++)
	{
		AdjacencyItem tmpActivity = list[i];
		if(tmpActivity.startTime >= activity.endTime)
		{
			max++;
			activity = tmpActivity;
		}
	}

	results.max = max;
	results.activities = list;
	return results;
}

timings making_change(int amount, int num_denom, std::vector<int> denominations)
{
	timings results;
	results.num_times = 2;
	std::vector<int> change(num_denom);
	change.reserve(num_denom); 

	int tmpAmount = amount;
	for (int i = denominations.size()-1; i > -1; i--)
	{
		change[i] = tmpAmount/denominations[i];
		tmpAmount = tmpAmount - (change[i]*denominations[i]);
	}

	results.vect = change;
	return results;
}

/*MISC*/
int random_index(int a, int b)
{
	std::random_device rd;
	std::mt19937 rng(rd());    
	std::uniform_int_distribution<int> uni(a, b); 

	return uni(rng);
}

void halt_execution(string message="")
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
    printf("At least two parameters must be selected.\n-1 will denote inf value\n\n");
    printf("usage: %s -t -r1\n", argv[0]);
    printf("test -t\n");
    printf("run -r\n");
}

bool contains_string(string input, string str)
{
    if (input.find(str) != string::npos) {
        return true;
    } 
    return false;
}
