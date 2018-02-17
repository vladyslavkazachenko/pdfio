#include "pdfio/pdf1_0/file_trailer.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(FileTrailerTestSuite, defaultCtor)
{
	pdf1_0::FileTrailer fileTrailer;
	EXPECT_TRUE(fileTrailer.size() == 0ll);
	EXPECT_TRUE(fileTrailer.hasPrev());
	EXPECT_TRUE(fileTrailer.prev() == 0ll);
	EXPECT_TRUE(fileTrailer.root().objectNumber() == 0ll);
	EXPECT_TRUE(fileTrailer.root().generationNumber() == 0ll);
	EXPECT_TRUE(fileTrailer.hasInfo());
	EXPECT_TRUE(fileTrailer.info().objectNumber() == 0ll);
	EXPECT_TRUE(fileTrailer.info().generationNumber() == 0ll);
}

TEST(FileTrailerTestSuite, size)
{
	pdf1_0::FileTrailer fileTrailer;
	fileTrailer.size() = 123ll;
	EXPECT_TRUE(fileTrailer.size() == 123ll);
}

TEST(FileTrailerTestSuite, prev)
{
	pdf1_0::FileTrailer fileTrailer;
	fileTrailer.prev() = 234ll;
	EXPECT_TRUE(fileTrailer.prev() == 234ll);
}

TEST(FileTrailerTestSuite, root)
{
	pdf1_0::FileTrailer fileTrailer;
	fileTrailer.root().objectNumber() = 22;
	fileTrailer.root().generationNumber() = 1;
	EXPECT_TRUE(fileTrailer.root().objectNumber() == 22);
	EXPECT_TRUE(fileTrailer.root().generationNumber() == 1);
}

TEST(FileTrailerTestSuite, info)
{
	pdf1_0::FileTrailer fileTrailer;
	fileTrailer.info().objectNumber() = 11;
	fileTrailer.info().generationNumber() = 2;
	EXPECT_TRUE(fileTrailer.info().objectNumber() == 11);
	EXPECT_TRUE(fileTrailer.info().generationNumber() == 2);
}