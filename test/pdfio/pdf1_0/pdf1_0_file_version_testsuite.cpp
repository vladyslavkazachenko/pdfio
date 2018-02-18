#include "pdfio/pdf1_0/file_version.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(FileVersionTestSuite, defaultCtor)
{
	pdf1_0::FileVersion fileVersion;
	EXPECT_EQ(0, fileVersion.beginOffset());
	EXPECT_EQ(0, fileVersion.endOffset());
	EXPECT_TRUE(fileVersion.xref().section().subsections().empty());
	EXPECT_TRUE(fileVersion.trailer().size() == 0ll);
	EXPECT_FALSE(fileVersion.trailer().hasPrev());
	EXPECT_TRUE(fileVersion.trailer().root().objectNumber() == 0ll);
	EXPECT_TRUE(fileVersion.trailer().root().generationNumber() == 0ll);
	EXPECT_FALSE(fileVersion.trailer().hasInfo());
}

TEST(FileVersionTestSuite, assignment)
{
	pdf1_0::FileVersion fileVersion;
	fileVersion.beginOffset() = 100;
	fileVersion.endOffset() = 1000;
	fileVersion.trailer().size() = 50ll;
	fileVersion.trailer().prev() = 200ll;
	fileVersion.trailer().root().objectNumber() = 5ll;
	fileVersion.trailer().root().generationNumber() = 1ll;
	fileVersion.trailer().info().objectNumber() = 56ll;
	fileVersion.trailer().info().generationNumber() = 2ll;
	EXPECT_EQ(100, fileVersion.beginOffset());
	EXPECT_EQ(1000, fileVersion.endOffset());
	EXPECT_TRUE(fileVersion.xref().section().subsections().empty());
	EXPECT_TRUE(fileVersion.trailer().size() == 50ll);
	EXPECT_TRUE(fileVersion.trailer().hasPrev());
	EXPECT_TRUE(fileVersion.trailer().prev() == 200ll);
	EXPECT_TRUE(fileVersion.trailer().root().objectNumber() == 5ll);
	EXPECT_TRUE(fileVersion.trailer().root().generationNumber() == 1ll);
	EXPECT_TRUE(fileVersion.trailer().hasInfo());
	EXPECT_TRUE(fileVersion.trailer().info().objectNumber() == 56ll);
	EXPECT_TRUE(fileVersion.trailer().info().generationNumber() == 2ll);
}