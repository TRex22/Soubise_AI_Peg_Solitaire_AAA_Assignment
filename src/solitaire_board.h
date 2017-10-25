/*Class header for the game definitions and rules*/
/*Using the European style board layout
  The European style has no solution if the centre is empty however there are 3 postions where a valid solution is viable
  I will be only using 1 of those positions*/
/*Max 36 pegs in play at a time with 1 missing*/
/* Board's dimensions in a square are 7x7*/
/*12 positions are missing fromthe square, 3 in each corner in a triangle*/
/*Neeed to randomize the peg postions on the board*/
/*	-1 repesents out of bounds area (off board),
	0 repesents empty space
	1 repesents a position with a peg
*/	
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include <string>
#include <random>
#include "omp.h"

using namespace std;

class GameBoard
{
	private:
		int row = 7;
		int col = 7;
	
	public:
		/*varibles*/
		std::vector<std::vector<int>> board;

		/*constructors*/
		GameBoard();
		GameBoard(int num_pegs);

		/*Functions*/
		int getRow();
		int getCol();
		void setRow(int r);
		void setCol(int c);

		void printBoard();
		int numPegs();
		int numMoves();
		std::vector<std::vector<int>> getPegs();

		void euroConfig_Start();
		void euroConfig_Random();
		bool makeMove(int id, int r, int c);
		bool checkIfMoveValid(int id,int r,int c);

		void copy(GameBoard gb);
		bool equals(GameBoard gb);
		std::vector<Move> getMoves(std::vector<Move> path);
		bool checkGameEnd();
		bool checkGameWin();

		bool makeReverseMove(int id, int r, int c);

};

GameBoard::GameBoard()// default empty board exept the corners. 
						//37 0's and 12 (-1)'s
{
	setRow(row);
	setCol(col);

	//init rows of board
	for (int i = 0; i < getRow(); ++i)
	{
		std::vector<int> row;
		for (int j = 0; j < getCol(); ++j)
		{
			if ((i==0)||(i==6))
			{
				if ((j>=2)&&(j<=4))
				{
					row.push_back(0);
				}else
				{
					row.push_back(-1);
				}
			}else if ((i==1)||(i==5))
			{
				if ((j>=1)&&(j<=5))
				{
					row.push_back(0);
				}else
				{
					row.push_back(-1);
				}
			}else
			{
				row.push_back(0);
			}
		}
		board.push_back(row);
	}

}

GameBoard::GameBoard(int num_pegs)//default empty board populated with num_pegs of valid pegs at random positions.
									//num_pegs 1's , 12(-1)'s and (37-num_pegs) 0's
{
	setRow(row);
	setCol(col);

	//init rows of board
	for (int i = 0; i < getRow(); ++i)
	{
		std::vector<int> row;
		for (int j = 0; j < getCol(); ++j)
		{
			if ((i==0)||(i==6))
			{
				if ((j>=2)&&(j<=4))
				{
					row.push_back(0);
				}else
				{
					row.push_back(-1);
				}
			}else if ((i==1)||(i==5))
			{
				if ((j>=1)&&(j<=5))
				{
					row.push_back(0);
				}else
				{
					row.push_back(-1);
				}
			}else
			{
				row.push_back(0);
			}
		}
		board.push_back(row);
	}

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> row_distribution(0,row-1);

	std::random_device rd2;
	std::mt19937 mt2(rd2());
	std::uniform_int_distribution<int> col_distribution(0,col-1);
	for (int i=0; i<num_pegs; i++)
	{
		int rnd_row = row_distribution(mt);
		int rnd_col = col_distribution(mt2);
		//cout<<"I:"<<i<<std::endl<<"Row:"<<rnd_row<<std::endl<<"Col:"<<rnd_col<<std::endl;
		while(true)
		{
			if(board[rnd_row][rnd_col]==0)
			{
				//cout<<"In if"<<std::endl;
				break;
			}else
			{
				//cout<<"In else"<<std::endl;
				rnd_row = row_distribution(mt);
				rnd_col = col_distribution(mt2);
				//cout<<"New Row:"<<rnd_row<<std::endl<<"New Col:"<<rnd_col<<std::endl;
			}
		}
		board[rnd_row][rnd_col]=1;
		//cout<<"Added at Row:"<<rnd_row<<" Col:"<<rnd_col<<std::endl;
	}
}

