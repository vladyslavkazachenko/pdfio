#include <sstream>

#include "pdfio/pdf1_0/istream/read_file_header.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(FileHeaderTestSuite, emptyStream)
{
	pdf1_0::FileHeader fileHeader;
	std::istringstream istream;
	EXPECT_FALSE(istream >> fileHeader);
}

TEST(FileHeaderTestSuite, wrongHeader)
{
	pdf1_0::FileHeader fileHeader;
	std::istringstream istream("PDF-1.0");
	EXPECT_FALSE(istream >> fileHeader);
}

TEST(FileHeaderTestSuite, ok)
{
	pdf1_0::FileHeader fileHeader;
	std::istringstream istream("%PDF-1.0");
	EXPECT_TRUE(istream >> fileHeader);
}