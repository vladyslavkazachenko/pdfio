#include "pdfio/pdf1_0/file_xref.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(FileXrefTestSuite, defaultCtor)
{
	pdf1_0::FileXref fileXref;
	EXPECT_TRUE(fileXref.section().subsections().empty());
}

TEST(FileXrefTestSuite, addSubsection)
{
	pdf1_0::FileXref fileXref;
	pdf1_0::FileXref::Subsection subsection1;
	fileXref.section().subsections().push_back(subsection1);
	EXPECT_TRUE(fileXref.section().subsections().size() == 1);
	EXPECT_TRUE(fileXref.section().subsections()[0].objectNumber() == 0);
	EXPECT_TRUE(fileXref.section().subsections()[0].entries().empty());
	
	pdf1_0::FileXref::Subsection subsection2;
	subsection2.objectNumber() = 123ll;
	fileXref.section().subsections().push_back(subsection2);
	EXPECT_TRUE(fileXref.section().subsections().size() == 2);
	EXPECT_TRUE(fileXref.section().subsections()[1].objectNumber() == 123ll);
	EXPECT_TRUE(fileXref.section().subsections()[1].entries().empty());
}

TEST(FileXrefTestSuite, addEntry)
{
	pdf1_0::FileXref fileXref;
	pdf1_0::FileXref::Subsection subsection;
	subsection.entries().push_back(pdf1_0::FileXref::Entry());
	EXPECT_TRUE(subsection.entries().size() == 1);
	EXPECT_TRUE(subsection.entries()[0].byteOffset() == 0);
	EXPECT_TRUE(subsection.entries()[0].generationNumber() == 0);
	EXPECT_TRUE(subsection.entries()[0].isInUse());
}