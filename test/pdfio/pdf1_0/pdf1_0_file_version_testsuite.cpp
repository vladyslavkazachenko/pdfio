#include "pdfio/pdf1_0/file_version.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(FileVersionTestSuite, defaultCtor)
{
	pdf1_0::FileVersion fileVersion;
	EXPECT_EQ(0, fileVersion.beginOffset());
	EXPECT_EQ(0, fileVersion.endOffset());
	EXPECT_TRUE(fileVersion.xref().section().subsections().empty());
	EXPECT_TRUE(fileVersion.trailer().size() == 0);
	EXPECT_FALSE(fileVersion.trailer().hasPrev());
	EXPECT_TRUE(fileVersion.trailer().root().objectNumber() == 0);
	EXPECT_TRUE(fileVersion.trailer().root().generationNumber() == 0);
	EXPECT_FALSE(fileVersion.trailer().hasInfo());
}

TEST(FileVersionTestSuite, assignment)
{
	pdf1_0::FileVersion fileVersion;
	fileVersion.beginOffset() = 100;
	fileVersion.endOffset() = 1000;
	fileVersion.trailer().size() = 50;
	fileVersion.trailer().prev() = 200;
	fileVersion.trailer().root().objectNumber() = 5;
	fileVersion.trailer().root().generationNumber() = 1;
	fileVersion.trailer().info().objectNumber() = 56;
	fileVersion.trailer().info().generationNumber() = 2;
	EXPECT_EQ(100, fileVersion.beginOffset());
	EXPECT_EQ(1000, fileVersion.endOffset());
	EXPECT_TRUE(fileVersion.xref().section().subsections().empty());
	EXPECT_TRUE(fileVersion.trailer().size() == 50);
	EXPECT_TRUE(fileVersion.trailer().hasPrev());
	EXPECT_TRUE(fileVersion.trailer().prev() == 200);
	EXPECT_TRUE(fileVersion.trailer().root().objectNumber() == 5);
	EXPECT_TRUE(fileVersion.trailer().root().generationNumber() == 1);
	EXPECT_TRUE(fileVersion.trailer().hasInfo());
	EXPECT_TRUE(fileVersion.trailer().info().objectNumber() == 56);
	EXPECT_TRUE(fileVersion.trailer().info().generationNumber() == 2);
}