#include "gtest/gtest.h"
#include "pdfio/pdf1_7/file_structure.h"

namespace pdf1_7 = pdfio::pdf1_7;

TEST(FileStructureTestSuite, xrefEntry)
{
	pdf1_7::FileStructure::XrefEntry xrefEntry1;
	EXPECT_EQ(0, xrefEntry1.offset_);
	EXPECT_EQ(0, xrefEntry1.generation_);
	EXPECT_TRUE(xrefEntry1.inUseFlag_);
	
	pdf1_7::FileStructure::XrefEntry xrefEntry2 = {1234567890, 12345, false};
	EXPECT_EQ(1234567890, xrefEntry2.offset_);
	EXPECT_EQ(12345, xrefEntry2.generation_);
	EXPECT_FALSE(xrefEntry2.inUseFlag_);
	
	pdf1_7::FileStructure::XrefEntry xrefEntry3;
	xrefEntry3.offset_ = 234;
	xrefEntry3.generation_ = 2;
	xrefEntry3.inUseFlag_ = false;
	EXPECT_EQ(234, xrefEntry3.offset_);
	EXPECT_EQ(2, xrefEntry3.generation_);
	EXPECT_FALSE(xrefEntry3.inUseFlag_);
}

TEST(FileStructureTestSuite, xrefSubsection)
{
	pdf1_7::FileStructure::XrefSubsection xrefSubsection1;
	EXPECT_EQ(0, xrefSubsection1.firstObjectNumber_);
	EXPECT_TRUE(xrefSubsection1.entries_.empty());
	
	pdf1_7::FileStructure::XrefSubsection xrefSubsection2;
	xrefSubsection2.firstObjectNumber_ = 12345;
	xrefSubsection2.entries_.push_back(pdf1_7::FileStructure::XrefEntry({1234567890, 12345, false}));
	EXPECT_EQ(12345, xrefSubsection2.firstObjectNumber_);
	EXPECT_EQ(1, xrefSubsection2.entries_.size());
	EXPECT_EQ(1234567890, xrefSubsection2.entries_[0].offset_);
	EXPECT_EQ(12345, xrefSubsection2.entries_[0].generation_);
	EXPECT_FALSE(xrefSubsection2.entries_[0].inUseFlag_);
}

TEST(FileStructureTestSuite, xrefSection)
{
	pdf1_7::FileStructure::XrefSection xrefSection1;
	EXPECT_TRUE(xrefSection1.subsections().empty());
	
	pdf1_7::FileStructure::XrefSection xrefSection2;
	pdf1_7::FileStructure::XrefSubsection xrefSubsection21;
	xrefSubsection21.firstObjectNumber_ = 0;
	xrefSubsection21.entries_.push_back(pdf1_7::FileStructure::XrefEntry({1234567890, 12345, false}));
	EXPECT_TRUE(xrefSection2.add(xrefSubsection21));
}

TEST(FileStructureTestSuite, trailer)
{
	pdf1_7::FileStructure::Trailer trailer1;
	EXPECT_EQ(0, trailer1.size());
	EXPECT_FALSE(trailer1.hasPrev());
	EXPECT_FALSE(trailer1.hasRoot());
	EXPECT_FALSE(trailer1.hasEncrypt());
	EXPECT_FALSE(trailer1.hasInfo());
	EXPECT_FALSE(trailer1.hasId());
}

TEST(FileStructureTestSuite, version)
{
	pdf1_7::FileStructure::Version version1;
	EXPECT_TRUE(version1.xrefSection_.subsections().empty());
	EXPECT_EQ(0, version1.trailer_.size());
	EXPECT_FALSE(version1.trailer_.hasPrev());
	EXPECT_FALSE(version1.trailer_.hasRoot());
	EXPECT_FALSE(version1.trailer_.hasEncrypt());
	EXPECT_FALSE(version1.trailer_.hasInfo());
	EXPECT_FALSE(version1.trailer_.hasId());
}

TEST(FileStructureTestSuite, defaultCtor)
{
	pdf1_7::FileStructure fileStruct;
	EXPECT_TRUE(fileStruct.versions_.empty());
}