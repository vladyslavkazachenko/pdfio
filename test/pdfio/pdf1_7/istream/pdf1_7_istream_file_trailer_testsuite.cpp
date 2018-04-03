#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_7/istream/read_file_trailer.h"

namespace pdf1_7 = pdfio::pdf1_7;

TEST(FileTrailerTestSuite, emptyStream)
{
	pdf1_7::FileTrailer fileTrailer;
	std::istringstream istream;
	EXPECT_FALSE(istream >> fileTrailer);
}

TEST(FileTrailerTestSuite, wrongFirstLine)
{
	pdf1_7::FileTrailer fileTrailer;
	std::istringstream istream("trailerr");
	EXPECT_FALSE(istream >> fileTrailer);
}

TEST(FileTrailerTestSuite, simpleTrailer)
{
	pdf1_7::FileTrailer fileTrailer;
	std::istringstream istream("trailer << /Size 22 /Root 2 0 R /Info 1 0 R /ID [ < 81b14aafa313db63dbd6f981e49f94f4 > < 81b14aafa313db63dbd6f981e49f94f4 > ] >> startxref 18799 %%EOF");
	EXPECT_TRUE(istream >> fileTrailer);
	EXPECT_TRUE(fileTrailer.size() == 22);
	EXPECT_FALSE(fileTrailer.hasPrev());
	EXPECT_TRUE(fileTrailer.root().objectNumber() == 2);
	EXPECT_TRUE(fileTrailer.root().generationNumber() == 0);
	EXPECT_TRUE(fileTrailer.hasInfo());
	EXPECT_TRUE(fileTrailer.info().objectNumber() == 1);
	EXPECT_TRUE(fileTrailer.info().generationNumber() == 0);
	EXPECT_TRUE(fileTrailer.hasID());
	EXPECT_TRUE(fileTrailer.id().size() == 2);
	EXPECT_TRUE(fileTrailer.id()[0] == "81b14aafa313db63dbd6f981e49f94f4");
	EXPECT_TRUE(fileTrailer.id()[1] == "81b14aafa313db63dbd6f981e49f94f4");
}

TEST(FileTrailerTestSuite, wrongStartxref)
{
	pdf1_7::FileTrailer fileTrailer1;
	std::istringstream istream1("trailer << /Size 123 /Root 234 1 R >>");
	EXPECT_FALSE(istream1 >> fileTrailer1);
	
	pdf1_7::FileTrailer fileTrailer2;
	std::istringstream istream2("trailer << /Size 123 /Root 234 1 R >> startxreff");
	EXPECT_FALSE(istream2 >> fileTrailer2);
}

TEST(FileTrailerTestSuite, wrongXrefOffset)
{
	pdf1_7::FileTrailer fileTrailer1;
	std::istringstream istream1("trailer << /Size 123 /Root 234 1 R >> startxref");
	EXPECT_FALSE(istream1 >> fileTrailer1);
	
	pdf1_7::FileTrailer fileTrailer2;
	std::istringstream istream2("trailer << /Size 123 /Root 234 1 R >> startxref whatever");
	EXPECT_FALSE(istream2 >> fileTrailer2);
}

TEST(FileTrailerTestSuite, wrongEOF)
{
	pdf1_7::FileTrailer fileTrailer1;
	std::istringstream istream1("trailer << /Size 123 /Root 234 1 R >> startxref 543");
	EXPECT_FALSE(istream1 >> fileTrailer1);
	
	pdf1_7::FileTrailer fileTrailer2;
	std::istringstream istream2("trailer << /Size 123 /Root 234 1 R >> startxref 543 EOF");
	EXPECT_FALSE(istream2 >> fileTrailer2);
}

TEST(FileTrailerTestSuite, noSize)
{
	pdf1_7::FileTrailer fileTrailer;
	std::istringstream istream("trailer << /Root 234 1 R >> startxref 456 %%EOF");
	EXPECT_FALSE(istream >> fileTrailer);
}

TEST(FileTrailerTestSuite, noRoot)
{
	pdf1_7::FileTrailer fileTrailer;
	std::istringstream istream("trailer << /Size 123  >> startxref 456 %%EOF");
	EXPECT_FALSE(istream >> fileTrailer);
}