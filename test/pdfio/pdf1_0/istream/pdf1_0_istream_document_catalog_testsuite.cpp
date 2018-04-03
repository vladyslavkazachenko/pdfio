#include <sstream>

#include "pdfio/pdf1_0/document_catalog.h"
#include "pdfio/pdf1_0/istream/read_indirect_object.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(DocumentCatalogTestSuite, emptyStream)
{
	pdf1_0::IndirectObject catalog{pdf1_0::DocumentCatalog()};
	std::istringstream istream;
	EXPECT_FALSE(istream >> catalog);
}

TEST(DocumentCatalogTestSuite, simpleCatalog)
{
	pdf1_0::IndirectObject catalog{pdf1_0::DocumentCatalog()};
	std::istringstream istream("1 0 obj << /Type /Catalog /Pages 2 0 R >> endobj");
	EXPECT_TRUE(istream >> catalog);
	EXPECT_TRUE(catalog.objectNumber() == 1);
	EXPECT_TRUE(catalog.generationNumber() == 0);
	EXPECT_TRUE(catalog.get<pdf1_0::DocumentCatalog>().pages().objectNumber() == 2);
	EXPECT_TRUE(catalog.get<pdf1_0::DocumentCatalog>().pages().generationNumber() == 0);
	EXPECT_FALSE(catalog.get<pdf1_0::DocumentCatalog>().hasOutlines());
	EXPECT_FALSE(catalog.get<pdf1_0::DocumentCatalog>().hasPageMode());
}

TEST(DocumentCatalogTestSuite, fullCatalog)
{
	pdf1_0::IndirectObject catalog{pdf1_0::DocumentCatalog()};
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
	EXPECT_TRUE(catalog.objectNumber() == 1);
	EXPECT_TRUE(catalog.generationNumber() == 0);
	EXPECT_TRUE(catalog.get<pdf1_0::DocumentCatalog>().pages().objectNumber() == 2);
	EXPECT_TRUE(catalog.get<pdf1_0::DocumentCatalog>().pages().generationNumber() == 0);
	EXPECT_TRUE(catalog.get<pdf1_0::DocumentCatalog>().hasOutlines());
	EXPECT_TRUE(catalog.get<pdf1_0::DocumentCatalog>().outlines().objectNumber() == 3);
	EXPECT_TRUE(catalog.get<pdf1_0::DocumentCatalog>().outlines().generationNumber() == 0);
	EXPECT_TRUE(catalog.get<pdf1_0::DocumentCatalog>().hasPageMode());
	EXPECT_TRUE(catalog.get<pdf1_0::DocumentCatalog>().pageMode() == "UseOutlines");
}

TEST(DocumentCatalogTestSuite, wrongType)
{
	pdf1_0::IndirectObject catalog1{pdf1_0::DocumentCatalog()};
	std::istringstream istream1("1 0 obj << /type /Catalog /Pages 2 0 R >> endobj");
	EXPECT_FALSE(istream1 >> catalog1);
	
	pdf1_0::IndirectObject catalog2{pdf1_0::DocumentCatalog()};
	std::istringstream istream2("1 0 obj << /Type /catalog /Pages 2 0 R >> endobj");
	EXPECT_FALSE(istream2 >> catalog2);
}

TEST(DocumentCatalogTestSuite, noPages)
{
	pdf1_0::IndirectObject catalog{pdf1_0::DocumentCatalog()};
	std::istringstream istream1("1 0 obj << /Type /Catalog >> endobj");
	EXPECT_FALSE(istream1 >> catalog);
}