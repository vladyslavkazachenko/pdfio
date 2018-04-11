#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_0/istream/read_string.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(StringTestSuite, emptyStream)
{
	pdf1_0::String string;
	std::istringstream istream;
	EXPECT_FALSE(istream >> string);
	EXPECT_EQ(pdf1_0::String::kNone, string.field_);
}

TEST(HexStringTestSuite, ok1)
{
	pdf1_0::String string;
	std::istringstream istream("<B0DCFF11815D46D2A0723B8B6A07897C>");
	EXPECT_TRUE(istream >> string);
	EXPECT_EQ(pdf1_0::String::kHexString, string.field_);
	EXPECT_TRUE(string.hexString_ == "B0DCFF11815D46D2A0723B8B6A07897C");
}

TEST(HexStringTestSuite, ok2)
{
	pdf1_0::String string;
	std::istringstream istream("(B0DCFF11815D46D2A0723B8B6A07897C)");
	EXPECT_TRUE(istream >> string);
	EXPECT_EQ(pdf1_0::String::kLiteralString, string.field_);
	EXPECT_TRUE(string.literalString_ == "B0DCFF11815D46D2A0723B8B6A07897C");
}