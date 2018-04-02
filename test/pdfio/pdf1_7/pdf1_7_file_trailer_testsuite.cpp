#include "gtest/gtest.h"
#include "pdfio/pdf1_7/file_trailer.h"

namespace pdf1_7 = pdfio::pdf1_7;

TEST(FileTrailerTestSuite, defaultCtor)
{
	pdf1_7::FileTrailer fileTrailer;
	EXPECT_TRUE(fileTrailer.size() == 0ll);
	EXPECT_FALSE(fileTrailer.hasPrev());
	EXPECT_TRUE(fileTrailer.root().objectNumber() == 0ll);
	EXPECT_TRUE(fileTrailer.root().generationNumber() == 0ll);
	EXPECT_FALSE(fileTrailer.hasInfo());
}