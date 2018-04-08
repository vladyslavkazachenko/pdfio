#include <sstream>

#include "pdfio/pdf1_0/istream/read_document_page.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(DocumentPageTestSuite, emptyStream)
{
  pdf1_0::DocumentPage page;
  std::istringstream istream;
  EXPECT_FALSE(istream >> page);
}

TEST(DocumentPageTestSuite, fullPage)
{
  pdf1_0::DocumentPage page;
  std::istringstream istream(
"<<\n\
/Type /Page\n\
/Parent 4 0 R\n\
/MediaBox [ 0 0 612 792 ]\n\
/Resources << /Font << /F3 7 0 R /F5 9 0 R /F7 11 0 R >> /ProcSet [/PDF /ImageB] >>\n\
/Thumb 12 0 R\n\
/Contents 14 0 R\n\
/Annots [ 23 0 R 24 0 R ]\n\
>>"
  );
  EXPECT_TRUE(istream >> page);
  EXPECT_TRUE(page.parent().objectNumber() == 4);
  EXPECT_TRUE(page.parent().generationNumber() == 0);
  EXPECT_TRUE(page.mediaBox()[0] == 0);
  EXPECT_TRUE(page.mediaBox()[1] == 0);
  EXPECT_TRUE(page.mediaBox()[2] == 612);
  EXPECT_TRUE(page.mediaBox()[3] == 792);
  EXPECT_TRUE(page.resources().get<pdf1_0::DocumentPage::ResourceDictionary>(pdf1_0::Name("Font"))[pdf1_0::Name("F3")].objectNumber() == 7);
  EXPECT_TRUE(page.resources().get<pdf1_0::DocumentPage::ResourceDictionary>(pdf1_0::Name("Font"))[pdf1_0::Name("F3")].generationNumber() == 0);
  EXPECT_TRUE(page.resources().get<pdf1_0::DocumentPage::ResourceDictionary>(pdf1_0::Name("Font"))[pdf1_0::Name("F5")].objectNumber() == 9);
  EXPECT_TRUE(page.resources().get<pdf1_0::DocumentPage::ResourceDictionary>(pdf1_0::Name("Font"))[pdf1_0::Name("F5")].generationNumber() == 0);
  EXPECT_TRUE(page.resources().get<pdf1_0::DocumentPage::ResourceDictionary>(pdf1_0::Name("Font"))[pdf1_0::Name("F7")].objectNumber() == 11);
  EXPECT_TRUE(page.resources().get<pdf1_0::DocumentPage::ResourceDictionary>(pdf1_0::Name("Font"))[pdf1_0::Name("F7")].generationNumber() == 0);
  EXPECT_TRUE(page.resources().contains(pdf1_0::Name("ProcSet")));
  EXPECT_EQ(2, page.resources().get<pdf1_0::Array<pdf1_0::Name>>(pdf1_0::Name("ProcSet")).size());
  EXPECT_TRUE(page.resources().get<pdf1_0::Array<pdf1_0::Name>>(pdf1_0::Name("ProcSet"))[0] == pdf1_0::Name("PDF"));
  EXPECT_TRUE(page.resources().get<pdf1_0::Array<pdf1_0::Name>>(pdf1_0::Name("ProcSet"))[1] == pdf1_0::Name("ImageB"));
  EXPECT_TRUE(page.thumb().objectNumber() == 12);
  EXPECT_TRUE(page.thumb().generationNumber() == 0);
  EXPECT_EQ(1, page.contents().size());
  EXPECT_EQ(14, page.contents()[0].objectNumber());
  EXPECT_EQ(0, page.contents()[0].generationNumber());
  EXPECT_TRUE(page.annots()[0].objectNumber() == 23);
  EXPECT_TRUE(page.annots()[0].generationNumber() == 0);
  EXPECT_TRUE(page.annots()[1].objectNumber() == 24);
  EXPECT_TRUE(page.annots()[1].generationNumber() == 0);
}

TEST(DocumentPageTestSuite, pageWithXObject)
{
	pdf1_0::DocumentPage page;
	std::istringstream istream(
		"<<"
		"/MediaBox [0.00000 0.00000 595.00000 842.00000]"
		"/Type /Page"
		"/Contents [6 0 R]"
		"/Parent 4 0 R"
		"/Resources <<"
		"/XObject <<"
		"/WnvPdf_nnmcpgcecigakfbbbgncpigbonhoeaie 7 0 R"
		">>"
		"/ProcSet [/PDF /Text /ImageC]"
		">>"
		">>");
  EXPECT_TRUE(istream >> page);
}