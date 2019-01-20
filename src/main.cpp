#include "../include/bowling.h"
#include <string>
#include <iostream>

int main(int argc, char ** argv)
{
	std::cout << std::endl;

	std::cout << "********************************************" << std::endl;
	std::cout << "***                                      ***" << std::endl;
	std::cout << "***        Bowling Score Evaluation      ***" << std::endl;
	std::cout << "***                                      ***" << std::endl;
	std::cout << "********************************************" << std::endl;

	std::cout << std::endl;

	int computed_score;
	std::string seq;

	BowlingScore * score = new BowlingScore();

	if(argc != 2)
	{
		std::cout << "Argument sould be of length 1" << std::endl;
	}
	else
	{
		seq = argv[1];
		std::cout << seq << std::endl;
	}

	if(score->check_sequence(seq) > 0) 
	{
		return 0;
	}

	score->process_sequence();
	computed_score = score->compute_total_score();
		
	std::cout << " Score reached : " << computed_score << std::endl;

	return 0;
}
