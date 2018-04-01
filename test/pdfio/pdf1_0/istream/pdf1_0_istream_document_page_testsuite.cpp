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
/Resources << /Font << /F3 7 0 R /F5 9 0 R /F7 11 0 R >> /ProcSet 15 1 R >>\n\
/Thumb 12 0 R\n\
/Contents 14 0 R\n\
/Annots [ 23 0 R 24 0 R ]\n\
>>"
  );
  EXPECT_TRUE(istream >> page);
  EXPECT_TRUE(page.parent().objectNumber() == 4ll);
  EXPECT_TRUE(page.parent().generationNumber() == 0ll);
  EXPECT_TRUE(page.mediaBox()[0] == 0ll);
  EXPECT_TRUE(page.mediaBox()[1] == 0ll);
  EXPECT_TRUE(page.mediaBox()[2] == 612ll);
  EXPECT_TRUE(page.mediaBox()[3] == 792ll);
  EXPECT_TRUE(page.resources().get<pdf1_0::DocumentPage::ResourceDictionary>(pdf1_0::Name("Font"))[pdf1_0::Name("F3")].objectNumber() == 7ll);
  EXPECT_TRUE(page.resources().get<pdf1_0::DocumentPage::ResourceDictionary>(pdf1_0::Name("Font"))[pdf1_0::Name("F3")].generationNumber() == 0ll);
  EXPECT_TRUE(page.resources().get<pdf1_0::DocumentPage::ResourceDictionary>(pdf1_0::Name("Font"))[pdf1_0::Name("F5")].objectNumber() == 9ll);
  EXPECT_TRUE(page.resources().get<pdf1_0::DocumentPage::ResourceDictionary>(pdf1_0::Name("Font"))[pdf1_0::Name("F5")].generationNumber() == 0ll);
  EXPECT_TRUE(page.resources().get<pdf1_0::DocumentPage::ResourceDictionary>(pdf1_0::Name("Font"))[pdf1_0::Name("F7")].objectNumber() == 11ll);
  EXPECT_TRUE(page.resources().get<pdf1_0::DocumentPage::ResourceDictionary>(pdf1_0::Name("Font"))[pdf1_0::Name("F7")].generationNumber() == 0ll);
  EXPECT_TRUE(page.resources().contains(pdf1_0::Name("ProcSet")));
  EXPECT_TRUE(page.resources().get<pdf1_0::DocumentPage::ProcSet>(pdf1_0::Name("ProcSet")).objectNumber() == 15);
  EXPECT_TRUE(page.resources().get<pdf1_0::DocumentPage::ProcSet>(pdf1_0::Name("ProcSet")).generationNumber() == 1);
  EXPECT_TRUE(page.thumb().objectNumber() == 12);
  EXPECT_TRUE(page.thumb().generationNumber() == 0ll);
  EXPECT_TRUE(page.contents().objectNumber() == 14ll);
  EXPECT_TRUE(page.contents().generationNumber() == 0ll);
  EXPECT_TRUE(page.annots()[0].objectNumber() == 23ll);
  EXPECT_TRUE(page.annots()[0].generationNumber() == 0ll);
  EXPECT_TRUE(page.annots()[1].objectNumber() == 24ll);
  EXPECT_TRUE(page.annots()[1].generationNumber() == 0ll);
}