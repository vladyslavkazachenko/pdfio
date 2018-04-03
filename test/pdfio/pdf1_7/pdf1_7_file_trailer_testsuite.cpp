#include "gtest/gtest.h"
#include "pdfio/pdf1_7/file_trailer.h"

namespace pdf1_7 = pdfio::pdf1_7;

TEST(FileTrailerTestSuite, defaultCtor)
{
	pdf1_7::FileTrailer fileTrailer;
	EXPECT_TRUE(fileTrailer.size() == 0);
	EXPECT_FALSE(fileTrailer.hasPrev());
	EXPECT_TRUE(fileTrailer.root().objectNumber() == 0);
	EXPECT_TRUE(fileTrailer.root().generationNumber() == 0);
	EXPECT_FALSE(fileTrailer.hasInfo());
	EXPECT_FALSE(fileTrailer.hasID());
}

TEST(FileTrailerTestSuite, id)
{
	pdf1_7::FileTrailer fileTrailer;
	fileTrailer.id()[0] = "3456";
	fileTrailer.id()[1] = "5678";
	EXPECT_EQ(fileTrailer.id()[0], "3456");
	EXPECT_EQ(fileTrailer.id()[1], "5678");
}