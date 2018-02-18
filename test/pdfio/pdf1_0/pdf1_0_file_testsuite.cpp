#include "pdfio/pdf1_0/file.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(FileTestSuite, defaultCtor)
{
	pdf1_0::File file;
	EXPECT_EQ(0, file.latestVersion().beginOffset());
	EXPECT_EQ(0, file.latestVersion().endOffset());
	EXPECT_TRUE(file.latestVersion().xref().section().subsections().empty());
	EXPECT_TRUE(file.latestVersion().trailer().size() == 0ll);
	EXPECT_FALSE(file.latestVersion().trailer().hasPrev());
	EXPECT_TRUE(file.latestVersion().trailer().root().objectNumber() == 0ll);
	EXPECT_TRUE(file.latestVersion().trailer().root().generationNumber() == 0ll);
	EXPECT_FALSE(file.latestVersion().trailer().hasInfo());
}