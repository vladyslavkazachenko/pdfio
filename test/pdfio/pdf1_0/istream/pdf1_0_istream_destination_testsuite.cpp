#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_0/istream/read_destination.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(DestinationTestSuite, xyz)
{
   pdf1_0::Destination destination;
   std::istringstream istream("[630 0 R /XYZ 200 200 2]");
   EXPECT_TRUE(istream >> destination);
   EXPECT_EQ(pdf1_0::Destination::Type::kXYZ, destination.type());
   EXPECT_EQ(630, destination.xyz().page_.objectNumber());
   EXPECT_EQ(0, destination.xyz().page_.generationNumber());
   EXPECT_EQ(200, destination.xyz().left_);
   EXPECT_EQ(200, destination.xyz().top_);
   EXPECT_EQ(2, destination.xyz().zoom_);
}

TEST(DestinationTestSuite, fit)
{
   pdf1_0::Destination destination;
   std::istringstream istream("[630 0 R /Fit ]");
   EXPECT_TRUE(istream >> destination);
   EXPECT_EQ(pdf1_0::Destination::Type::kFit, destination.type());
   EXPECT_EQ(630, destination.fit().page_.objectNumber());
   EXPECT_EQ(0, destination.fit().page_.generationNumber());
}

TEST(DestinationTestSuite, fitH)
{
   pdf1_0::Destination destination;
   std::istringstream istream("[630 0 R /FitH 200]");
   EXPECT_TRUE(istream >> destination);
   EXPECT_EQ(pdf1_0::Destination::Type::kFitH, destination.type());
   EXPECT_EQ(630, destination.fitH().page_.objectNumber());
   EXPECT_EQ(0, destination.fitH().page_.generationNumber());
   EXPECT_EQ(200, destination.fitH().top_);
}

TEST(DestinationTestSuite, fitV)
{
   pdf1_0::Destination destination;
   std::istringstream istream("[630 0 R /FitV 200]");
   EXPECT_TRUE(istream >> destination);
   EXPECT_EQ(pdf1_0::Destination::Type::kFitV, destination.type());
   EXPECT_EQ(630, destination.fitV().page_.objectNumber());
   EXPECT_EQ(0, destination.fitV().page_.generationNumber());
   EXPECT_EQ(200, destination.fitV().left_);
}

TEST(DestinationTestSuite, fitR)
{
   pdf1_0::Destination destination;
   std::istringstream istream("[630 0 R /FitR 200 200 400 400]");
   EXPECT_TRUE(istream >> destination);
   EXPECT_EQ(pdf1_0::Destination::Type::kFitR, destination.type());
   EXPECT_EQ(630, destination.fitR().page_.objectNumber());
   EXPECT_EQ(0, destination.fitR().page_.generationNumber());
   EXPECT_EQ(200, destination.fitR().left_);
   EXPECT_EQ(200, destination.fitR().bottom_);
   EXPECT_EQ(400, destination.fitR().right_);
   EXPECT_EQ(400, destination.fitR().top_);
}
