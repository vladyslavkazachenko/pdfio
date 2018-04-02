#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_7/hexstring.h"
#include "pdfio/pdf1_7/istream/read_hexstring.h"
#include "pdfio/pdf1_7/istream/read_array.h"

namespace pdf1_7 = pdfio::pdf1_7;

TEST(ArrayTestSuite, emptyStream)
{
	pdf1_7::Array<pdf1_7::HexString> array;
	std::istringstream istream;
	EXPECT_FALSE(istream >> array);
}

TEST(ArrayTestSuite, ok)
{
	pdf1_7::Array<pdf1_7::HexString> array;
	std::istringstream istream("[ < 81b14aafa313db63dbd6f981e49f94f4 > < 81b14aafa313db63dbd6f981e49f94f4 > ]");
	EXPECT_TRUE(istream >> array);
	EXPECT_EQ(2, array.size());
	EXPECT_EQ(array[0], "81b14aafa313db63dbd6f981e49f94f4");
	EXPECT_EQ(array[1], "81b14aafa313db63dbd6f981e49f94f4");
}