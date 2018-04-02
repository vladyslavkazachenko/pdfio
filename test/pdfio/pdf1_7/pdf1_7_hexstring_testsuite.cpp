#include "gtest/gtest.h"
#include "pdfio/pdf1_7/hexstring.h"

namespace pdf1_7 = pdfio::pdf1_7;

TEST(HexStringTestSuite, defaultCtor)
{
	pdf1_7::HexString hexString;
	EXPECT_EQ(hexString, "");
}

TEST(HexStringTestSuite, assignment)
{
	pdf1_7::HexString hexString;
	hexString = "45fa";
	EXPECT_EQ(hexString, "45fa");
}