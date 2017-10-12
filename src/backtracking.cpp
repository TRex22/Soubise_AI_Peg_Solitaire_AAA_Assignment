GameBoard backtracking_stack(GameBoard start, std::vector<std::vector<int>> path)
{
	GameBoard prev;
	std::vector<std::vector<int>> pegs = start.getPegs();
	for (std::vector<int> peg : pegs)
	{
		
	}


}

GameBoard backtracking_recursive(GameBoard start, GameBoard prev, std::vector<std::vector<int>> path)
{
	if(start.numPegs() == prev.numPegs())
	{
		return prev; // converged
	}
	else
	{
		std::vector<std::vector<int>> pegs = start.getPegs();
		for (std::vector<int> peg : pegs)
		{
			//up
			GameBoard upCopy;
			upCopy.copy(start);
			int upPegs = upCopy.numPegs();
			cout<<"i: "<<peg[0]<<" j:"<<peg[1]<<" num pegs: "<<start.numPegs()<<" "<<upCopy.numPegs()<<std::endl;
			upCopy.jumpUp(peg[0], peg[1]);

			if(upPegs < upCopy.numPegs())
			{
				std::vector<int> upPeg = peg;
				upPeg[0] = upPeg[0]-2;
				path.push_back(upPeg);
				GameBoard next = backtracking_recursive(upCopy, start, path);

				if(upCopy.numPegs() == next.numPegs())
				{
					return upCopy; // converged
				}
				else
				{
					path.pop_back();
				}
			}

			//down
			GameBoard downCopy;
			downCopy.copy(start);
			int downPegs = downCopy.numPegs();
			downCopy.jumpDown(peg[0], peg[1]);

			if(downPegs < downCopy.numPegs())
			{
				std::vector<int> downPeg = peg;
				downPeg[0] = downPeg[0]+2;
				path.push_back(downPeg);

				GameBoard next = backtracking_recursive(downCopy, start, path);

				if(downCopy.numPegs() == next.numPegs())
				{
					return downCopy; // converged
				}
				else
				{
					path.pop_back();
				}
			}

			//left
			GameBoard leftCopy;
			leftCopy.copy(start);
			int leftPegs = leftCopy.numPegs();
			leftCopy.jumpLeft(peg[0], peg[1]);

			if(leftPegs < leftCopy.numPegs())
			{
				std::vector<int> leftPeg = peg;
				leftPeg[1] = leftPeg[1]-2;
				path.push_back(leftPeg);

				GameBoard next = backtracking_recursive(leftCopy, start, path);

				if(leftCopy.numPegs() == next.numPegs())
				{
					return leftCopy; // converged
				}
				else
				{
					path.pop_back();
				}
			}

			//right
			GameBoard rightCopy;
			rightCopy.copy(start);
			int rightPegs = rightCopy.numPegs();
			rightCopy.jumpRight(peg[0], peg[1]);

			if(rightPegs < rightCopy.numPegs())
			{
				std::vector<int> rightPeg = peg;
				rightPeg[1] = rightPeg[1]+2;
				path.push_back(rightPeg);

				GameBoard next = backtracking_recursive(rightCopy, start, path);

				if(rightCopy.numPegs() == next.numPegs())
				{
					return rightCopy; // converged
				}
				else
				{
					path.pop_back();
				}
			}

			return start;
		}
	}
	// return start;
}

