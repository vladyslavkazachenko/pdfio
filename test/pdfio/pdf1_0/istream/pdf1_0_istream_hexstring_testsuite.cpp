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