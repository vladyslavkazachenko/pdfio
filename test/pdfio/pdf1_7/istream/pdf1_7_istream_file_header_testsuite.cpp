#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_7/istream/read_file_header.h"

namespace pdf1_7 = pdfio::pdf1_7;

TEST(FileHeaderTestSuite, emptyStream)
{
	pdf1_7::FileHeader fileHeader;
	std::istringstream istream;
	EXPECT_FALSE(istream >> fileHeader);
}


TEST(FileHeaderTestSuite, wrongHeader)
{
	pdf1_7::FileHeader fileHeader;
	std::istringstream istream("PDF-1.7");
	EXPECT_FALSE(istream >> fileHeader);
}

TEST(FileHeaderTestSuite, ok_1_7)
{
	pdf1_7::FileHeader fileHeader;
	std::istringstream istream("%PDF-1.7");
	EXPECT_TRUE(istream >> fileHeader);
}

TEST(FileHeaderTestSuite, ok_1_6)
{
	pdf1_7::FileHeader fileHeader;
	std::istringstream istream("%PDF-1.6");
	EXPECT_TRUE(istream >> fileHeader);
}

TEST(FileHeaderTestSuite, ok_1_5)
{
	pdf1_7::FileHeader fileHeader;
	std::istringstream istream("%PDF-1.5");
	EXPECT_TRUE(istream >> fileHeader);
}

TEST(FileHeaderTestSuite, ok_1_4)
{
	pdf1_7::FileHeader fileHeader;
	std::istringstream istream("%PDF-1.4");
	EXPECT_TRUE(istream >> fileHeader);
}

TEST(FileHeaderTestSuite, ok_1_3)
{
	pdf1_7::FileHeader fileHeader;
	std::istringstream istream("%PDF-1.3");
	EXPECT_TRUE(istream >> fileHeader);
}

TEST(FileHeaderTestSuite, ok_1_2)
{
	pdf1_7::FileHeader fileHeader;
	std::istringstream istream("%PDF-1.2");
	EXPECT_TRUE(istream >> fileHeader);
}

TEST(FileHeaderTestSuite, ok_1_1)
{
	pdf1_7::FileHeader fileHeader;
	std::istringstream istream("%PDF-1.1");
	EXPECT_TRUE(istream >> fileHeader);
}

TEST(FileHeaderTestSuite, ok_1_0)
{
	pdf1_7::FileHeader fileHeader;
	std::istringstream istream("%PDF-1.0");
	EXPECT_TRUE(istream >> fileHeader);
}