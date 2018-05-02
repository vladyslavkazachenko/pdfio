#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_4/istream/read_file_version.h"

namespace pdf1_4 = pdfio::pdf1_4;

TEST(FileVersionTestSuite, header1)
{
   pdf1_4::FileVersion::Header header;
   std::istringstream istream("%PDF-1.0");
   EXPECT_TRUE(istream >> header);
}

TEST(FileVersionTestSuite, header2)
{
   pdf1_4::FileVersion::Header header;
   std::istringstream istream("%PDF-1.1");
   EXPECT_TRUE(istream >> header);
}

TEST(FileVersionTestSuite, header3)
{
   pdf1_4::FileVersion::Header header;
   unsigned char data[] = {0x25, 0x50, 0x44, 0x46, 0x2d, 0x31, 0x2e, 0x32};
   std::stringstream istream;
   istream.write(reinterpret_cast<char *>(data), sizeof(data));
   EXPECT_TRUE(istream >> header);
}

TEST(FileVersionTestSuite, header4)
{
   pdf1_4::FileVersion::Header header;
   std::istringstream istream("%PDF-1.3");
   EXPECT_TRUE(istream >> header);
}

TEST(FileVersionTestSuite, header5)
{
   pdf1_4::FileVersion::Header header;
   std::istringstream istream("%PDF-1.4");
   EXPECT_TRUE(istream >> header);
}

TEST(FileVersionTestSuite, header6)
{
   pdf1_4::FileVersion::Header header;
   std::istringstream istream("%PDF-1.5");
   EXPECT_FALSE(istream >> header);
}

TEST(FileVersionTestSuite, header7)
{
   pdf1_4::FileVersion::Header header;
   std::istringstream istream("%PDF-1.6");
   EXPECT_FALSE(istream >> header);
}

TEST(FileVersionTestSuite, header8)
{
   pdf1_4::FileVersion::Header header;
   std::istringstream istream("%PDF-1.7");
   EXPECT_FALSE(istream >> header);
}


TEST(FileVersionTestSuite, xrefEntry1)
{
   pdf1_4::FileVersion::XrefEntry entry;
   std::istringstream istream1("1234567890 12345 n");
   EXPECT_TRUE(istream1 >> entry);
   EXPECT_EQ(1234567890, entry.offset_);
   EXPECT_EQ(12345, entry.generation_);
   EXPECT_TRUE(entry.inUseFlag_);
}

TEST(FileVersionTestSuite, xrefEntry2)
{
   pdf1_4::FileVersion::XrefEntry entry;
   std::istringstream istream2("67890 23456 f");
   EXPECT_TRUE(istream2 >> entry);
   EXPECT_EQ(67890, entry.offset_);
   EXPECT_EQ(23456, entry.generation_);
   EXPECT_FALSE(entry.inUseFlag_);
}

TEST(FileVersionTestSuite, trailer1)
{
   pdf1_4::FileVersion::Trailer trailer;
   std::istringstream istream(
      "trailer\n"
      "<< /Size 22"
      "/Root 2 0 R"
      "/Info 1 0 R"
      "/ID [ < 81b14aafa313db63dbd6f981e49f94f4 >"
      "< 81b14aafa313db63dbd6f981e49f94f4 >"
      "]"
      ">>"
      "startxref\n"
      "18799\n"
      "%%EOF"
   );
   EXPECT_TRUE(istream >> trailer);
   EXPECT_EQ(22, trailer.size());
   EXPECT_TRUE(trailer.hasRoot());
   EXPECT_EQ(2, trailer.root().objectNumber());
   EXPECT_EQ(0, trailer.root().generationNumber());
   EXPECT_TRUE(trailer.hasInfo());
   EXPECT_EQ(1, trailer.info().objectNumber());
   EXPECT_EQ(0, trailer.info().generationNumber());
   EXPECT_TRUE(trailer.hasId());
   EXPECT_EQ(2, trailer.id().size());
   EXPECT_TRUE(trailer.id()[0] == "81b14aafa313db63dbd6f981e49f94f4");
   EXPECT_TRUE(trailer.id()[1] == "81b14aafa313db63dbd6f981e49f94f4");
}
