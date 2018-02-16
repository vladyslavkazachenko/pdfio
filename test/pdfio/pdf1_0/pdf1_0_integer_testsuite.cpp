#include "pdfio/pdf1_0/integer.h"
#include "gtest/gtest.h"

namespace 
{
	const long long defaultIntegerValue = 0;
	const long long integerValue = 123;
}

namespace pdf1_0 = pdfio::pdf1_0;

TEST(IntegerTestSuite, defaultCtor)
{
	pdf1_0::Integer integer;
	EXPECT_TRUE(integer == defaultIntegerValue);
}

TEST(IntegerTestSuite, ctor)
{
	pdf1_0::Integer integer(integerValue);
	EXPECT_TRUE(integer == integerValue);
	EXPECT_FALSE(integer == defaultIntegerValue);
}

TEST(IntegerTestSuite, copyCtor)
{
	pdf1_0::Integer integer1(integerValue);
	pdf1_0::Integer integer2(integer1);
	EXPECT_TRUE(integer2 == integerValue);
	
	pdf1_0::Integer integer3 = integer1;
	EXPECT_TRUE(integer3 == integerValue);
}

TEST(IntegerTestSuite, assignment)
{
	pdf1_0::Integer integer1;
	integer1 = integerValue;
	EXPECT_TRUE(integer1 == integerValue);
	
	pdf1_0::Integer integer2;
	integer2 = integer1;
	EXPECT_TRUE(integer2 == integerValue);
	EXPECT_TRUE(integer1 == integer2);
}