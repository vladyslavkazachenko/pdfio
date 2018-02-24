#include <sstream>

#include "pdfio/pdf1_0/istream/read_document_catalog.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(DocumentCatalogTestSuite, emptyStream)
{
	pdf1_0::DocumentCatalog catalog;
	std::istringstream istream;
	EXPECT_FALSE(istream >> catalog);
}

TEST(DocumentCatalogTestSuite, simpleCatalog)
{
	pdf1_0::DocumentCatalog catalog;
	std::istringstream istream("1 0 obj << /Type /Catalog /Pages 2 0 R >> endobj");
	EXPECT_TRUE(istream >> catalog);
	EXPECT_TRUE(catalog.object().objectNumber() == 1ll);
	EXPECT_TRUE(catalog.object().generationNumber() == 0ll);
	EXPECT_TRUE(catalog.pages().objectNumber() == 2ll);
	EXPECT_TRUE(catalog.pages().generationNumber() == 0ll);
	EXPECT_FALSE(catalog.hasOutlines());
	EXPECT_FALSE(catalog.hasPageMode());
}

TEST(DocumentCatalogTestSuite, fullCatalog)
{
	pdf1_0::DocumentCatalog catalog;
	std::istringstream istream(
"1 0 obj\r\n\
<<\r\n\
/Type /Catalog\r\n\
/Pages 2 0 R\r\n\
/Outlines 3 0 R\r\n\
/PageMode /UseOutlines\r\n\
>>\r\n\
endobj");
	EXPECT_TRUE(istream >> catalog);
	EXPECT_TRUE(catalog.object().objectNumber() == 1ll);
	EXPECT_TRUE(catalog.object().generationNumber() == 0ll);
	EXPECT_TRUE(catalog.pages().objectNumber() == 2ll);
	EXPECT_TRUE(catalog.pages().generationNumber() == 0ll);
	EXPECT_TRUE(catalog.hasOutlines());
	EXPECT_TRUE(catalog.outlines().objectNumber() == 3ll);
	EXPECT_TRUE(catalog.outlines().generationNumber() == 0ll);
	EXPECT_TRUE(catalog.hasPageMode());
	EXPECT_TRUE(catalog.pageMode() == "UseOutlines");
}

TEST(DocumentCatalogTestSuite, wrongType)
{
	pdf1_0::DocumentCatalog catalog1;
	std::istringstream istream1("1 0 obj << /type /Catalog /Pages 2 0 R >> endobj");
	EXPECT_FALSE(istream1 >> catalog1);
	
	pdf1_0::DocumentCatalog catalog2;
	std::istringstream istream2("1 0 obj << /Type /catalog /Pages 2 0 R >> endobj");
	EXPECT_FALSE(istream2 >> catalog2);
}

TEST(DocumentCatalogTestSuite, noPages)
{
	pdf1_0::DocumentCatalog catalog1;
	std::istringstream istream1("1 0 obj << /Type /Catalog >> endobj");
	EXPECT_FALSE(istream1 >> catalog1);
}