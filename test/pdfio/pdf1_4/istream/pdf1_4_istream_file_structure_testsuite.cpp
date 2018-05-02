#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_4/istream/read_file_structure.h"

namespace pdf1_4 = pdfio::pdf1_4;

TEST(FileStructureTestSuite, ok1)
{
   pdfio::FileStructure<pdf1_4::FileVersion> fileStruct;
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
   EXPECT_TRUE(fileStruct.header_.data_ == "%PDF−1.4");
   EXPECT_EQ(1, fileStruct.versions_.size());
   EXPECT_EQ(1, fileStruct.versions_.front().xrefSection_.subsections().size());
   const auto &subsection = 
      fileStruct.versions_.front().xrefSection_.subsections()[0];
   EXPECT_EQ(0, subsection.firstObjectNumber_);
   EXPECT_EQ(7, subsection.entries_.size());
   EXPECT_EQ(0, subsection.entries_[0].offset_);
   EXPECT_EQ(65535, subsection.entries_[0].generation_);
   EXPECT_FALSE(subsection.entries_[0].inUseFlag_);
   EXPECT_EQ(9, subsection.entries_[1].offset_);
   EXPECT_EQ(0, subsection.entries_[1].generation_);
   EXPECT_TRUE(subsection.entries_[1].inUseFlag_);
   EXPECT_EQ(74, subsection.entries_[2].offset_);
   EXPECT_EQ(0, subsection.entries_[2].generation_);
   EXPECT_TRUE(subsection.entries_[2].inUseFlag_);
   EXPECT_EQ(120, subsection.entries_[3].offset_);
   EXPECT_EQ(0, subsection.entries_[3].generation_);
   EXPECT_TRUE(subsection.entries_[3].inUseFlag_);
   EXPECT_EQ(179, subsection.entries_[4].offset_);
   EXPECT_EQ(0, subsection.entries_[4].generation_);
   EXPECT_TRUE(subsection.entries_[4].inUseFlag_);
   EXPECT_EQ(300, subsection.entries_[5].offset_);
   EXPECT_EQ(0, subsection.entries_[5].generation_);
   EXPECT_TRUE(subsection.entries_[5].inUseFlag_);
   EXPECT_EQ(384, subsection.entries_[6].offset_);
   EXPECT_EQ(0, subsection.entries_[6].generation_);
   EXPECT_TRUE(subsection.entries_[6].inUseFlag_);
   const auto &trailer = fileStruct.versions_.front().trailer_;
   EXPECT_EQ(7, trailer.size());
   EXPECT_TRUE(trailer.hasRoot());
   EXPECT_EQ(1, trailer.root().objectNumber());
   EXPECT_EQ(0, trailer.root().generationNumber());
}
