#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_0/istream/read_hexstring.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(HexStringTestSuite, emptyStream)
{
	pdf1_0::HexString hexString;
	std::istringstream istream;
	EXPECT_FALSE(istream >> hexString);
}

TEST(HexStringTestSuite, ok)
{
	pdf1_0::HexString hexString1;
	std::istringstream istream1("<B0DCFF11815D46D2A0723B8B6A07897C>");
	EXPECT_TRUE(istream1 >> hexString1);
  EXPECT_TRUE(hexString1 == "B0DCFF11815D46D2A0723B8B6A07897C");
  
  pdf1_0::HexString hexString2;
	std::istringstream istream2("< B0DCFF11815D46D2A0723B8B6A07897C >");
	EXPECT_TRUE(istream2 >> hexString2);
  EXPECT_TRUE(hexString2 == "B0DCFF11815D46D2A0723B8B6A07897C");
}