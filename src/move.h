class Move
{
private:

public:
	Move(int id, int x, int y);

	int id;
	int r;
	int c;
};

Move::Move(int id, int x, int y)
{
	this->id = id;
	this->r = x;
	this->c = y;
}