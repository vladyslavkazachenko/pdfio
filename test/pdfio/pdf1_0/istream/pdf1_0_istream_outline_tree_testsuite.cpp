#include <sstream>

#include "pdfio/pdf1_0/istream/read_outline_tree.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(OutlineTreeTestSuite, emptyStream)
{
   pdf1_0::OutlineTree outlineTree;
   std::istringstream istream;
   EXPECT_FALSE(istream >> outlineTree);
}

TEST(OutlineTreeTestSuite, ok1)
{
   pdf1_0::OutlineTree outlineTree;
   std::istringstream istream(
      "<<"
      "/Count 6"
      "/First 22 0 R"
      "/Last 29 0 R"
      ">>");
   EXPECT_TRUE(istream >> outlineTree);
   EXPECT_TRUE(outlineTree.hasCount());
   EXPECT_EQ(6, outlineTree.count());
   EXPECT_TRUE(outlineTree.hasFirst());
   EXPECT_EQ(22, outlineTree.first().objectNumber());
   EXPECT_EQ(0, outlineTree.first().generationNumber());
   EXPECT_TRUE(outlineTree.hasLast());
   EXPECT_EQ(29, outlineTree.last().objectNumber());
   EXPECT_EQ(0, outlineTree.last().generationNumber());
}