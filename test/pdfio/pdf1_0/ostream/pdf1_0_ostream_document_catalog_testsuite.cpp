#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_0/ostream/write_document_catalog.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(DocumentCatalogTestSuite, test1)
{
   pdf1_0::DocumentCatalog catalog;
   std::ostringstream ostream;
   EXPECT_TRUE(ostream << catalog);
   EXPECT_TRUE(ostream.str() == "<</Pages 0 0 R/Type /Catalog>>");
}

TEST(DocumentCatalogTestSuite, test2)
{
   pdf1_0::DocumentCatalog catalog;
   catalog.pages().objectNumber() = 11;
   catalog.pages().generationNumber() = 1;
   std::ostringstream ostream;
   EXPECT_TRUE(ostream << catalog);
   EXPECT_TRUE(ostream.str() == "<</Pages 11 1 R/Type /Catalog>>");
}

