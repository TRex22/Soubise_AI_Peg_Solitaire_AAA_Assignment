GameBoard backtracking_stack(GameBoard start,vector<vector<int>> &outPath)
{
	GameBoard prev;
	GameBoard current;

	std::vector<Move> path;// moves that should be tried
	path =start.getMoves(path);
	//std::vector<std::vector<int>> pegs = start.getPegs();
	current.copy(start);

	while(!current.checkGameEnd2())
	{
		//play move pop off stack
		Move mov = path.back();
		path.pop_back();

		//cout<<"TEST in BT:"<<endl;
		//current.printBoard();
		//std::cout<<"id: "<<mov.id<<" r: "<<mov.r<<" c: "<<mov.c<<std::endl;
		//std::cout<<"Check: "<<current.checkIfMoveValid(mov.id, mov.r, mov.c)<<std::endl;
		//std::cout<<"Path Size: "<<path.size()<<std::endl;

		if(current.checkIfMoveValid(mov.id, mov.r, mov.c))
		{
			//cout<<"TEST VALID"<<std::endl;
			prev.copy(current);
			current.makeMove(mov.id, mov.r, mov.c);

			std::vector<int> coord;
			coord.push_back(mov.r);
			coord.push_back(mov.c);
			outPath.push_back(coord);

			path = current.getMoves(path);
			//cout<<"finished"<<std::endl;
		}
		//cout<<"TEST after pos move...."<<std::endl;
		//current.printBoard();

		if(path.size() < 1)
			break;
		//cout<<current.checkGameEnd2()<<std::endl;
	}

	return current;
}
