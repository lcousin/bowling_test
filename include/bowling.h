#ifndef __BOWLING_H__
#define __BOWLING_H__

#include <string>
#include <vector>

class Frame
{

	public:

		Frame();
		Frame(int first, int second, int f_number);
		
		int get_first_throw()  {return first_throw;}
		int get_second_throw() {return second_throw;}
		int get_total_pins_down() {return first_throw+second_throw;}

		int get_frame_index() {return frame_index;}
		int get_property() {return property;}

		void set_strike();
		void set_spare(int first);
		void set_miss(int first, int second);
		void set_last_throw(int score);
		
		void set_frame_index(int index) {frame_index = index;}
		
	private:

		int property;
		int frame_index;

		int first_throw;
		int second_throw;
};

class BowlingScore
{

	public:

		BowlingScore();
		~BowlingScore();

		int check_sequence(std::string seq);
                void process_sequence();		
		int compute_total_score();

		bool test_strike(char c);
		bool test_spare(char c0, char c1);
		bool test_miss(char c0, char c1, char c2);
		bool test_last(char c);

	private:

		std::string line;
		std::vector<Frame*> frames;
		std::vector<int> frame_score;
		int line_score;
};

#endif
