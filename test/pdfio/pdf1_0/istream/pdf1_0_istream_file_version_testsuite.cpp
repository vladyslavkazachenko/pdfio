#include <sstream>

#include "pdfio/pdf1_0/istream/read_file_version.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(FileVersionTestSuite, emptyStream)
{
	pdf1_0::FileVersion fileVersion;
	std::istringstream istream;
	EXPECT_FALSE(istream >> fileVersion);
}

TEST(FileVersionTestSuite, wrongXref)
{
	pdf1_0::FileVersion fileVersion1;
	std::istringstream istream1("xreff");
	EXPECT_FALSE(istream1 >> fileVersion1);
}

TEST(FileVersionTestSuite, wrongTrailer)
{
	pdf1_0::FileVersion fileVersion1;
	std::istringstream istream1("xref\r\ntrailerr");
	EXPECT_FALSE(istream1 >> fileVersion1);
	
	pdf1_0::FileVersion fileVersion2;
	std::istringstream istream2("xref\r\ntrailer << >>");
	EXPECT_FALSE(istream2 >> fileVersion2);
}

TEST(FileVersionTestSuite, ok)
{
	pdf1_0::FileVersion fileVersion;
	std::istringstream istream(
"xref\n\
0 7\n\
0000000000 65535 f\n\
0000000009 00000 n\n\
0000000074 00000 n\n\
0000000120 00000 n\n\
0000000179 00000 n\n\
0000000300 00000 n\n\
0000000384 00000 n\n\
trailer\n\
<<\n\
/Size 7\n\
/Root 1 0 R\n\
>>\n\
startxref\n\
408\n\
%%EOF\n");
	istream.seekg(0, std::ios_base::end);
	auto endPosition3 = istream.tellg();
	istream.seekg(0, std::ios_base::beg);
	auto beginPosition3 = istream.tellg();
	EXPECT_TRUE(istream >> fileVersion);
	EXPECT_EQ(beginPosition3, fileVersion.beginOffset());
	EXPECT_EQ(endPosition3, fileVersion.endOffset());
	EXPECT_TRUE(fileVersion.xref().section().subsections().size() == 1);
	EXPECT_TRUE(fileVersion.trailer().size() == 7ll);
	EXPECT_FALSE(fileVersion.trailer().hasPrev());
	EXPECT_TRUE(fileVersion.trailer().root().objectNumber() == 1ll);
	EXPECT_TRUE(fileVersion.trailer().root().generationNumber() == 0ll);
	EXPECT_FALSE(fileVersion.trailer().hasInfo());
}