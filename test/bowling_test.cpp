#include <gtest/gtest.h>
//#include <gmock/gmock.h>
#include "../include/bowling.h"


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

TEST(FULL_SEQ_TEST, TEST_LINE_300)
{
	BowlingScore* score = new BowlingScore();
	
	std::string line = "XXXXXXXXXXXX";
	
	score->check_sequence( line );
	ASSERT_EQ(300, score->compute_total_score() );

	delete score;
}

TEST(FULL_SEQ_TEST, TEST_LINE_150)
{
	BowlingScore* score = new BowlingScore();
	
	std::string line = "5/5/5/5/5/5/5/5/5/5/5";
	
	score->check_sequence( line );
	ASSERT_EQ(150, score->compute_total_score() );

	delete score;
}

TEST(FULL_SEQ_TEST, TEST_LINE_90)
{
	BowlingScore* score = new BowlingScore();
	
	std::string line = "54-54-54-54-54-54-54-54-54-54-";
	
	score->check_sequence( line );
	ASSERT_EQ(90, score->compute_total_score() );

	delete score;
}

TEST(FULL_SEQ_TEST, TEST_LINE_164)
{
	BowlingScore* score = new BowlingScore();
	
	std::string line= "X54-6/36-X9/81-4/XX81";
	
	score->check_sequence( line );
	ASSERT_EQ(164, score->compute_total_score() );

	delete score;
}

TEST(FULL_SEQ_TEST, TEST_LINE_151)
{
	BowlingScore* score = new BowlingScore();
	
	std::string line = "X54-6/36-X9/81-4/XX12";
	
	score->check_sequence( line );
	ASSERT_EQ(151, score->compute_total_score() );

	delete score;
}

TEST(FULL_SEQ_TEST, TEST_LINE_153)
{
	BowlingScore* score = new BowlingScore();
	
	std::string line = "X54-6/36-X9/81-4/X7/6";
	
	score->check_sequence( line );
	ASSERT_EQ(153, score->compute_total_score() );

	delete score;
}

TEST(FULL_SEQ_TEST, TEST_LINE_141)
{
	BowlingScore* score = new BowlingScore();
	
	std::string line = "X54-6/36-X9/81-4/X70-";
	
	score->check_sequence( line );
	ASSERT_EQ(141, score->compute_total_score() );

	delete score;
}


int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
