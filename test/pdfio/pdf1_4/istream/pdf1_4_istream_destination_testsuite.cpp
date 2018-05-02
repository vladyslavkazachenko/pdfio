#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_4/istream/read_destination.h"

namespace pdf1_4 = pdfio::pdf1_4;

TEST(DestinationTestSuite, fit)
{
   pdf1_4::Destination destination;
   std::istringstream istream("[ 630 0 R /Fit ]");
   EXPECT_TRUE(istream >> destination);
   EXPECT_EQ(pdf1_4::Destination::Type::kFit, destination.type());
   EXPECT_EQ(630, destination.fit().page_.objectNumber());
   EXPECT_EQ(0, destination.fit().page_.generationNumber());
}
