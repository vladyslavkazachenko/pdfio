#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_0/istream/read_document_pages_tree.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(DocumentPagesTreeTestSuite, emptyStream)
{
   pdf1_0::DocumentPagesTree pagesTree;
   std::istringstream istream;
   EXPECT_FALSE(istream >> pagesTree);
}

TEST(DocumentPagesTreeTestSuite, pages_ok1)
{
   pdf1_0::DocumentPagesTree pagesTree;
   std::istringstream istream(
      "<<"
      "/Type /Pages"
      "/Kids [ 4 0 R 10 0 R 24 0 R ]"
      "/Count 3"
      ">>");
   EXPECT_TRUE(istream >> pagesTree);
   EXPECT_TRUE(pagesTree.isTree());
   EXPECT_TRUE(pagesTree.hasKids());
   EXPECT_EQ(3, pagesTree.kids().size());
   EXPECT_TRUE(pagesTree.kids()[0].objectNumber() == 4);
   EXPECT_TRUE(pagesTree.kids()[0].generationNumber() == 0);
   EXPECT_TRUE(pagesTree.kids()[1].objectNumber() == 10);
   EXPECT_TRUE(pagesTree.kids()[1].generationNumber() == 0);
   EXPECT_TRUE(pagesTree.kids()[2].objectNumber() == 24);
   EXPECT_TRUE(pagesTree.kids()[2].generationNumber() == 0);
   EXPECT_TRUE(pagesTree.hasCount());
   EXPECT_TRUE(pagesTree.count() == 3);
   EXPECT_FALSE(pagesTree.hasParent());
}

TEST(DocumentPagesTreeTestSuite, pages_ok2)
{
   pdf1_0::DocumentPagesTree pagesTree;
   std::istringstream istream(
      "<<"
      "/Type /Pages"
      "/Kids [ 4 0 R 10 0 R 24 0 R ]"
      "/Count 3"
      "/Parent 25 0 R"
      ">>");
   EXPECT_TRUE(istream >> pagesTree);
   EXPECT_TRUE(pagesTree.hasParent());
   EXPECT_TRUE(pagesTree.parent().objectNumber() == 25);
   EXPECT_TRUE(pagesTree.parent().generationNumber() == 0);
}

TEST(DocumentPagesTreeTestSuite, pages_noType)
{
   pdf1_0::DocumentPagesTree pagesTree;
   std::istringstream istream(
      "<<"
      "/Kids [ 4 0 R 10 0 R 24 0 R ]"
      "/Count 3"
      "/Parent 25 0 R"
      ">>");
   EXPECT_FALSE(istream >> pagesTree);
}

TEST(DocumentPagesTreeTestSuite, pages_noKids)
{
   pdf1_0::DocumentPagesTree pagesTree;
   std::istringstream istream(
      "<<"
      "/Type /Pages"
      "/Count 3"
      "/Parent 25 0 R"
      ">>");
   EXPECT_FALSE(istream >> pagesTree);
}

TEST(DocumentPagesTreeTestSuite, pages_noCount)
{
   pdf1_0::DocumentPagesTree pagesTree;
   std::istringstream istream(
      "<<"
      "/Type /Pages"
      "/Kids [ 4 0 R 10 0 R 24 0 R ]"
      "/Parent 25 0 R"
      ">>");
   EXPECT_FALSE(istream >> pagesTree);
}

TEST(DocumentPagesTreeTestSuite, page_ok1)
{
  pdf1_0::DocumentPagesTree pagesTree;
  std::istringstream istream(
      "<<"
      "/Type /Page"
      "/Parent 4 0 R"
      "/MediaBox [ 0 0 612 792 ]"
      "/Resources << /Font << /F3 7 0 R /F5 9 0 R /F7 11 0 R >> /ProcSet [/PDF /ImageB] >>"
      "/Thumb 12 0 R"
      "/Contents 14 0 R"
      "/Annots [ 23 0 R 24 0 R ]"
      ">>"
  );
   EXPECT_TRUE(istream >> pagesTree);
   EXPECT_FALSE(pagesTree.isTree());
   EXPECT_TRUE(pagesTree.hasParent());
   EXPECT_TRUE(pagesTree.parent().objectNumber() == 4);
   EXPECT_TRUE(pagesTree.parent().generationNumber() == 0);
   EXPECT_TRUE(pagesTree.hasMediaBox());
   EXPECT_TRUE(pagesTree.mediaBox()[0] == 0);
   EXPECT_TRUE(pagesTree.mediaBox()[1] == 0);
   EXPECT_TRUE(pagesTree.mediaBox()[2] == 612);
   EXPECT_TRUE(pagesTree.mediaBox()[3] == 792);
   /*EXPECT_TRUE(page.resources().get<pdf1_0::DocumentPage::ResourceDictionary>(pdf1_0::Name("Font"))[pdf1_0::Name("F3")].objectNumber() == 7);
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
   EXPECT_TRUE(page.annots()[1].generationNumber() == 0);*/
}

TEST(DocumentPagesTreeTestSuite, page_ok2)
{
   pdf1_0::DocumentPagesTree pagesTree;
   std::istringstream istream(
      "<</CropBox[0 0 531 666]/Annots[7882 0 R 7880 0 R 7883 0 R 7881 0 R 7876 0 R 7877 0 R 7878 0 R 7879 0 R]/Parent 109892 0 R/StructParents 4648/Contents 2027 0 R/Rotate 0/MediaBox[0 0 531 666]/Resources<</Font<</T1_0 3914 0 R/T1_1 3912 0 R/T1_2 3957 0 R/T1_3 3944 0 R/T1_4 3931 0 R/T1_5 4161 0 R/T1_6 4533 0 R>>/ProcSet[/PDF/Text]/ExtGState<</GS0 333283 0 R>>>>/Type/Page>>"
   );
   EXPECT_TRUE(istream >> pagesTree);
   EXPECT_FALSE(pagesTree.isTree());
   EXPECT_TRUE(pagesTree.mediaBox()[0] == 0);
   EXPECT_TRUE(pagesTree.mediaBox()[1] == 0);
   EXPECT_TRUE(pagesTree.mediaBox()[2] == 531);
   EXPECT_TRUE(pagesTree.mediaBox()[3] == 666);
}