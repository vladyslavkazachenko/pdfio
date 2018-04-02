#include "gtest/gtest.h"
#include "pdfio/pdf1_7/pdf.h"

TEST(PdfTestSuite, version)
{
	EXPECT_EQ("1.7", pdfio::pdf1_7::kVersion);
}