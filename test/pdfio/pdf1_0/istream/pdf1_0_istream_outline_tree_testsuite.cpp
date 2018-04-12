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

TEST(OutlineTreeTestSuite, entry_emptyStream)
{
   pdf1_0::OutlineTree::Entry entry;
   std::istringstream istream;
   EXPECT_FALSE(istream >> entry);
}

TEST(OutlineTreeTestSuite, entry_ok1)
{
   pdf1_0::OutlineTree::Entry entry;
   std::istringstream istream(
      "<<"
      "/Parent 21 0 R"
      "/Dest [ 3 0 R /Top 0 792 0 ]"
      "/Title (Document)"
      "/Next 29 0 R"
      "/First 25 0 R"
      "/Last 28 0 R"
      "/Count 4"
      ">>");
   EXPECT_TRUE(istream >> entry);
   EXPECT_EQ(21, entry.parent().objectNumber());
   EXPECT_EQ(0, entry.parent().generationNumber());
	EXPECT_EQ(pdf1_0::String::kLiteralString, entry.title().field_);
   EXPECT_TRUE(entry.title().literalString_ == "Document");
   EXPECT_TRUE(entry.hasNext());
   EXPECT_EQ(29, entry.next().objectNumber());
   EXPECT_EQ(0, entry.next().generationNumber());
   EXPECT_TRUE(entry.hasCount());
   EXPECT_EQ(4, entry.count());
   EXPECT_TRUE(entry.hasFirst());
   EXPECT_EQ(25, entry.first().objectNumber());
   EXPECT_EQ(0, entry.first().generationNumber());
   EXPECT_TRUE(entry.hasLast());
   EXPECT_EQ(28, entry.last().objectNumber());
   EXPECT_EQ(0, entry.last().generationNumber());
}