int GameBoard::getRow()
{
	return row;
}
int GameBoard::getCol()
{
	return col;
}
void GameBoard::setRow(int r)
{
	row = r;
}
void GameBoard::setCol(int c)
{
	col =c;
}

void GameBoard::printBoard()//Prints the current board to console.
{
	cout<<'\n';
	for (int i = 0; i < (int) board.size(); ++i)
	{
		for (int j = 0; j <(int) board[i].size(); ++j)
		{
			cout<<board[i][j]<<'\t';
		}
		cout<<'\n';
	}
	cout<<'\n';
}

int GameBoard::numPegs()//Number of valid pegs on the board
{
	int count=0;
	for (int i = 0; i < (int) board.size(); ++i)
	{
		for (int j = 0; j <(int) board[i].size(); ++j)
		{
			if (board[i][j]==1)
			{
				count =count +1;
			}
		}
	}
	return count;
}

int GameBoard::numMoves()//Total possible number of moves
{
	int numMoves = row*col*numPegs();
	return numMoves;
}

std::vector<std::vector<int>> GameBoard::getPegs()//Retrieves the coordinates of the pegs. pegs[0][0]=r and pegs[0][1]=c of peg 0;
													//pegs[0][2] is direction id
{
	std::vector<std::vector<int>> pegs;
	for(int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if(board[i][j] == 1)
			{
				std::vector<int> coord;
				coord.push_back(i);
				coord.push_back(j);
				coord.push_back(0);
				pegs.push_back(coord);
			}
		}
	}

	return pegs;
}
void GameBoard::euroConfig_Start()//Standard Configuration config
									//36 1's , 1 0 and 12 (-1)'s
{
	for (int i = 0; i < (int) board.size(); ++i)
	{
		for (int j = 0; j <(int) board[i].size(); ++j)
		{
			if ((i==0)&&(j==2))
			{
				board[i][j] =0;
			}else if (board[i][j] ==0)
			{
				board[i][j]=1;
			}
		}
	}
}

void GameBoard::euroConfig_Random()// creates a random state with random number of pegs.
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> distribution(1,100);
	 
	for (int i = 0; i < (int) board.size(); ++i)
	{
		for (int j = 0; j <(int) board[i].size(); ++j)
		{
			if(board[i][j]==0)
			{
			int randNum = distribution(mt);
			board[i][j]=randNum%2;
			}
		}
	}
}

bool GameBoard::makeMove(int id,int r, int c)//Will make the move. MUST RUN checkIfMoveValid OR SEG-FAULTS!!!!
{
	switch(id)
	{
		case 0:	{// up
					board[r][c]=0;
					board[r-1][c]=0;
					board[r-2][c]=1;
					//cout<<"Made move"<<std::endl;
					return true;
					break;					
				}
		case 1:	{//right
					board[r][c] = 0;
					board[r][c+1] = 0;
					board[r][c+2] = 1;
					//cout<<"Made move"<<std::endl;
					return true;
					break;
				}
		case 2:	{// down
					board[r][c]=0;
					board[r+1][c]=0;
					board[r+2][c]=1;
					//cout<<"Made move"<<std::endl;
					return true;
					break;					
				}
		case 3:	{//left
					board[r][c] = 0;
					board[r][c-1] = 0;
					board[r][c-2] = 1;
					//cout<<"Made move"<<std::endl;
					return true;
					break;
				}
		default:{	
					std::cout<<"Invalid ID \n";
					return false;
					break;
				}
				
	}

}
bool GameBoard::checkIfMoveValid(int id, int r,int c)//Given a direction and a pair of coodinates
													 // will check if that move would be valid
{
	switch(id)
	{	
		case 0: {	//up
					if ((r>1)&&(board[r-2][c]==0)&&(board[r-1][c]==1)&&(board[r][c]==1)) // last check might be redundant but be safe
					{
						return true;
						break;
					}else
					{
						//cout <<"Invalid move \n";
						return false;
						break;
					}
				}
		case 1: {//right
					if((c<5)&&(board[r][c+2]==0)&&(board[r][c+1]==1)&&(board[r][c]==1))
					{
						return true;
						break;
					}else
					{
						//cout <<"Invalid move \n";
						return false;
						break;
					}
				}
		case 2: {//down
					if((r<5)&&(board[r+2][c]==0)&&(board[r+1][c]==1)&&(board[r][c]==1))
					{
						return true;
						break;
					}else
					{
						//cout <<"Invalid move \n";
						return false;
						break;
					}
				}
		case 3: {//left
					if((c>1)&&(board[r][c-2]==0)&&(board[r][c-1]==1)&&(board[r][c]==1))
					{
						return true;
						break;
					}else
					{
						//cout <<"Invalid move \n";
						return false;
						break;
					}
				}
		default:{	
					std::cout<<"Invalid ID \n";
					return false;
					break;
				}
	}
}

