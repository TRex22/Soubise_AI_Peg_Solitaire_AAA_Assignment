GameBoard backtracking_stack(GameBoard start, vector<vector<int>> &outPath)
{
	bool DEBUG = 0;
	bool found = false;
	bool foundValid =false;
	int counter=0;
	GameBoard current;
	GameBoard prev;
	GameBoard endState;
	std::vector<Move> path;
	std::vector<Move> prevPath;
	path =start.getMoves(path);
	current.copy(start);
	vector<vector<int>> preOutPath;

	int numPegs = current.numPegs();
	int i=1;
	while(found==0  &&	i<=numPegs)
	{
		endState.copy(current);
		counter++;

		//--------------
		if (DEBUG)
		{
			cout<<"TEST IN FIRST WHILE "<<'\t'<<foundValid<<'\t'<<counter<<std::endl;
			current.printBoard();
		}
		//--------------

		if (foundValid==true)
		{
			path=prevPath;
			current.copy(prev);
			outPath=preOutPath;
			foundValid=false;
			
		}else if(current.checkGameEnd()==true)
		{
			break;
		}

		while(!current.checkGameEnd())// do the path till fail
		{
			numPegs = current.numPegs();
			if (path.size()==0)
			{
				break;
			}
			Move mov = path.back();
			path.pop_back();

			//----------------
			if (DEBUG)
			{
				cout<<"TEST in BackTrack:"<<endl;
				current.printBoard();
				std::cout<<"id: "<<mov.id<<" r: "<<mov.r<<" c: "<<mov.c<<std::endl;
				std::cout<<"Check: "<<current.checkIfMoveValid(mov.id, mov.r, mov.c)<<std::endl;
				std::cout<<"Path Size: "<<path.size()<<std::endl;
			}
			//----------------

			if(current.checkIfMoveValid(mov.id, mov.r, mov.c))
			{
				
				foundValid=true;
				prevPath=path;
				prev.copy(current);
				preOutPath=outPath;

				if(DEBUG)
				{
					cout<<"Found valid move at"<<mov.id<<" r: "<<mov.r<<" c: "<<mov.c<<std::endl;
					for (int i = 0; i < (int) prevPath.size(); ++i)
					{
						cout<<"PrevPath: \t"<<i<<" ("<<prevPath[i].r<<","<<prevPath[i].c<<")"<<'\t'<<prevPath[i].id<<std::endl;
					}
				}
				current.makeMove(mov.id, mov.r, mov.c);
				std::vector<int> coord;
				coord.push_back(mov.r);
				coord.push_back(mov.c);
				coord.push_back(mov.id);
				outPath.push_back(coord);

				path = current.getMoves(path);

				//---------------
				if(DEBUG)
				{
					for (int i = 0; i < (int)path.size(); ++i)
					{
						cout<<"P: \t"<<i<<" ("<<path[i].r<<","<<path[i].c<<")"<<'\t'<<path[i].id <<std::endl;
					}
				}
				//--------------
			}

			//--------------
			if(DEBUG)
			{
				cout<<"After move:"<<std::endl;
				current.printBoard();
			}
			//--------------
					
		}	
		int numPegs = current.numPegs();
			if (numPegs==1 || path.size() ==0)//failed 1 peg
			{
				if (current.checkGameWin())
				{
					found =true;
				}else
				{
					break;
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
