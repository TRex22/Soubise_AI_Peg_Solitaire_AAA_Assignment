/*Card class*/

class timings
{
	private:

	public:
		std::vector<double> timing_results;
		std::vector<int> vect;
		int max = 0;
		std::vector<AdjacencyItem> activities;
		int num_times = 0;

		timings();
};

timings::timings()
{
}