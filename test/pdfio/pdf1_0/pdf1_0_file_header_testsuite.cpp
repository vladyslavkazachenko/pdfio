#include "pdfio/pdf1_0/file_header.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(FileHeaderTestSuite, defaultCtor)
{
	pdf1_0::FileHeader fileHeader;
	EXPECT_EQ(1, fileHeader.majorVersion());
	EXPECT_EQ(0, fileHeader.minorVersion());
}

TEST(FileHeaderTestSuite, assignment)
{
	pdf1_0::FileHeader fileHeader;
	fileHeader.majorVersion() = 1;
	fileHeader.minorVersion() = 3;
	EXPECT_EQ(1, fileHeader.majorVersion());
	EXPECT_EQ(3, fileHeader.minorVersion());
}