#include "gtest/gtest.h"
#include "pdfio/pdf1_7/file_structure.h"

namespace pdf1_7 = pdfio::pdf1_7;
namespace pdf1_0 = pdfio::pdf1_0;

TEST(FileStructureTestSuite, trailer)
{
   pdf1_7::FileStructure::Trailer trailer1;
   EXPECT_EQ(0, trailer1.size());
   EXPECT_FALSE(trailer1.hasPrev());
   EXPECT_FALSE(trailer1.hasRoot());
   EXPECT_FALSE(trailer1.hasEncrypt());
   EXPECT_FALSE(trailer1.hasInfo());
   EXPECT_FALSE(trailer1.hasId());
}

TEST(FileStructureTestSuite, version)
{
   pdf1_7::FileStructure::Version version1;
   EXPECT_TRUE(version1.xrefSection_.subsections().empty());
   EXPECT_EQ(0, version1.trailer_.size());
   EXPECT_FALSE(version1.trailer_.hasPrev());
   EXPECT_FALSE(version1.trailer_.hasRoot());
   EXPECT_FALSE(version1.trailer_.hasEncrypt());
   EXPECT_FALSE(version1.trailer_.hasInfo());
   EXPECT_FALSE(version1.trailer_.hasId());
}

TEST(FileStructureTestSuite, defaultCtor)
{
   pdf1_7::FileStructure fileStruct;
   EXPECT_TRUE(fileStruct.versions_.empty());
}
