#include <sstream>

#include "pdfio/pdf1_0/istream/read_file_xref.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(FileXrefTestSuite, emptyStream)
{
	pdf1_0::FileXref fileXref;
	std::istringstream istream;
	EXPECT_FALSE(istream >> fileXref);
}

TEST(FileXrefTestSuite, wrongXref)
{
	pdf1_0::FileXref fileXref;
	std::istringstream istream("xre");
	EXPECT_FALSE(istream >> fileXref);
}

TEST(FileXrefTestSuite, sectionWith1Subsection)
{
	pdf1_0::FileXref fileXref;
	std::istringstream istream("xref\n10 2\n0000000003 00003 f \n0000000017 00000 n \n");
	EXPECT_TRUE(istream >> fileXref);
	EXPECT_TRUE(fileXref.section().subsections().size() == 1);
	EXPECT_TRUE(fileXref.section().subsections()[0].objectNumber() == 10ll);
	EXPECT_TRUE(fileXref.section().subsections()[0].entries().size() == 2);
	EXPECT_TRUE(fileXref.section().subsections()[0].entries()[0].byteOffset() == 3ll);
	EXPECT_TRUE(fileXref.section().subsections()[0].entries()[0].generationNumber() == 3ll);
	EXPECT_FALSE(fileXref.section().subsections()[0].entries()[0].isInUse());
	EXPECT_TRUE(fileXref.section().subsections()[0].entries()[1].byteOffset() == 17ll);
	EXPECT_TRUE(fileXref.section().subsections()[0].entries()[1].generationNumber() == 0ll);
	EXPECT_TRUE(fileXref.section().subsections()[0].entries()[1].isInUse());
}

TEST(FileXrefTestSuite, sectionWith2Subsections)
{
	pdf1_0::FileXref fileXref;
	std::istringstream istream("xref\n10 2\n0000000003 00003 f \n0000000017 00000 n \n\
		12 1\n0000003456 00000 n \n");
	EXPECT_TRUE(istream >> fileXref);
	EXPECT_TRUE(fileXref.section().subsections().size() == 2);
	EXPECT_TRUE(fileXref.section().subsections()[0].objectNumber() == 10ll);
	EXPECT_TRUE(fileXref.section().subsections()[0].entries().size() == 2);
	EXPECT_TRUE(fileXref.section().subsections()[0].entries()[0].byteOffset() == 3ll);
	EXPECT_TRUE(fileXref.section().subsections()[0].entries()[0].generationNumber() == 3ll);
	EXPECT_FALSE(fileXref.section().subsections()[0].entries()[0].isInUse());
	EXPECT_TRUE(fileXref.section().subsections()[0].entries()[1].byteOffset() == 17ll);
	EXPECT_TRUE(fileXref.section().subsections()[0].entries()[1].generationNumber() == 0ll);
	EXPECT_TRUE(fileXref.section().subsections()[0].entries()[1].isInUse());
	EXPECT_TRUE(fileXref.section().subsections()[1].objectNumber() == 12ll);
	EXPECT_EQ(1, fileXref.section().subsections()[1].entries().size());
	EXPECT_TRUE(fileXref.section().subsections()[1].entries()[0].byteOffset() == 3456ll);
	EXPECT_TRUE(fileXref.section().subsections()[1].entries()[0].generationNumber() == 0ll);
	EXPECT_TRUE(fileXref.section().subsections()[1].entries()[0].isInUse());
}

TEST(FileXrefTestSuite, emptySection)
{
	pdf1_0::FileXref fileXref;
	std::istringstream istream("xref");
	EXPECT_FALSE(istream >> fileXref);
}

TEST(FileXrefTestSuite, wrongSubsection)
{
	pdf1_0::FileXref fileXref1;
	std::istringstream istream1("xref\r\nwhatever");
	EXPECT_TRUE(istream1 >> fileXref1);
	EXPECT_TRUE(fileXref1.section().subsections().empty());
	
	pdf1_0::FileXref fileXref2;
	std::istringstream istream2("xref\r\n24 whatever");
	EXPECT_TRUE(istream2 >> fileXref2);
	EXPECT_TRUE(fileXref2.section().subsections().empty());
	
	pdf1_0::FileXref fileXref3;
	std::istringstream istream3("xref\r\n24 1");
	EXPECT_TRUE(istream3 >> fileXref3);
	EXPECT_TRUE(fileXref3.section().subsections().empty());
}