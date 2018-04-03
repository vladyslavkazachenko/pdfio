#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_0/istream/read_real.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(RealTestSuite, emptyStream)
{
	pdf1_0::Real real;
	std::istringstream istream;
	EXPECT_FALSE(istream >> real);
}