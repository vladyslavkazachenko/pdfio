#include <sstream>

#include "pdfio/pdf1_7/istream/read_document_catalog.h"
#include "gtest/gtest.h"

namespace pdf1_7 = pdfio::pdf1_7;

TEST(DocumentCatalogTestSuite, emptyStream)
{
   pdf1_7::DocumentCatalog docCatalog;
   std::istringstream istream;
   EXPECT_FALSE(istream >> docCatalog);
}

TEST(DocumentCatalogTestSuite, ok1)
{
   pdf1_7::DocumentCatalog docCatalog;
   std::istringstream istream(
      "<<"
      "/Pages 18 0 R"
      "/PieceInfo <<"
      "/CVPI <<"
      "/LastModified (D:20131214172321+02'00')"
      "/Private <<"
      "/Mode /Stream"
      "/Build (3.1.34)"
      ">>"
      ">>"
      ">>"
      "/Type /Catalog"
      ">>");
   EXPECT_TRUE(istream >> docCatalog);
}

TEST(DocumentCatalogTestSuite, ok2)
{
   pdf1_7::DocumentCatalog docCatalog;
   std::istringstream istream(
      "<<"
      "/OutputIntents [<<"
      "/DestOutputProfile 2 0 R"
      "/S /GTS_PDFA1"
      "/Info (sRGB IEC61966-2.1)"
      "/RegistryName ()"
      "/OutputCondition ()"
      "/Type /OutputIntent"
      "/OutputConditionIdentifier (Custom)"
      ">>"
      "]"
      "/ViewerPreferences 3 0 R"
      "/Type /Catalog"
      "/PageLayout /OneColumn"
      "/Pages 4 0 R"
      "/PageMode /UseNone"
      ">>");
   EXPECT_TRUE(istream >> docCatalog);
}