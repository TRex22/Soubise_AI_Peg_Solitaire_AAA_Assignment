GameBoard backtracking_stack(GameBoard start, vector<vector<int>> &outPath)
{
	bool DEBUG = 0;
	GameBoard prev;
	GameBoard current;

	std::vector<Move> path;// moves that should be tried
	path =start.getMoves(path);;
	current.copy(start);

	int numPegs = current.numPegs();
	// !current.checkGameWin() && 
	while(numPegs != 1 && path.size() != 0)
	{
		//play move pop off stack
		Move mov = path.back();
		path.pop_back();

		if (DEBUG)
		{
			cout<<"TEST in BackTrack:"<<endl;
			current.printBoard();
			std::cout<<"id: "<<mov.id<<" r: "<<mov.r<<" c: "<<mov.c<<std::endl;
			std::cout<<"Check: "<<current.checkIfMoveValid(mov.id, mov.r, mov.c)<<std::endl;
			std::cout<<"Path Size: "<<path.size()<<std::endl;
		}
		if(current.checkIfMoveValid(mov.id, mov.r, mov.c))
		{
			prev.copy(current);
			current.makeMove(mov.id, mov.r, mov.c);

			std::vector<int> coord;
			coord.push_back(mov.r);
			coord.push_back(mov.c);
			outPath.push_back(coord);

			path = current.getMoves(path);
		}
		if(DEBUG)
		{
			cout<<"After move:"<<std::endl;
			current.printBoard();
		}

		numPegs = current.numPegs();		
		// if(numPegs == 1)
		// {
		// 	current.setFinal(true);
		// }
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
		moves = start.getMoves(moves);
		for (Move J : moves)
		{
			if (DEBUG)
			{
				cout<<"TEST in BackTrack:"<<endl;
				start.printBoard();
				std::cout<<"id: "<<J.id<<" r: "<<J.r<<" c: "<<J.c<<std::endl;
				std::cout<<"Check: "<<start.checkIfMoveValid(J.id, J.r, J.c)<<std::endl;
				std::cout<<"Path Size: "<<path.size()<<std::endl;
			}

			if(start.checkIfMoveValid(J.id, J.r, J.c))
			{
				start.makeMove(J.id, J.r, J.c);
				path.push_back(J);

				bool found = backtracking_recursive(start, final, path);
				if(found)
					return true;
				else
					start.makeReverseMove(J.id, J.r, J.c);
					path.pop_back();
			}
		}
		return false;
	}
}
