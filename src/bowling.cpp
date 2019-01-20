#include "../include/bowling.h"
#include<iostream>
#include<numeric>

BowlingScore::BowlingScore(){}


bool BowlingScore::test_strike(char c)
{
	if(c == 'X') return true;
	else return false;
}

bool BowlingScore::test_spare(char c0, char c1)
{
	if( int(c0) >= 48 && int(c0) <= 57)
	{
		if(c1 == '/') return true;
		else return false;
	}
	else return false;
}

bool BowlingScore::test_miss(char c0, char c1, char c2)
{
	if( c2 == '-' )
	{
		if( int(c0) >= 47 and int(c0) <= 57 && int(c1) >= 47 && int(c1) <= 57 ) return true;
		else return false;
	}
	else return false;
}

bool BowlingScore::test_last(char c)
{
	if( int(c) >= 48 && int(c) <= 57 ) return true;
	else return false;
}

int BowlingScore::check_sequence(std::string seq)
{	
	// 0 to 9 in ascii code = 48 to 57
	// X in ascii = 88
	// / in ascii = 47
	// - in ascii = 45


	line = seq;
        int status = 0;

	std::vector<char> sequence(line.begin(), line.end());

	int frame_number = 1;
        int additional_throw = -1;

	for(size_t i=0 ; i<sequence.size() ; )
	{
		char current_char = sequence[i];
		char next_char = ' ';
		char next_next_char = ' ';

		if(i+1<sequence.size()) next_char = sequence[i+1];
		if(i+2<sequence.size()) next_next_char = sequence[i+2];	
		
		if( test_strike(current_char) && frame_number <= 12)
		{
			if(frame_number == 10) additional_throw = 2;
			++i;
			++frame_number;
		}
		else if( test_spare(current_char, next_char) && frame_number <= 10)
		{
			if(frame_number == 10) additional_throw = 1;
			i += 2;
			++frame_number;
		}
		else if( test_miss(current_char, next_char, next_next_char)  && frame_number <= 10)
		{
			if(frame_number == 10) additional_throw = 0;
			i += 3;
			++frame_number;
		}
		else if( test_last(current_char) && additional_throw > 0 )
		{
			++i;
			--additional_throw;
		}
		else
		{
			std::cout << " Wrong Sequence : " << current_char << next_char << next_next_char
				  << "  Index = " << i << std::endl;

			// Write the sequence where the error is : to do.

			++status;
			break;
		}	
	}

	if(frame_number < 11) 
	{
		std::cout << " Wrong Sequence : only " << frame_number-1 << " frames." << std::endl;
		++status;
	}
	
	if(frame_number == 11 && additional_throw > 0)
	{
		std::cout << " Wrong Sequence : missing last throw(s)." <<std::endl;
		++status;
	}
	
	return status;
}

void BowlingScore::process_sequence()
{
	std::vector<char> sequence(line.begin(), line.end());

	/*
	for(size_t i=0; i<sequence.size(); ++i)
	{
		std::cout << sequence[i] << std::endl;
	}
	*/

	int counter_index = 1;

	for(size_t i=0; i<sequence.size() && counter_index<=12 ; )
	{
		char current_char = sequence[i];
	 	char next_char = ' ';
		char next_next_char = ' ';

		if(i+1<sequence.size()) next_char = sequence[i+1];
	        if(i+2<sequence.size()) next_next_char = sequence[i+2];	

		Frame* current_frame = new Frame();

		if(current_char == 'X')
		{
			//std::cout << "Frame " << counter_index << " --> Strike" << std::endl;
			
			current_frame->set_strike();
		        current_frame->set_frame_index(counter_index);

			frames.push_back(current_frame);

			++i;
			++counter_index;
		}
		else if(next_char == '/')
		{
			//std::cout << "Frame " << counter_index << " --> Spare !" << std::endl;
			
			// int(char) = ascii code - char of 0 (4ascii code 48) to convert char to int :
			current_frame->set_spare(int(current_char)-48);
			current_frame->set_frame_index(counter_index);

			frames.push_back(current_frame);

			i += 2;
			++counter_index;
		}
		else if(next_next_char == '-' && current_char != 'X' && next_char != 'X' && current_char != '/' && next_char != '/')
		{
			//std::cout << "Frame " << counter_index << " --> Miss !" << std::endl;
			
			current_frame->set_miss(int(current_char)-48, int(next_char)-48);
			current_frame->set_frame_index(counter_index);

			frames.push_back(current_frame);

			i += 3;
			++counter_index;
		}
		else if(counter_index >= 10 and counter_index <= 12)
		{
			//std::cout << "Frame 10 --> Last throws !" << std::endl;
			current_frame->set_last_throw(int(current_char)-48);
			current_frame->set_frame_index(counter_index);

			frames.push_back(current_frame);
			
			++i;
			++counter_index;
		}
		else
		{
			std::cout << "Frame not well detected !" << std::endl;
		        break;
		}
	}
/* 
 	for the tests
	std::cout << "frames = " << frames.size() << std::endl;
	for(size_t j=0; j<frames.size() ; ++j)
	{
		std::cout << frames[j]->get_frame_index() << "  " << frames[j]->get_property() << "  " << frames[j]->get_total_pins_down() << std::endl;
	}
*/
}

int BowlingScore::compute_total_score()
{
	std::vector<Frame*>::iterator it_frame = frames.begin();

	line_score = 0;

	int counter = 0;

	for( ; it_frame!=frames.end() ; )
	{
		++counter;

		int f_score = 0;

		switch( (*it_frame)->get_property() )
		{
			case 0 : // strike
				
				f_score = 10;
				
				if(++it_frame != frames.end() && (*it_frame)->get_frame_index()  <= 10)
				{
					if((*it_frame)->get_property() == 0)
					{
						f_score += 10;
						if(++it_frame != frames.end() && (*it_frame)->get_frame_index()  <= 11)
						{
							f_score += (*it_frame)->get_first_throw();
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

			case 1 : // spare
				
				f_score = 10;

				if(++it_frame != frames.end() && (*it_frame)->get_frame_index() <= 10)
				{
					f_score += (*it_frame)->get_first_throw();
					// No decrementation to go to the next frame
				}
				
				frame_score.push_back(f_score);
				break;
			
			case 2 : // miss
				
				f_score = (*it_frame)->get_total_pins_down();
				frame_score.push_back(f_score);
				
				++it_frame;
				break;

			case 3 : // last throws
				frame_score.push_back((*it_frame)->get_total_pins_down());
				++it_frame;
				break;
		}
	
	}

	//for(size_t i=0; i<frame_score.size() ; ++i) std::cout<<"Frame/Score = " << i << " / " << frame_score[i] << std::endl; // for the tests

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

void Frame::set_miss(int first, int second)
{
	property =  2; // "Miss"
	first_throw = first;
	second_throw = second;
}

void Frame::set_last_throw(int score)
{
	property = 3; // last throw
	first_throw = score;
	second_throw = 0;
}
