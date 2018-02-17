#include <sstream>

#include "pdfio/pdf1_0/istream/read_integer.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(IntegerTestSuite, emptyStream)
{
	pdf1_0::Integer integer;
	std::istringstream istream;
	EXPECT_FALSE(istream >> integer);
}

TEST(IntegerTestSuite, simpleInteger)
{
	pdf1_0::Integer integer1;
	std::istringstream istream1("12345");
	EXPECT_TRUE(istream1 >> integer1);
	EXPECT_TRUE(integer1 == 12345ll);
	
	pdf1_0::Integer integer2;
	std::istringstream istream2("-12345");
	EXPECT_TRUE(istream2 >> integer2);
	EXPECT_TRUE(integer2 == -12345ll);
}

TEST(IntegerTestSuite, wrongInteger)
{
	pdf1_0::Integer integer1;
	std::istringstream istream1("whatever");
	EXPECT_FALSE(istream1 >> integer1);
}