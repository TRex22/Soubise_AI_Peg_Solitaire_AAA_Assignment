/*Class header for the game definitions and rules*/

class GameBoard
{
	private:
		int row = 0;
		int col = 0;
	
	public:
		int getRow();

};

int GameBoard::getRow()
{
	return row;
}
