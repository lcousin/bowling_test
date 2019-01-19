#include "../include/bowling.h"
#include<iostream>
#include<numeric>

BowlingScore::BowlingScore(){}

int BowlingScore::check_sequence(std::string seq)
{	
	std::vector<std::string> pins{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
	std::vector<std::string> property{"X", "/", "-"};

	line = seq;

        // Check sequence : to do
	//if(sequence[0])
	return 0;
}

void BowlingScore::process_sequence()
{
	std::vector<char> sequence(line.begin(), line.end());

	for(size_t i=0; i<sequence.size(); ++i)
	{
		std::cout << sequence[i] << std::endl;
	}

	int counter_index = 1;

	for(size_t i=0; i<sequence.size() && counter_index<=12 ; )
	{
		char current_char = sequence[i];
	 	char next_char = char(' ');

		if(i+1<sequence.size()) next_char = sequence[i+1];
		
		Frame* current_frame = new Frame();

		if(current_char == char('X'))
		{
			std::cout << "Strike !" << std::endl;
			
			current_frame->set_strike();
		        current_frame->set_frame_index(counter_index);

			frames.push_back(current_frame);

			++i;
			++counter_index;
		}
		else if(next_char == char('/'))
		{
			std::cout << "Spare !" << std::endl;
			
			current_frame->set_spare(int(current_char)-48);
			current_frame->set_frame_index(counter_index);

			frames.push_back(current_frame);

			i += 2;
			++counter_index;
		}
		else if(next_char == char('-'))
		{
			std::cout << "Miss !" << std::endl;
			std::cout << current_char << "  " << int(current_char)-48 << std::endl;		
			current_frame->set_miss(int(current_char)-48);
			current_frame->set_frame_index(counter_index);

			frames.push_back(current_frame);

			i += 2;
			++counter_index;
		}
		else if(counter_index >= 10 and counter_index <= 12)
		{
			std::cout << "Last throws !" << std::endl;
			current_frame->set_last_throw(int(current_char)-48);
			current_frame->set_frame_index(counter_index);

			frames.push_back(current_frame);
			
			++i;
			++counter_index;
		}
	}

	std::cout << "frames = " << frames.size() << std::endl;
	for(size_t j=0; j<frames.size() ; ++j)
	{
		std::cout << frames[j]->get_frame_index() << "  " << frames[j]->get_property() << "  " << frames[j]->get_total_pins_down() << std::endl;
	}

}

int BowlingScore::compute_total_score()
{
	std::vector<Frame*>::iterator it_frame = frames.begin();

	line_score = 0;

	int counter = 0;

	for( ; it_frame!=frames.end() ; )
	{
		std::cout<<counter<<std::endl;
		++counter;

		int f_score = 0;

		switch( (*it_frame)->get_property() )
		{
			case 0 :
				
				f_score = 10;
				
				if(++it_frame != frames.end() && (*it_frame)->get_frame_index()  <= 10)
				{
					if((*it_frame)->get_property() == 0)
					{
						f_score += 10;
						if(++it_frame != frames.end() && (*it_frame)->get_frame_index()  <= 11)
						{
							f_score += 10;
						}
						
						--it_frame; // Just one decrementation to go to the next frame

					}
					else if((*it_frame)->get_property() == 1 || (*it_frame)->get_property() == 2)
					{
						f_score += (*it_frame)->get_total_pins_down();
						//--it_frame;
					}
				}

				frame_score.push_back(f_score);
				break;

			case 1 :
				
				f_score = 10;

				if(++it_frame != frames.end() && (*it_frame)->get_frame_index() <= 10)
				{
					f_score += (*it_frame)->get_first_throw();
					// No decrementation to go to the next frame
				}
				
				frame_score.push_back(f_score);
				break;
			
			case 2 : 
				
				f_score = (*it_frame)->get_total_pins_down();
				frame_score.push_back(f_score);
				
				++it_frame;
				break;

			case 3 : 
				frame_score.push_back((*it_frame)->get_total_pins_down());
				++it_frame;
				break;
		}
	
	}

	line_score = std::accumulate(frame_score.begin(), frame_score.end(), 0);
	
	return line_score;
}

Frame::Frame(){}

void Frame::set_strike()
{
	property = 0; //"Strike"
	first_throw = 10;
	second_throw = 0;
}

void Frame::set_spare(int first) 
{
	property = 1; //"Spare"
	first_throw = first;
	second_throw = 10 - first;
}

void Frame::set_miss(int score)
{
	property =  2; // "Miss"
	first_throw = score;
	second_throw = 0;
}

void Frame::set_last_throw(int score)
{
	property = 3; // last throw
	first_throw = score;
	second_throw = 0;
}
