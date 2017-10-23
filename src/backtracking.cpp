GameBoard backtracking_stack(GameBoard start,vector<vector<int>> &outPath)
{
	bool DEBUG =0;
	GameBoard prev;
	GameBoard current;

	std::vector<Move> path;// moves that should be tried
	path =start.getMoves(path);;
	current.copy(start);

	while(!current.checkGameEnd())
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
		if(path.size() < 1)
			break;
	}

	return current;
}
