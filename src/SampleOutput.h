class SampleOutput
{
	private:

	public:
		std::vector<int> B;
		std::vector<int> C;

		SampleOutput(int n, int m);
};

SampleOutput::SampleOutput(int n, int m)
{
	std::vector<int> b(m);
	std::vector<int> c(n);

	this->B = b;
	this->C = c;
}