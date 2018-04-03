#include <sstream>

#include "pdfio/pdf1_0/istream/read_file.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(FileTestSuite, emptyStream)
{
	pdf1_0::File file;
	std::istringstream istream;
	EXPECT_FALSE(istream >> file);
}

TEST(FileTestSuite, simpleFile)
{
	pdf1_0::File file;
	std::istringstream istream(
"%PDF-1.0\r\n\
1 0 obj\r\n\
<<\r\n\
159/Type /Catalog\r\n\
/Pages 3 0 R\r\n\
/Outlines 2 0 R\r\n\
>>\r\n\
endobj\r\n\
2 0 obj\r\n\
<<\r\n\
/Type /Outlines\r\n\
/Count 0\r\n\
>>\r\n\
endobj\r\n\
3 0 obj\r\n\
<<\r\n\
/Type /Pages\r\n\
/Count 1\r\n\
/Kids [ 4 0 R ]\r\n\
>>\r\n\
endobj\r\n\
4 0 obj\r\n\
<<\r\n\
/Type /Page\r\n\
/Parent 3 0 R\r\n\
/Resources << /ProcSet 6 0 R >>\r\n\
/MediaBox [ 0 0 612 792 ]\r\n\
/Contents 5 0 R\r\n\
>>\r\n\
endobj\r\n\
5 0 obj\r\n\
<< /Length 35 >>\r\n\
stream\r\n\
%place page marking operators here\r\n\
endstream\r\n\
endobj\r\n\
6 0 obj\r\n\
[ /PDF ]\r\n\
endobj\r\n\
xref\r\n\
0 7\r\n\
0000000000 65535 f\r\n\
0000000009 00000 n\r\n\
0000000074 00000 n\r\n\
0000000120 00000 n\r\n\
0000000179 00000 n\r\n\
0000000300 00000 n\r\n\
0000000384 00000 n\r\n\
trailer\r\n\
<<\r\n\
/Size 7\r\n\
/Root 1 0 R\r\n\
>>\r\n\
startxref\r\n\
450\r\n\
%%EOF\r\n");
	istream.seekg(0, std::ios_base::end);
	auto endPosition = istream.tellg();
	istream.seekg(0, std::ios_base::beg);
	EXPECT_TRUE(istream >> file);
	EXPECT_EQ(endPosition, file.latestVersion().endOffset());
	EXPECT_TRUE(file.latestVersion().xref().section().subsections().size() == 1);
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].objectNumber() == 0);
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries().size() == 7);
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[0].byteOffset() == 0);
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[0].generationNumber() == 65535);
	EXPECT_FALSE(file.latestVersion().xref().section().subsections()[0].entries()[0].isInUse());
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[1].byteOffset() == 9);
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[1].generationNumber() == 0);
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[1].isInUse());
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[2].byteOffset() == 74);
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[2].generationNumber() == 0);
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[2].isInUse());
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[3].byteOffset() == 120);
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[3].generationNumber() == 0);
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[3].isInUse());
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[4].byteOffset() == 179);
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[4].generationNumber() == 0);
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[4].isInUse());
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[5].byteOffset() == 300);
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[5].generationNumber() == 0);
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[5].isInUse());
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[6].byteOffset() == 384);
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[6].generationNumber() == 0);
	EXPECT_TRUE(file.latestVersion().xref().section().subsections()[0].entries()[6].isInUse());
	EXPECT_TRUE(file.latestVersion().trailer().size() == 7);
	EXPECT_FALSE(file.latestVersion().trailer().hasPrev());
	EXPECT_TRUE(file.latestVersion().trailer().root().objectNumber() == 1);
	EXPECT_TRUE(file.latestVersion().trailer().root().generationNumber() == 0);
	EXPECT_FALSE(file.latestVersion().trailer().hasInfo());
}