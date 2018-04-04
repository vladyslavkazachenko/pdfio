#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_7/istream/read_file_structure.h"

namespace pdf1_7 = pdfio::pdf1_7;

TEST(FileStructureTestSuite, trailer_emptyStream)
{
  pdf1_7::FileStructure::Trailer trailer;
  std::istringstream istream;
  EXPECT_FALSE(istream >> trailer);
}

TEST(FileStructureTestSuite, trailer_ok)
{
  pdf1_7::FileStructure::Trailer trailer1;
  std::istringstream istream1(
    "trailer\n"
    "<< /Size 22\n"
    "/Root 2 0 R\n"
    "/Info 1 0 R\n"
    "/ID [ < 81b14aafa313db63dbd6f981e49f94f4 >\n"
    "< 81b14aafa313db63dbd6f981e49f94f4 >\n"
    "]\n"
    ">>\n"
    "startxref\n"
    "18799\n"
    "%%EOF"
  );
  EXPECT_TRUE(istream1 >> trailer1);
  EXPECT_EQ(22, trailer1.size());
  EXPECT_TRUE(trailer1.hasRoot());
  EXPECT_EQ(2, trailer1.root().objectNumber());
  EXPECT_EQ(0, trailer1.root().generationNumber());
  EXPECT_TRUE(trailer1.hasInfo());
  EXPECT_EQ(1, trailer1.info().objectNumber());
  EXPECT_EQ(0, trailer1.info().generationNumber());
  EXPECT_TRUE(trailer1.hasId());
  EXPECT_EQ(2, trailer1.id().size());
  EXPECT_TRUE(trailer1.id()[0] == "81b14aafa313db63dbd6f981e49f94f4");
  EXPECT_TRUE(trailer1.id()[1] == "81b14aafa313db63dbd6f981e49f94f4");
  
  pdf1_7::FileStructure::Trailer trailer2;
  std::istringstream istream2(
    "trailer\n"
    "<</Size 4963/Prev 1513589/Root 1047 0 R/Info 1045 0 R/ID[<B0DCFF11815D46D2A0723B8B6A07897C><CB01C436D5674A45A3942939551EB0ED>]>>\n"
    "startxref\n"
    "0\n"
    "%%EOF"
  );
  EXPECT_TRUE(istream2 >> trailer2);
}

TEST(FileStructureTestSuite, emptyStream)
{
  pdf1_7::FileStructure fileStruct;
  std::istringstream istream;
  EXPECT_FALSE(istream >> fileStruct);
}

TEST(FileStructureTestSuite, ok)
{
  pdf1_7::FileStructure fileStruct;
  std::istringstream istream(
    "%PDF−1.4\n"
    "1 0 obj\n"
    "<<\n"
    "/Type /Catalog\n"
    "/Outlines 2 0 R\n"
    "/Pages 3 0 R\n"
    ">>\n"
    "endobj\n"
    "2 0 obj\n"
    "<<\n"
    "/Type /Outlines\n"
    "/Count 0\n"
    ">>\n"
    "endobj\n"
    "3 0 obj\n"
    "<<\n"
    "/Type /Pages\n"
    "/Kids [ 4 0 R ]\n"
    "/Count 1\n"
    ">>\n"
    "endobj\n"
    "4 0 obj\n"
    "<<\n"
    "/Type /Page\n"
    "/Parent 3 0 R\n"
    "/MediaBox [ 0 0 612 792 ]\n"
    "/Contents 5 0 R\n"
    "/Resources << /ProcSet 6 0 R >>\n"
    ">>\n"
    "endobj\n"
    "5 0 obj\n"
    "<< /Length 35 >>\n"
    "stream\n"
    "... Page-marking operators ...\n"
    "endstream\n"
    "endobj\n"
    "6 0 obj\n"
    "[ /PDF ]\n"
    "endobj\n"
    "xref\n"
    "0 7\n"
    "0000000000 65535 f\n"
    "0000000009 00000 n\n"
    "0000000074 00000 n\n"
    "0000000120 00000 n\n"
    "0000000179 00000 n\n"
    "0000000300 00000 n\n"
    "0000000384 00000 n\n"
    "trailer\n"
    "<< /Size 7\n"
    "/Root 1 0 R\n"
    ">>\n"
    "startxref\n"
    "406\n"
    "%%EOF\n"
  );
  EXPECT_TRUE(istream >> fileStruct);
  EXPECT_EQ(1, fileStruct.versions_.size());
  EXPECT_EQ(1, fileStruct.versions_[0].xrefSection_.subsections().size());
  EXPECT_EQ(0, fileStruct.versions_[0].xrefSection_.subsections()[0].firstObjectNumber_);
  EXPECT_EQ(7, fileStruct.versions_[0].xrefSection_.subsections()[0].entries_.size());
  EXPECT_EQ(0, fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[0].offset_);
  EXPECT_EQ(65535, fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[0].generation_);
  EXPECT_FALSE(fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[0].inUseFlag_);
  EXPECT_EQ(9, fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[1].offset_);
  EXPECT_EQ(0, fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[1].generation_);
  EXPECT_TRUE(fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[1].inUseFlag_);
  EXPECT_EQ(74, fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[2].offset_);
  EXPECT_EQ(0, fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[2].generation_);
  EXPECT_TRUE(fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[2].inUseFlag_);
  EXPECT_EQ(120, fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[3].offset_);
  EXPECT_EQ(0, fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[3].generation_);
  EXPECT_TRUE(fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[3].inUseFlag_);
  EXPECT_EQ(179, fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[4].offset_);
  EXPECT_EQ(0, fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[4].generation_);
  EXPECT_TRUE(fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[4].inUseFlag_);
  EXPECT_EQ(300, fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[5].offset_);
  EXPECT_EQ(0, fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[5].generation_);
  EXPECT_TRUE(fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[5].inUseFlag_);
  EXPECT_EQ(384, fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[6].offset_);
  EXPECT_EQ(0, fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[6].generation_);
  EXPECT_TRUE(fileStruct.versions_[0].xrefSection_.subsections()[0].entries_[6].inUseFlag_);
}