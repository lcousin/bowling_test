#include "../include/bowling.h"
#include<iostream>
#include<numeric>

BowlingScore::BowlingScore(){}

void BowlingScore::reset()
{
	std::vector<Frame*>::iterator it_frame = frames.begin();

	for( ; it_frame!=frames.end() ; ++it_frame)
	{
		delete *it_frame;
	}

	frames.clear();
	frame_score.clear();
}

BowlingScore::~BowlingScore()
{
	reset();
}

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

/** 
* Check the line sequence and fill the frames. 
* @param seq : bowling line to test
* @param test : false draw the errors in the line sequence, true doesn't print errors
*/ 
int BowlingScore::check_sequence(std::string seq, bool test)
{	
	// 0 to 9 in ascii code = 48 to 57
	// X in ascii = 88
	// / in ascii = 47
	// - in ascii = 45

	reset();

	line = seq;
        int status = 0;

	std::vector<char> sequence(line.begin(), line.end());

	int frame_number = 1;
        int additional_throw = 0;

	for(size_t i=0 ; i<sequence.size() ; )
	{
		char current_char = sequence[i];
		char next_char = ' ';
		char next_next_char = ' ';

		if(i+1<sequence.size()) next_char = sequence[i+1];
		if(i+2<sequence.size()) next_next_char = sequence[i+2];	
	
		Frame* current_frame = new Frame();

		if( test_strike(current_char) && frame_number <= 12)
		{
			current_frame->set_strike();
		        current_frame->set_frame_index(frame_number);

			frames.push_back(current_frame);

			if(frame_number == 10) additional_throw = 2; 	// if frame 10 sets two more throws.
			if(frame_number<=10) ++frame_number; 		// limit the frame number to 10.
			else if(frame_number==11) --additional_throw; 	// if frame_number > 10 and strike decrease the additional throws.

			++i;
		}
		else if( test_spare(current_char, next_char) && frame_number <= 10)
		{
				
			// int(char) = ascii code - char of 0 (ascii code 48) to convert char to int :
			current_frame->set_spare(int(current_char)-48);
			current_frame->set_frame_index(frame_number);

			frames.push_back(current_frame);
			
			if(frame_number == 10) additional_throw = 1;
			i += 2;
			++frame_number;
		}
		else if( test_miss(current_char, next_char, next_next_char)  && frame_number <= 10)
		{
			current_frame->set_miss(int(current_char)-48, int(next_char)-48);
			current_frame->set_frame_index(frame_number);

			frames.push_back(current_frame);

			if(frame_number == 10) additional_throw = 0;
			i += 3;
			++frame_number;
		}
		else if( test_last(current_char) && additional_throw > 0 )
		{
			// Last throw treated as a new frame.
			current_frame->set_last_throw(int(current_char)-48);
			current_frame->set_frame_index(frame_number);

			frames.push_back(current_frame);	
			
			++i;
			--additional_throw;
		}
		else
		{
			if(!test) std::cout << " Wrong Sequence : " << current_char << next_char << next_next_char
				  << " Index = " << i << std::endl;

			++status;
			break;
		}	
	}

	if(frame_number < 11) 
	{
		if(!test) std::cout << " Wrong Sequence : only " << frame_number-1 << " correct frames." << std::endl;
		++status;
	}

	if(frame_number == 11 && additional_throw > 0)
	{
		if(!test) std::cout << " Wrong Sequence : missing last throw(s)." << std::endl;
		++status;
	}
	
	if(frame_number == 11 && additional_throw < 0)
	{
		if(!test) std::cout << " Wrong Sequence : incorrect number of last throw(s)." << std::endl;
		++status;
	}

	if(frame_number > 11)
	{
		if(!test) std::cout << " Wrong Sequence : more than 10 frames (" << frame_number-1 << ")" << std::endl;
		++status;
	}

	return status;
}

/** 
* Compute the score of the frames. 
*/ 
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
