#include <sstream>

#include "pdfio/pdf1_0/istream/read_file_trailer.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(FileTrailerTestSuite, emptyStream)
{
	pdf1_0::FileTrailer fileTrailer;
	std::istringstream istream;
	EXPECT_FALSE(istream >> fileTrailer);
}

TEST(FileTrailerTestSuite, wrongFirstLine)
{
	pdf1_0::FileTrailer fileTrailer;
	std::istringstream istream("trailerr");
	EXPECT_FALSE(istream >> fileTrailer);
}

TEST(FileTrailerTestSuite, simpleTrailer)
{
	pdf1_0::FileTrailer fileTrailer;
	std::istringstream istream("trailer << /Size 123 /Root 234 1 R >> startxref 456 %%EOF");
	EXPECT_TRUE(istream >> fileTrailer);
	EXPECT_TRUE(fileTrailer.size() == 123ll);
	EXPECT_FALSE(fileTrailer.hasPrev());
	EXPECT_TRUE(fileTrailer.root().objectNumber() == 234ll);
	EXPECT_TRUE(fileTrailer.root().generationNumber() == 1ll);
	EXPECT_FALSE(fileTrailer.hasInfo());
}

TEST(FileTrailerTestSuite, wrongStartxref)
{
	pdf1_0::FileTrailer fileTrailer1;
	std::istringstream istream1("trailer << /Size 123 /Root 234 1 R >>");
	EXPECT_FALSE(istream1 >> fileTrailer1);
	
	pdf1_0::FileTrailer fileTrailer2;
	std::istringstream istream2("trailer << /Size 123 /Root 234 1 R >> startxreff");
	EXPECT_FALSE(istream2 >> fileTrailer2);
}

TEST(FileTrailerTestSuite, wrongXrefOffset)
{
	pdf1_0::FileTrailer fileTrailer1;
	std::istringstream istream1("trailer << /Size 123 /Root 234 1 R >> startxref");
	EXPECT_FALSE(istream1 >> fileTrailer1);
	
	pdf1_0::FileTrailer fileTrailer2;
	std::istringstream istream2("trailer << /Size 123 /Root 234 1 R >> startxref whatever");
	EXPECT_FALSE(istream2 >> fileTrailer2);
}

TEST(FileTrailerTestSuite, wrongEOF)
{
	pdf1_0::FileTrailer fileTrailer1;
	std::istringstream istream1("trailer << /Size 123 /Root 234 1 R >> startxref 543");
	EXPECT_FALSE(istream1 >> fileTrailer1);
	
	pdf1_0::FileTrailer fileTrailer2;
	std::istringstream istream2("trailer << /Size 123 /Root 234 1 R >> startxref 543 EOF");
	EXPECT_FALSE(istream2 >> fileTrailer2);
}

TEST(FileTrailerTestSuite, noSize)
{
	pdf1_0::FileTrailer fileTrailer;
	std::istringstream istream("trailer << /Root 234 1 R >> startxref 456 %%EOF");
	EXPECT_FALSE(istream >> fileTrailer);
}

TEST(FileTrailerTestSuite, noRoot)
{
	pdf1_0::FileTrailer fileTrailer;
	std::istringstream istream("trailer << /Size 123  >> startxref 456 %%EOF");
	EXPECT_FALSE(istream >> fileTrailer);
}