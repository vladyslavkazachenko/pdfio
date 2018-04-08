#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_7/istream/read_file_structure.h"
#include "pdfio/pdf1_7/indirect_object.h"
#include "pdfio/pdf1_7/istream/read_indirect_object.h"

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

TEST(FileStructureTestSuite, xrefStream_ok)
{
	pdf1_7::IndirectObject indirectObject;
	indirectObject.set<pdf1_7::FileStructure::XrefStream>();
	unsigned char data[] = {
		0X31, 0X38, 0X30, 0X35, 0X35, 0X20,
		0X30, 0X20, 0X6F, 0X62, 0X6A, 0X0A, 0X3C, 0X3C, 0X0A, 0X2F, 0X44, 0X65,
		0X63, 0X6F, 0X64, 0X65, 0X50, 0X61, 0X72, 0X6D, 0X73, 0X20, 0X3C, 0X3C,
		0X0A, 0X2F, 0X43, 0X6F, 0X6C, 0X75, 0X6D, 0X6E, 0X73, 0X20, 0X36, 0X0A,
		0X2F, 0X50, 0X72, 0X65, 0X64, 0X69, 0X63, 0X74, 0X6F, 0X72, 0X20, 0X31,
		0X32, 0X0A, 0X3E, 0X3E, 0X0A, 0X2F, 0X46, 0X69, 0X6C, 0X74, 0X65, 0X72,
		0X20, 0X2F, 0X46, 0X6C, 0X61, 0X74, 0X65, 0X44, 0X65, 0X63, 0X6F, 0X64,
		0X65, 0X0A, 0X2F, 0X49, 0X44, 0X20, 0X5B, 0X20, 0X3C, 0X45, 0X32, 0X33,
		0X44, 0X38, 0X30, 0X37, 0X32, 0X30, 0X36, 0X34, 0X33, 0X30, 0X45, 0X36,
		0X34, 0X35, 0X43, 0X39, 0X32, 0X34, 0X42, 0X30, 0X38, 0X38, 0X38, 0X34,
		0X44, 0X37, 0X30, 0X43, 0X37, 0X3E, 0X20, 0X3C, 0X32, 0X31, 0X33, 0X45,
		0X44, 0X43, 0X32, 0X45, 0X31, 0X35, 0X44, 0X33, 0X42, 0X30, 0X32, 0X31,
		0X30, 0X34, 0X43, 0X42, 0X43, 0X44, 0X37, 0X42, 0X37, 0X35, 0X30, 0X43,
		0X38, 0X35, 0X34, 0X39, 0X3E, 0X20, 0X5D, 0X0A, 0X2F, 0X49, 0X6E, 0X64,
		0X65, 0X78, 0X20, 0X5B, 0X20, 0X38, 0X20, 0X31, 0X20, 0X31, 0X33, 0X39,
		0X30, 0X39, 0X20, 0X31, 0X20, 0X31, 0X37, 0X36, 0X39, 0X32, 0X20, 0X31,
		0X20, 0X31, 0X37, 0X36, 0X39, 0X37, 0X20, 0X31, 0X20, 0X31, 0X37, 0X36,
		0X39, 0X39, 0X20, 0X31, 0X20, 0X31, 0X38, 0X30, 0X35, 0X35, 0X20, 0X31,
		0X20, 0X5D, 0X0A, 0X2F, 0X49, 0X6E, 0X66, 0X6F, 0X20, 0X31, 0X37, 0X36,
		0X39, 0X37, 0X20, 0X30, 0X20, 0X52, 0X0A, 0X2F, 0X4C, 0X65, 0X6E, 0X67,
		0X74, 0X68, 0X20, 0X33, 0X36, 0X0A, 0X2F, 0X50, 0X72, 0X65, 0X76, 0X20,
		0X32, 0X31, 0X30, 0X31, 0X38, 0X37, 0X38, 0X38, 0X0A, 0X2F, 0X52, 0X6F,
		0X6F, 0X74, 0X20, 0X31, 0X37, 0X36, 0X39, 0X32, 0X20, 0X30, 0X20, 0X52,
		0X0A, 0X2F, 0X53, 0X69, 0X7A, 0X65, 0X20, 0X31, 0X38, 0X30, 0X35, 0X36,
		0X0A, 0X2F, 0X54, 0X79, 0X70, 0X65, 0X20, 0X2F, 0X58, 0X52, 0X65, 0X66,
		0X0A, 0X2F, 0X57, 0X20, 0X5B, 0X20, 0X31, 0X20, 0X34, 0X20, 0X31, 0X20,
		0X5D, 0X0A, 0X3E, 0X3E, 0X0A, 0X73, 0X74, 0X72, 0X65, 0X61, 0X6D, 0X0A,
		0X78, 0XDA, 0X63, 0X62, 0X64, 0X74, 0XD8, 0XBD, 0X9D, 0X81, 0X89, 0X81,
		0X81, 0X81, 0X71, 0X26, 0X98, 0X62, 0X82, 0XF0, 0XD8, 0XA3, 0XC1, 0XD4,
		0X8F, 0X40, 0X30, 0XC5, 0XD5, 0XCC, 0X00, 0X00, 0X78, 0X18, 0X05, 0X4C,
		0X0D, 0X65, 0X6E, 0X64, 0X73, 0X74, 0X72, 0X65, 0X61, 0X6D, 0X0A, 0X65,
		0X6E, 0X64, 0X6F, 0X62, 0X6A, 0X0A, 0X0A, 0X73, 0X74, 0X61, 0X72, 0X74,
		0X78, 0X72, 0X65, 0X66, 0X0A, 0X32, 0X31, 0X30, 0X32, 0X32, 0X35, 0X31,
		0X38, 0X0A, 0X25, 0X25, 0X45, 0X4F, 0X46};
	std::stringstream istream;
	istream.write(reinterpret_cast<char *>(data), sizeof(data));
	EXPECT_TRUE(istream >> indirectObject);
	auto &xrefStream = indirectObject.get<pdf1_7::FileStructure::XrefStream>();
	EXPECT_TRUE(xrefStream.type() == xrefStream.kXRef);
	EXPECT_EQ(18056, xrefStream.size());
	EXPECT_EQ(36, xrefStream.length());
	EXPECT_TRUE(xrefStream.hasDecodeParms());
	EXPECT_TRUE(xrefStream.decodeParms().contains(pdf1_7::FileStructure::XrefStream::kKeyColumns));
	EXPECT_EQ(6, xrefStream.decodeParms().get<pdf1_7::Integer>(
		pdf1_7::FileStructure::XrefStream::kKeyColumns));
	EXPECT_EQ(12, xrefStream.decodeParms().get<pdf1_7::Integer>(
		pdf1_7::FileStructure::XrefStream::kKeyPredictor));
	EXPECT_TRUE(xrefStream.hasFilter());
	EXPECT_TRUE(xrefStream.get<pdf1_7::Name>(
		pdf1_7::FileStructure::XrefStream::kKeyFilter) == "FlateDecode");
	EXPECT_TRUE(xrefStream.hasId());
	EXPECT_EQ(2, xrefStream.id().size());
	EXPECT_TRUE(xrefStream.id()[0] == "E23D807206430E645C924B08884D70C7");
	EXPECT_TRUE(xrefStream.id()[1] == "213EDC2E15D3B02104CBCD7B750C8549");
	EXPECT_TRUE(xrefStream.hasIndex());
	EXPECT_EQ(12, xrefStream.index().size());
	EXPECT_EQ(8, xrefStream.index()[0]);
	EXPECT_EQ(1, xrefStream.index()[1]);
	EXPECT_EQ(13909, xrefStream.index()[2]);
	EXPECT_EQ(1, xrefStream.index()[3]);
	EXPECT_EQ(17692, xrefStream.index()[4]);
	EXPECT_EQ(1, xrefStream.index()[5]);
	EXPECT_EQ(17697, xrefStream.index()[6]);
	EXPECT_EQ(1, xrefStream.index()[7]);
	EXPECT_EQ(17699, xrefStream.index()[8]);
	EXPECT_EQ(1, xrefStream.index()[9]);
	EXPECT_EQ(18055, xrefStream.index()[10]);
	EXPECT_EQ(1, xrefStream.index()[11]);
	EXPECT_TRUE(xrefStream.hasInfo());
	EXPECT_EQ(17697, xrefStream.info().objectNumber());
	EXPECT_EQ(0, xrefStream.info().generationNumber());
	EXPECT_TRUE(xrefStream.hasPrev());
	EXPECT_EQ(21018788, xrefStream.prev());
	EXPECT_TRUE(xrefStream.hasRoot());
	EXPECT_EQ(17692, xrefStream.root().objectNumber());
	EXPECT_EQ(0, xrefStream.root().generationNumber());
	EXPECT_EQ(3, xrefStream.w().size());
	EXPECT_EQ(1, xrefStream.w()[0]);
	EXPECT_EQ(4, xrefStream.w()[1]);
	EXPECT_EQ(1, xrefStream.w()[2]);
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