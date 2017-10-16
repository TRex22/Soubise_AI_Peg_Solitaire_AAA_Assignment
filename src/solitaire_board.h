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


/*personal notes*/
// Currently using square multi vector but since im using vectors, dont need to be a square... i think.... use square for now

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
		std::vector<std::vector<int> > board;

		/*Functions*/
		int getRow();
		int getCol();
		void setRow(int r);
		void setCol(int c);

		GameBoard();
		void printBoard();
		void euroConfig_Start();
		void euroConfig_Random();
		int numPegs();
		int numMoves();
		bool makeMove(int id,int r, int c);
		bool checkIfMoveValid(int id,int r,int c);
		std::vector<std::vector<int>> getPegs();
		void copy(GameBoard gb);

};

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

GameBoard::GameBoard()// default empty board
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
void GameBoard::euroConfig_Start()//------Standard Configuration config
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
void GameBoard::printBoard()
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
void GameBoard::euroConfig_Random()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> distribution(1,100);
	 
	cout<<'\n';
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
		cout<<'\n';
	}
	cout<<'\n';
}

bool GameBoard::makeMove(int id,int r, int c)
{
	switch(id)
	{
		case 0:	{// up
					board[r][c]=0;
					board[r-1][c]=0;
					board[r-2][c]=1;
					return true;
					break;					
				}
		case 1:	{//right
					board[r][c] = 0;
					board[r][c+1] = 0;
					board[r][c+2] = 1;
					return true;
					break;
				}
		case 2:	{// down
					board[r][c]=0;
					board[r+1][c]=0;
					board[r+2][c]=1;
					return true;
					break;					
				}
		case 3:	{//left
					board[r][c] = 0;
					board[r][c-1] = 0;
					board[r][c-2] = 1;
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
bool GameBoard::checkIfMoveValid(int id,int r,int c)
{
	switch(id)
	{
		case 0: {
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
		case 1: {
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
		case 2: {
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
		case 3: {
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

int GameBoard::numPegs()
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

int GameBoard::numMoves()
{
	int numMoves = row*col*numPegs();
	return numMoves;
}

std::vector<std::vector<int>> GameBoard::getPegs()
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
				pegs.push_back(coord);
			}
		}
	}

	return pegs;
}

void GameBoard::copy(GameBoard gb)
{
	this->board = gb.board;
}