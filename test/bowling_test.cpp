#include <gtest/gtest.h>
#include "../include/bowling.h"

// Test frame detection : 

TEST(SEQ_TEST, TEST_STRIKE)
{
	BowlingScore* score = new BowlingScore();
	
	ASSERT_TRUE(score->test_strike('X') );
	
	delete score;
}

TEST(SEQ_TEST, TEST_SPARE)
{
	BowlingScore* score = new BowlingScore();

	ASSERT_TRUE(score->test_spare('5','/') );
	
	delete score;
}

TEST(SEQ_TEST, TEST_MISS)
{
	BowlingScore* score = new BowlingScore();

	ASSERT_TRUE(score->test_miss('3','4','-') );

	delete score;
}

TEST(SEQ_TEST, TEST_LAST)
{
	BowlingScore* score = new BowlingScore();

	ASSERT_TRUE(score->test_last('5') );
	
	delete score;
}

// Test wrong sequences :

TEST(WRONG_SEQ_TEST, TEST_LINE_WRONG_LINE)
{
	BowlingScore* score = new BowlingScore();

	std::string wrong_line_0 = "X54-6/36-X9/81-4/XX81/";
 	std::string wrong_line_1 = "X54-6/36-X9/81-4/XX811";
	std::string wrong_line_2 = "X54-6/36-X9/8/81-4/XX81";
	std::string wrong_line_3 = "X54-6/36-X9/81-11-4/XX81/";
	std::string wrong_line_4 = "X54-6/36-X9/814/XX81/";
	std::string wrong_line_5 = "X54-6/36-/X9/81-4/XX81/";
	std::string wrong_line_6 = "X54-6/36--X9/81-4/XX81/";
	std::string wrong_line_7 = "X54-6/36-XX9/81-4/XX81/";
	std::string wrong_line_8 = "X54-6/36-X912/81-4/XX81/";
	std::string wrong_line_9 = "X54-6/36-X9/81-4/X9/811";
	std::string wrong_line_10 = "X54-6/36-X9/81-4/X9/8111";
	std::string wrong_line_11 = "X54-6/36-X9/81-4/X23-81-";
	std::string wrong_line_12 = "X-54-6/36-X9/81-4/X23-";
	std::string wrong_line_13 = "X54-6//36-X9/81-4/X23-";
	std::string wrong_line_14 = "-X54-6/36-X9/81-4/X23-";
	std::string wrong_line_15 = "XX54-6/36-X9/81-4/X23-";
	std::string wrong_line_16 = "X54-6//36-X9/81-4/X5/4";
	std::string wrong_line_17 = "X54-6/36-X9/81-4/X5/a";
	std::string wrong_line_18 = "X54-*/36-X9/81-4/X5/8";
	std::string wrong_line_19 = "X54-";
	std::string wrong_line_20 = " ";
	std::string wrong_line_21 = "azerty";
	std::string wrong_line_22 = ":;!&"; 			// be careful with the "&" on linux
	std::string wrong_line_23 = "X54-6/36-X9/81-4/X9/81-";

	ASSERT_GT( score->check_sequence( wrong_line_0, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_1, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_2, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_3, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_4, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_5, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_6, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_7, true), 0);
	ASSERT_GT( score->check_sequence( wrong_line_8, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_9, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_10, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_11, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_12, true), 0);
	ASSERT_GT( score->check_sequence( wrong_line_13, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_14, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_15, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_16, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_17, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_18, true), 0);
	ASSERT_GT( score->check_sequence( wrong_line_19, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_20, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_21, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_22, true ), 0);
	ASSERT_GT( score->check_sequence( wrong_line_23, true ), 0);

	delete score;
}

// Test some lines with good sequence :

TEST(GOOD_SEQ_TEST, TEST_LINE)
{
	BowlingScore* score = new BowlingScore();
	
	std::string line_0 = "XXXXXXXXXXXX";
	std::string line_1 = "5/5/5/5/5/5/5/5/5/5/5";
	std::string line_2 = "54-54-54-54-54-54-54-54-54-54-";
	std::string line_3 = "X54-6/36-X9/81-4/XX81";
	std::string line_4 = "X54-6/36-X9/81-4/XX12";
	std::string line_5 = "X54-6/36-X9/81-4/X7/6";
	std::string line_6 = "X54-6/36-X9/81-4/X70-";

	score->check_sequence( line_0, false );
	ASSERT_EQ(300, score->compute_total_score() );

	score->check_sequence( line_1, false );
	ASSERT_EQ(150, score->compute_total_score() );
	
	score->check_sequence( line_2, false );
	ASSERT_EQ(90, score->compute_total_score() );
	
	score->check_sequence( line_3, false );
	ASSERT_EQ(164, score->compute_total_score() );
	
	score->check_sequence( line_4, false );
	ASSERT_EQ(151, score->compute_total_score() );
	
	score->check_sequence( line_5, false );
	ASSERT_EQ(153, score->compute_total_score() );
	
	score->check_sequence( line_6, false );
	ASSERT_EQ(141, score->compute_total_score() );


	delete score;
}

int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
