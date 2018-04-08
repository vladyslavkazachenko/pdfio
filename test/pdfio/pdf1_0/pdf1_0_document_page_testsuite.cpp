#include "pdfio/pdf1_0/document_page.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(DocumentPageTestSuite, defaultCtor)
{
	pdf1_0::DocumentPage page;
	EXPECT_TRUE(page.mediaBox().size() == 4);
	EXPECT_TRUE(page.mediaBox()[0] == 0);
	EXPECT_TRUE(page.mediaBox()[1] == 0);
	EXPECT_TRUE(page.mediaBox()[2] == 0);
	EXPECT_TRUE(page.mediaBox()[3] == 0);
	EXPECT_TRUE(page.parent().objectNumber() == 0);
	EXPECT_TRUE(page.parent().generationNumber() == 0);
	EXPECT_TRUE(page.resources().keys().empty());
	EXPECT_FALSE(page.hasContents());
	EXPECT_FALSE(page.hasCropBox());
	EXPECT_FALSE(page.hasRotate());
	EXPECT_FALSE(page.hasThumb());
	EXPECT_FALSE(page.hasAnnots());
}

TEST(DocumentPageTestSuite, assignment)
{
	pdf1_0::DocumentPage page;
	page.mediaBox()[0] = 1;
	page.mediaBox()[1] = 1;
	page.mediaBox()[2] = 100;
	page.mediaBox()[3] = 100;
	page.parent().objectNumber() = 40;
	page.parent().generationNumber() = 1;
	page.resources().insert(pdf1_0::Name("whatever"), pdf1_0::Name("whatever"));
	page.contents().resize(1);
	page.contents()[0].objectNumber() = 41;
	page.contents()[0].generationNumber() = 1;
	EXPECT_TRUE(page.mediaBox()[0] == 1);
	EXPECT_TRUE(page.mediaBox()[1] == 1);
	EXPECT_TRUE(page.mediaBox()[2] == 100);
	EXPECT_TRUE(page.mediaBox()[3] == 100);
	EXPECT_TRUE(page.parent().objectNumber() == 40);
	EXPECT_TRUE(page.parent().generationNumber() == 1);
	EXPECT_TRUE(page.resources().keys().size() == 1);
	EXPECT_TRUE(page.resources().get<pdf1_0::Name>(pdf1_0::Name("whatever")) == "whatever");
	EXPECT_TRUE(page.hasContents());
	EXPECT_TRUE(page.contents()[0].objectNumber() == 41);
	EXPECT_TRUE(page.contents()[0].generationNumber() == 1);
}