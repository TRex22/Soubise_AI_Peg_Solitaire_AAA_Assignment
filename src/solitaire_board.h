/*Class header for the game definitions and rules*/
/*Using the European style board layout*/
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
		int row = 0;
		int col = 0;
	
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
	setRow(7);
	setCol(7);

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