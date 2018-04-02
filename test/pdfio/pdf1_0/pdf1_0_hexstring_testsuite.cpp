#include "gtest/gtest.h"
#include "pdfio/pdf1_0/hexstring.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(HexStringTestSuite, defaultCtor)
{
	pdf1_0::HexString hexString;
	EXPECT_EQ(hexString, "");
}

TEST(HexStringTestSuite, assignment)
{
	pdf1_0::HexString hexString;
	hexString = "45fa";
	EXPECT_EQ(hexString, "45fa");
}