#include <sstream>

#include "pdfio/pdf1_4/istream/read_document_catalog.h"
#include "gtest/gtest.h"

namespace pdf1_4 = pdfio::pdf1_4;

TEST(DocumentCatalogTestSuite, ok1)
{
   pdf1_4::DocumentCatalog docCatalog;
   std::istringstream istream(
      "<<"
      "/Type /Catalog"
      "/Pages 617 0 R"
      "/Outlines 631 0 R"
      "/PageMode /UseOutlines"
      "/OpenAction 629 0 R"
      ">>");
   EXPECT_TRUE(istream >> docCatalog);
   EXPECT_EQ(617, docCatalog.pages().objectNumber());
   EXPECT_EQ(0, docCatalog.pages().generationNumber());
   EXPECT_TRUE(docCatalog.hasOutlines());
   EXPECT_EQ(631, docCatalog.outlines().objectNumber());
   EXPECT_EQ(0, docCatalog.outlines().generationNumber());
   EXPECT_TRUE(docCatalog.hasPageMode());
   EXPECT_TRUE(docCatalog.pageMode() == "UseOutlines");
   EXPECT_TRUE(docCatalog.hasOpenAction());
   EXPECT_EQ(629, docCatalog.openAction().objectNumber());
   EXPECT_EQ(0, docCatalog.openAction().generationNumber());
}
