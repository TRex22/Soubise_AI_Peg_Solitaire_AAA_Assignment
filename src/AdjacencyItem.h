class AdjacencyItem
{
	private:

	public:
		int startTime = 0;
		int endTime = 0;

		AdjacencyItem(int start, int end);
};

AdjacencyItem::AdjacencyItem(int start, int end)
{
	this->startTime = start;
	this->endTime = end;
}