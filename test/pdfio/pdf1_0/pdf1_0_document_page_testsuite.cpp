#include "pdfio/pdf1_0/document_page.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(DocumentPageTestSuite, defaultCtor)
{
	pdf1_0::DocumentPage page;
	EXPECT_TRUE(page.mediaBox().size() == 4);
	EXPECT_TRUE(page.mediaBox()[0] == 0ll);
	EXPECT_TRUE(page.mediaBox()[1] == 0ll);
	EXPECT_TRUE(page.mediaBox()[2] == 0ll);
	EXPECT_TRUE(page.mediaBox()[3] == 0ll);
	EXPECT_TRUE(page.parent().objectNumber() == 0ll);
	EXPECT_TRUE(page.parent().generationNumber() == 0ll);
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
	page.mediaBox()[0] = 1ll;
	page.mediaBox()[1] = 1ll;
	page.mediaBox()[2] = 100ll;
	page.mediaBox()[3] = 100ll;
	page.parent().objectNumber() = 40ll;
	page.parent().generationNumber() = 1ll;
	page.resources().insert(pdf1_0::Name("whatever"), pdf1_0::Name("whatever"));
	page.contents().objectNumber() = 41ll;
	page.contents().generationNumber() = 1ll;
	EXPECT_TRUE(page.mediaBox()[0] == 1ll);
	EXPECT_TRUE(page.mediaBox()[1] == 1ll);
	EXPECT_TRUE(page.mediaBox()[2] == 100ll);
	EXPECT_TRUE(page.mediaBox()[3] == 100ll);
	EXPECT_TRUE(page.parent().objectNumber() == 40ll);
	EXPECT_TRUE(page.parent().generationNumber() == 1ll);
	EXPECT_TRUE(page.resources().keys().size() == 1);
	EXPECT_TRUE(page.resources().get<pdf1_0::Name>(pdf1_0::Name("whatever")) == "whatever");
	EXPECT_TRUE(page.hasContents());
	EXPECT_TRUE(page.contents().objectNumber() == 41ll);
	EXPECT_TRUE(page.contents().generationNumber() == 1ll);
}