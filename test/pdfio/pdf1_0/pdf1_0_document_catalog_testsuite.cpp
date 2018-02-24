#include "pdfio/pdf1_0/document_catalog.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(DocumentCatalogTestSuite, defaultCtor)
{
	pdf1_0::DocumentCatalog catalog;
	EXPECT_TRUE(catalog.pages().objectNumber() == 0ll);
	EXPECT_TRUE(catalog.pages().generationNumber() == 0ll);
	EXPECT_FALSE(catalog.hasOutlines());
	EXPECT_FALSE(catalog.hasPageMode());
}

TEST(DocumentCatalogTestSuite, assignment)
{
	pdf1_0::DocumentCatalog catalog;
	catalog.pages().objectNumber() = 23ll;
	catalog.pages().generationNumber() = 1ll;
	catalog.outlines().objectNumber() = 24ll;
	catalog.outlines().generationNumber() = 2ll;
	catalog.pageMode() = "UseThumbs";
	EXPECT_TRUE(catalog.pages().objectNumber() == 23ll);
	EXPECT_TRUE(catalog.pages().generationNumber() == 1ll);
	EXPECT_TRUE(catalog.hasOutlines());
	EXPECT_TRUE(catalog.outlines().objectNumber() == 24ll);
	EXPECT_TRUE(catalog.outlines().generationNumber() == 2ll);
	EXPECT_TRUE(catalog.hasPageMode());
	EXPECT_TRUE(catalog.pageMode() == "UseThumbs");
}
