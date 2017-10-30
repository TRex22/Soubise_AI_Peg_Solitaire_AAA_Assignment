GameBoard backtracking_stack(GameBoard start, vector<vector<int>> &outPath, int &totalNumPegs, int &numValidMoves)
{
	bool found = false;
	GameBoard current;
	std::vector<Move> path;
	start.getMoves(path);
	current.copy(start);

	std::vector<std::vector<Move>> stackVector;
	std::vector<GameBoard> boardVector;
	stackVector.push_back(path);
	boardVector.push_back(current);

	int numPegs = current.numPegs();
	int i = 1;

	while (found == 0 && i <= numPegs && stackVector.size() > 0 && path.size() > 0)
	{
		path = stackVector.back();
		stackVector.pop_back();
		current.copy(boardVector.back());
		boardVector.pop_back();
		
		//print stuff
		current.printBoard();
		cout << "back tracked path \t V:" << stackVector.size() << "\tP:" << path.size() << endl;

		while (!current.checkGameEnd() && numPegs >= 1 && path.size() > 0) // do the path till no path left
		{
			numPegs = current.numPegs();
			totalNumPegs += numPegs;

			Move mov = path.back();
			path.pop_back();

			if (current.checkIfMoveValid(mov.id, mov.r, mov.c))
			{
				stackVector.push_back(path);
				boardVector.push_back(current);

				numValidMoves++;

				current.makeMove(mov.id, mov.r, mov.c);
				std::vector<int> coord;
				coord.push_back(mov.r);
				coord.push_back(mov.c);
				coord.push_back(mov.id);
				outPath.push_back(coord);

				current.getMoves(path);
				numPegs = current.numPegs();
			}
		}

		numPegs = current.numPegs();
		if (numPegs == 1) //do we need this?
		{
			if (current.checkGameWin())
			{
				found = 1;
				// break;
			} else
			{
				found = 0;
				// break;
			}
		} 
	}

	return current;
}

bool backtracking_recursive(GameBoard start, GameBoard final, vector<Move> path)
{
	bool DEBUG = 0;

	if (start.numPegs() <= final.numPegs())
	{
		return start.equals(final);
	}
	else
	{
		std::vector<Move> moves;
		start.getMoves(moves);
		for (Move J : moves)
		{
			if (DEBUG)
			{
				cout << "TEST in BackTrack:" << endl;
				start.printBoard();
				std::cout << "id: " << J.id << " r: " << J.r << " c: " << J.c << std::endl;
				std::cout << "Check: " << start.checkIfMoveValid(J.id, J.r, J.c) << std::endl;
				std::cout << "Path Size: " << path.size() << std::endl;
			}

			if (start.checkIfMoveValid(J.id, J.r, J.c))
			{
				start.makeMove(J.id, J.r, J.c);
				path.push_back(J);

				bool found = backtracking_recursive(start, final, path);
				if (found)
					return true;
				else
					start.makeReverseMove(J.id, J.r, J.c);
				path.pop_back();
			}
		}
		return false;
	}
}

GameBoard bestCase(int numPegs)
{
	GameBoard bc;
	bc.board[0][2] = 1;
	//bc.printBoard();
	int curR = 0;
	int curC = 2;

	for (int i = 1; i < numPegs; ++i)// for each new peg
	{
		int j = 0;
		bool found = false;
		while (j < 4 && found == false) // try reverse up, right, down, left
		{
			//cout<<"R: "<<curR<<"\t C: "<<curC<<"\t J: "<<j<<endl;
			switch (j)
			{
			case 0: {//reverseUp
				if (curR < 5)
				{
					curR = curR + 2;
					if (bc.checkIfMoveValidReverse(j, curR, curC))
					{
						bc.makeReverseMove(j, curR, curC);
						found = true;
						//cout<<"MOVED up"<<endl;
					} else
					{
						curR = curR - 2;
					}
				}
				break;
			}
			case 1: {//reverseright
				if (curC > 1)
				{
					curC = curC - 2;
					if (bc.checkIfMoveValidReverse(j, curR, curC))
					{
						bc.makeReverseMove(j, curR, curC);
						found = true;
						//cout<<"MOVED right"<<endl;
					} else
					{
						curC = curC + 2;
					}
				}
				break;
			}
			case 2: {//reversedown
				if (curR > 1)
				{
					curR = curR - 2;
					if (bc.checkIfMoveValidReverse(j, curR, curC))
					{
						bc.makeReverseMove(j, curR, curC);
						found = true;
						//cout<<"MOVED down"<<endl;
					} else
					{
						curR = curR + 2;
					}
				}
				break;
			}
			case 3: {//reverseleft
				if (curC < 5)
				{
					curC = curC + 2;
					if (bc.checkIfMoveValidReverse(j, curR, curC))
					{
						bc.makeReverseMove(j, curR, curC);
						found = true;
						//cout<<"MOVED left"<<endl;
					} else
					{
						curC = curC - 2;
					}
				}
				break;
			}
			default: {
				std::cout << "Invalid direcion \n";
				return false;
				break;
			}
			}
			j++;
		}
	}
	return (bc);
}
GameBoard betterCase(int)
{
	vector<Move> path;
	Move current(1, 0, 2);
}