void GameBoard::copy(GameBoard gb)
{
	this->board = gb.board;
}

bool GameBoard::equals(GameBoard gb)
{
	bool isEqual = true;
	if(this->board.size() != gb.board.size())
		return false;

	for (int i=0; i < row; i++)
	{
		if(this->board[i].size() != gb.board[i].size())
			return false;

		isEqual = std::equal(this->board[i].begin(), this->board[i].end(), gb.board[i].begin());
		if(isEqual == false)
			return false;
	}

	return isEqual;
}

std::vector<Move> GameBoard::getMoves(std::vector<Move> path)//pushes all possible moves of valid pegs onto the path stack.
{
	for (int i=0; i<row; i++)
	{
		for (int j=0; j<col; j++)
		{
			if(board[i][j] == 1)
			{
				int id = 0;
				Move possible_move_up(id, i, j);
				path.push_back(possible_move_up);

				id = 2;
				Move possible_move_down(id, i, j);
				path.push_back(possible_move_down);

				id = 3;
				Move possible_move_left(id, i, j);
				path.push_back(possible_move_left);

				id = 1;
				Move possible_move_right(id, i, j);
				path.push_back(possible_move_right);
			}
		}
	}

	return path;
}

bool GameBoard::checkGameEnd()//Checks the 4 positions (above, below, to the left, to the right) of a peg for another peg.
								//If one exists then we havnt reached an end state yet as there is still a move possible.
{
	std::vector<std::vector<int>> pegs = this->getPegs();
	for (int i = 0; i < (int) pegs.size(); ++i)//for each peg
	{
		if(pegs[i][0]>0)//can check up
			if (board[pegs[i][0]-1][pegs[i][1]]==1)
				return false;

		if(pegs[i][0]<6)//can check down
			if (board[pegs[i][0]+1][pegs[i][1]]==1)
				return false;

		if(pegs[i][1]>0)//can check left
			if (board[pegs[i][0]][pegs[i][1]-1]==1)
				return false;

		if(pegs[i][1]<6)//can check right
			if (board[pegs[i][0]][pegs[i][1]+1]==1)
				return false;
	}
	return true;
}

bool GameBoard::checkGameWin()
{
	std::vector<std::vector<int>> pegs = this->getPegs();

	// end states for European
    // 3:   0,2
    //      1,3
    //      2,3
	bool state1 = pegs.size() == 1 && this->board[0][2] == 1;
	bool state2 = pegs.size() == 1 && this->board[1][3] == 1;
	bool state3 = pegs.size() == 1 && this->board[2][3] == 1;

	// cout<<"State 1: " <<state1<<"State 2: " <<state2<<"State 3: " <<state3<<endl;

	if(state1 || state2 || state3)
	{
		return true;
	}

	return false;
}

bool GameBoard::makeReverseMove(int id, int r, int c)
{
	switch(id)
	{
		case 0:	{// up
					board[r][c]=1;
					board[r-1][c]=1;
					board[r-2][c]=0;
					//cout<<"Made move"<<std::endl;
					return true;
					break;					
				}
		case 1:	{//right
					board[r][c] = 1;
					board[r][c+1] = 1;
					board[r][c+2] = 0;
					//cout<<"Made move"<<std::endl;
					return true;
					break;
				}
		case 2:	{// down
					board[r][c]=1;
					board[r+1][c]=1;
					board[r+2][c]=0;
					//cout<<"Made move"<<std::endl;
					return true;
					break;					
				}
		case 3:	{//left
					board[r][c] = 1;
					board[r][c-1] = 1;
					board[r][c-2] = 0;
					//cout<<"Made move"<<std::endl;
					return true;
					break;
				}
		default:{	
					std::cout<<"Invalid ID \n";
					return false;
					break;
				}
				
	}
}