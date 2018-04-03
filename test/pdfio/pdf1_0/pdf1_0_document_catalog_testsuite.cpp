#include "pdfio/pdf1_0/document_catalog.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(DocumentCatalogTestSuite, defaultCtor)
{
	pdf1_0::DocumentCatalog catalog;
	EXPECT_TRUE(catalog.pages().objectNumber() == 0);
	EXPECT_TRUE(catalog.pages().generationNumber() == 0);
	EXPECT_FALSE(catalog.hasOutlines());
	EXPECT_FALSE(catalog.hasPageMode());
}

TEST(DocumentCatalogTestSuite, assignment)
{
	pdf1_0::DocumentCatalog catalog;
	catalog.pages().objectNumber() = 23;
	catalog.pages().generationNumber() = 1;
	catalog.outlines().objectNumber() = 24;
	catalog.outlines().generationNumber() = 2;
	catalog.pageMode() = "UseThumbs";
	EXPECT_TRUE(catalog.pages().objectNumber() == 23);
	EXPECT_TRUE(catalog.pages().generationNumber() == 1);
	EXPECT_TRUE(catalog.hasOutlines());
	EXPECT_TRUE(catalog.outlines().objectNumber() == 24);
	EXPECT_TRUE(catalog.outlines().generationNumber() == 2);
	EXPECT_TRUE(catalog.hasPageMode());
	EXPECT_TRUE(catalog.pageMode() == "UseThumbs");
}
