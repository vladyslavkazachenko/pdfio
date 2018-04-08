#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_0/istream/read_file_structure.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(FileStructureTestSuite, xrefEntry_emptyStream)
{
  pdf1_0::FileStructure::XrefEntry xrefEntry;
  std::istringstream istream;
  EXPECT_FALSE(istream >> xrefEntry);
}

TEST(FileStructureTestSuite, xrefEntry_ok)
{
  pdf1_0::FileStructure::XrefEntry xrefEntry1;
  std::istringstream istream1("1234567890 12345 n");
  EXPECT_TRUE(istream1 >> xrefEntry1);
  EXPECT_EQ(1234567890, xrefEntry1.offset_);
  EXPECT_EQ(12345, xrefEntry1.generation_);
  EXPECT_TRUE(xrefEntry1.inUseFlag_);
  
  pdf1_0::FileStructure::XrefEntry xrefEntry2;
  std::istringstream istream2("67890 23456 f");
  EXPECT_TRUE(istream2 >> xrefEntry2);
  EXPECT_EQ(67890, xrefEntry2.offset_);
  EXPECT_EQ(23456, xrefEntry2.generation_);
  EXPECT_FALSE(xrefEntry2.inUseFlag_);
}

TEST(FileStructureTestSuite, xrefSubsection_emptyStream)
{
  pdf1_0::FileStructure::XrefSubsection xrefSubsection;
  std::istringstream istream;
  EXPECT_FALSE(istream >> xrefSubsection);
}

TEST(FileStructureTestSuite, xrefSubsection_ok)
{
  pdf1_0::FileStructure::XrefSubsection xrefSubsection;
  std::istringstream istream(
    "0 6\r\n"
    "0000000003 65535 f\r\n"
    "0000000017 00000 n\r\n"
    "0000000081 00000 n\r\n"
    "0000000000 00007 f\r\n"
    "0000000331 00000 n\r\n"
    "0000000409 00000 n\r\n"
  );
  EXPECT_TRUE(istream >> xrefSubsection);
  EXPECT_EQ(0, xrefSubsection.firstObjectNumber_);
  EXPECT_EQ(6, xrefSubsection.entries_.size());
  EXPECT_EQ(3, xrefSubsection.entries_[0].offset_);
  EXPECT_EQ(65535, xrefSubsection.entries_[0].generation_);
  EXPECT_EQ(17, xrefSubsection.entries_[1].offset_);
  EXPECT_EQ(0, xrefSubsection.entries_[1].generation_);
  EXPECT_EQ(81, xrefSubsection.entries_[2].offset_);
  EXPECT_EQ(0, xrefSubsection.entries_[2].generation_);
  EXPECT_EQ(0, xrefSubsection.entries_[3].offset_);
  EXPECT_EQ(7, xrefSubsection.entries_[3].generation_);
  EXPECT_EQ(331, xrefSubsection.entries_[4].offset_);
  EXPECT_EQ(0, xrefSubsection.entries_[4].generation_);
  EXPECT_EQ(409, xrefSubsection.entries_[5].offset_);
  EXPECT_EQ(0, xrefSubsection.entries_[5].generation_);
}

TEST(FileStructureTestSuite, xrefSection_emptyStream)
{
  pdf1_0::FileStructure::XrefSection xrefSection;
  std::istringstream istream;
  EXPECT_FALSE(istream >> xrefSection);
}

TEST(FileStructureTestSuite, xrefSection_ok)
{
  pdf1_0::FileStructure::XrefSection xrefSection;
  std::istringstream istream("xref\r"
    "0 6\r"
    "0000000003 65535 f\r"
    "0000000017 00000 n\r"
    "0000000081 00000 n\r"
    "0000000000 00007 f\r"
    "0000000331 00000 n\r"
    "0000000409 00000 n\r"
  );
  EXPECT_TRUE(istream >> xrefSection);
  EXPECT_EQ(1, xrefSection.subsections().size());
  EXPECT_EQ(0, xrefSection.subsections()[0].firstObjectNumber_);
  EXPECT_EQ(6, xrefSection.subsections()[0].entries_.size());
  EXPECT_EQ(3, xrefSection.subsections()[0].entries_[0].offset_);
  EXPECT_EQ(65535, xrefSection.subsections()[0].entries_[0].generation_);
  EXPECT_EQ(17, xrefSection.subsections()[0].entries_[1].offset_);
  EXPECT_EQ(0, xrefSection.subsections()[0].entries_[1].generation_);
  EXPECT_EQ(81, xrefSection.subsections()[0].entries_[2].offset_);
  EXPECT_EQ(0, xrefSection.subsections()[0].entries_[2].generation_);
  EXPECT_EQ(0, xrefSection.subsections()[0].entries_[3].offset_);
  EXPECT_EQ(7, xrefSection.subsections()[0].entries_[3].generation_);
  EXPECT_EQ(331, xrefSection.subsections()[0].entries_[4].offset_);
  EXPECT_EQ(0, xrefSection.subsections()[0].entries_[4].generation_);
  EXPECT_EQ(409, xrefSection.subsections()[0].entries_[5].offset_);
  EXPECT_EQ(0, xrefSection.subsections()[0].entries_[5].generation_);
}

TEST(FileStructureTestSuite, trailer_emptyStream)
{
  pdf1_0::FileStructure::Trailer trailer;
  std::istringstream istream;
  EXPECT_FALSE(istream >> trailer);
}

TEST(FileTrailerTestSuite, trailer_ok)
{
	pdf1_0::FileStructure::Trailer trailer;
	std::istringstream istream("trailer << /Size 123 /Root 234 1 R >> startxref 456 %%EOF");
	EXPECT_TRUE(istream >> trailer);
	EXPECT_TRUE(trailer.size() == 123);
	EXPECT_FALSE(trailer.hasPrev());
	EXPECT_TRUE(trailer.root().objectNumber() == 234);
	EXPECT_TRUE(trailer.root().generationNumber() == 1);
	EXPECT_FALSE(trailer.hasInfo());
}