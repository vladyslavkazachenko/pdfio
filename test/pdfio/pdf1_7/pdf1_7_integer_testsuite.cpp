#include "gtest/gtest.h"
#include "pdfio/pdf1_7/integer.h"

namespace 
{
	const long long defaultIntegerValue = 0;
}

namespace pdf1_7 = pdfio::pdf1_7;

TEST(IntegerTestSuite, defaultCtor)
{
	pdf1_7::Integer integer;
	EXPECT_TRUE(integer == defaultIntegerValue);
}