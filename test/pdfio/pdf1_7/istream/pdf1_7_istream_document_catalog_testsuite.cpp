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

TEST(DocumentCatalogTestSuite, ok)
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