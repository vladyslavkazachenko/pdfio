#include "gtest/gtest.h"
#include "pdfio/pdf1_0/real.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(RealTestSuite, defaultCtor)
{
	pdf1_0::Real real;
	EXPECT_EQ(0.0, real);
}

TEST(RealTestSuite, ctor)
{
	pdf1_0::Real real(45.67);
	EXPECT_EQ(45.67, real);
}

TEST(RealTestSuite, assignment)
{
	pdf1_0::Real real;
  real = -45.67;
	EXPECT_EQ(-45.67, real);
}

TEST(RealTestSuite, comparison)
{
	pdf1_0::Real real1, real2;
  real1 = 45.67;
  real2 = 45.67;
	EXPECT_TRUE(real1 == real2);
}
