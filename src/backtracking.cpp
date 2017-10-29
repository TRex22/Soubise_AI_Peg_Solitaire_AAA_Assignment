GameBoard backtracking_stack(GameBoard start, vector<vector<int>> &outPath,int &numValidMoves)
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

	std::vector<std::vector<Move>> stackVector;
	std::vector<GameBoard> boardVector;
	stackVector.push_back(path);
	boardVector.push_back(current);

	int numPegs = current.numPegs();
	int i=1;


		while(found==0  &&	i<=numPegs && stackVector.size()>0)
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
			cout<<"TEST before reset "<<endl;
			//boardVector.back().printBoard();

			path =stackVector.back();
			stackVector.pop_back();
			current.copy(boardVector.back());
			boardVector.pop_back();
			current.printBoard();
			cout<<"back tracked path \t V:"<<stackVector.size()<<"\tP:"<<path.size()<<endl;
			//current.printBoard();
			outPath=preOutPath;				
			
				//cout<<"Breaking"<<endl;

			while(!current.checkGameEnd() && numPegs>=1)// do the path till fail
			{

				numPegs = current.numPegs();
				//cout<<"Breaking with: "<<path.size()<<endl;
				if (path.size()==0)
				{
					cout<<"Breaking2"<<endl;
					break;
				}
				Move mov = path.back();
				path.pop_back();

				//----------------
				if (0)
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
					foundValid=true; // makes the temp at that point
					//prevPath=path;
					stackVector.push_back(path);
					//prev.copy(current);
					boardVector.push_back(current);
					//cout<<"Adding a new path \t N:"<<stackVector.size()<<"\tP:"<<path.size()<<endl;
					//current.printBoard();
					//cout<<"Pushing state to stack"<<endl;

					preOutPath=outPath;
					numValidMoves++;

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
							cout<<"P (new): \t"<<i<<" ("<<path[i].r<<","<<path[i].c<<")"<<'\t'<<path[i].id <<std::endl;
						}
					}
					//--------------
					numPegs = current.numPegs();
				}

				//--------------
				if(0)
				{
					cout<<"After move:"<<std::endl;
					current.printBoard();
				}
				//--------------
						
			}// until stack fails
			int numPegs = current.numPegs();
			if (numPegs==1)
			{
				if(current.checkGameWin())
				{
					found =1;
					break;
				}else
				{
					cout<<"Found alternative soln"<<endl;
					break;
				}
			}else if(path.size()==0)
			{
				break;
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
GameBoard bestCase(int numPegs)
{
	GameBoard bc;
	bc.board[0][2] =1;
	//bc.printBoard();
	int curR=0;
	int curC=2;

	for (int i = 1; i < numPegs; ++i)// for each new peg
	{
		int j=0;
		bool found = false;
		while(j<4 && found ==false)// try reverse up, right, down, left
		{
			//cout<<"R: "<<curR<<"\t C: "<<curC<<"\t J: "<<j<<endl;
			switch(j)
			{
				case 0: {//reverseUp
							if (curR<5)
							{
								curR=curR+2;
								if(bc.checkIfMoveValidReverse(j,curR,curC))
								{
									bc.makeReverseMove(j,curR,curC);
									found = true;
									//cout<<"MOVED up"<<endl;
								}else
								{
									curR=curR-2;
								}
							}
							break;
						}
				case 1: {//reverseright
							if (curC>1)
							{
								curC=curC-2;
								if(bc.checkIfMoveValidReverse(j,curR,curC))
								{
									bc.makeReverseMove(j,curR,curC);
									found = true;
									//cout<<"MOVED right"<<endl;
								}else
								{
									curC=curC+2;
								}
							}
							break;
						}
				case 2: {//reversedown
							if (curR>1)
							{
								curR=curR-2;
								if(bc.checkIfMoveValidReverse(j,curR,curC))
								{
									bc.makeReverseMove(j,curR,curC);
									found = true;
									//cout<<"MOVED down"<<endl;
								}else
								{
									curR=curR+2;
								}
							}
							break;							
						}
				case 3: {//reverseleft
							if (curC<5)
							{
								curC=curC+2;
								if(bc.checkIfMoveValidReverse(j,curR,curC))
								{
									bc.makeReverseMove(j,curR,curC);
									found = true;
									//cout<<"MOVED left"<<endl;
								}else
								{
									curC=curC -2;
								}
							}
							break;
						}
				default:{	
							std::cout<<"Invalid direcion \n";
							return false;
							break;
						}
			}
			j++;
		}
	}
	return(bc);
}
GameBoard betterCase(int)
{
	vector<Move> path;
	Move current(1,0,2);
}