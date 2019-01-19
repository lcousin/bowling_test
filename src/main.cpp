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
	std::cout << std::endl;

	int computed_score;
	std::string seq;
	bool non_valid = false;

	//do {
		// blah blah to define X / and -

		if(argc != 2)
		{
			std::cout << "Argument sould be of length 1" << std::endl;
			non_valid = true;
		}
		else
		{
			seq = argv[1];
			std::cout << seq << std::endl;
		}

		if(non_valid)
		{
			std::cout << "	Enter a bowling sequence or [q] to quit : " << std::endl;
			std::cin >> seq;
		}

		BowlingScore * score = new BowlingScore();

		//if(score->check_sequence(seq) != 0) continue;
		score->check_sequence(seq);

		score->process_sequence();
		computed_score = score->compute_total_score();
		
		std::cout << " Score reached : " << computed_score << std::endl;


	//} while(seq!="q");
	
	return 0;
}
