#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_0/istream/read_indirect_object.h"
#include "pdfio/pdf1_0/generic_object_type.h"
#include "pdfio/pdf1_0/file_structure.h"
#include "pdfio/pdf1_0/outline_tree.h"
#include "pdfio/pdf1_0/document_pages_tree.h"
#include "pdfio/pdf1_0/info.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(IndirectObjectTestSuite, emptyStream)
{
   pdf1_0::IndirectObject indirectObject;
   std::istringstream istream;
   EXPECT_FALSE(istream >> indirectObject);
}

TEST(IndirectObjectTestSuite, wrongObjectNumber)
{
   pdf1_0::IndirectObject indirectObject;
   std::istringstream istream("whatever");
   EXPECT_FALSE(istream >> indirectObject);
}

TEST(IndirectObjectTestSuite, wrongGenerationNumber)
{
   pdf1_0::IndirectObject indirectObject1;
   std::istringstream istream1("23");
   EXPECT_FALSE(istream1 >> indirectObject1);
   
   pdf1_0::IndirectObject indirectObject2;
   std::istringstream istream2("23 whatever");
   EXPECT_FALSE(istream2 >> indirectObject2);
}

TEST(IndirectObjectTestSuite, obj)
{
   pdf1_0::IndirectObject indirectObject1;
   std::istringstream istream1("23 1");
   EXPECT_FALSE(istream1 >> indirectObject1);
   
   pdf1_0::IndirectObject indirectObject2;
   std::istringstream istream2("23 1 whatever");
   EXPECT_FALSE(istream2 >> indirectObject2);
}

TEST(IndirectObjectTestSuite, endobj)
{
   pdf1_0::IndirectObject indirectObject1;
   indirectObject1.set<pdf1_0::Integer>();
   std::istringstream istream1("23 1 obj 678");
   EXPECT_FALSE(istream1 >> indirectObject1);
   
   pdf1_0::IndirectObject indirectObject2;
   indirectObject2.set<pdf1_0::Integer>();
   std::istringstream istream2("23 1 obj 678 whatever");
   EXPECT_FALSE(istream2 >> indirectObject2);
}

TEST(IndirectObjectTestSuite, integer)
{
   pdf1_0::IndirectObject indirectObject1;
   indirectObject1.set<pdf1_0::Integer>();
   std::istringstream istream1("23 1 obj whatever endobj");
   EXPECT_FALSE(istream1 >> indirectObject1);
   
   pdf1_0::IndirectObject indirectObject2;
   indirectObject2.set<pdf1_0::Integer>();
   std::istringstream istream2("23 1 obj 678 endobj");
   EXPECT_TRUE(istream2 >> indirectObject2);
   EXPECT_TRUE(indirectObject2.objectNumber() == 23);
   EXPECT_TRUE(indirectObject2.generationNumber() == 1);
   EXPECT_TRUE(indirectObject2.get<pdf1_0::Integer>() == 678);
}

TEST(IndirectObjectTestSuite, name)
{
   pdf1_0::IndirectObject indirectObject1;
   indirectObject1.set<pdf1_0::Name>();
   std::istringstream istream1("23 1 obj whatever endobj");
   EXPECT_FALSE(istream1 >> indirectObject1);
   
   pdf1_0::IndirectObject indirectObject2;
   indirectObject2.set<pdf1_0::Name>();
   std::istringstream istream2("23 1 obj /name endobj");
   EXPECT_TRUE(istream2 >> indirectObject2);
   EXPECT_TRUE(indirectObject2.objectNumber() == 23);
   EXPECT_TRUE(indirectObject2.generationNumber() == 1);
   EXPECT_TRUE(indirectObject2.get<pdf1_0::Name>() == "name");
}

TEST(IndirectObjectTestSuite, indirectReference)
{
   pdf1_0::IndirectObject indirectObject1;
   indirectObject1.set<pdf1_0::IndirectReference>();
   std::istringstream istream1("23 1 obj whatever endobj");
   EXPECT_FALSE(istream1 >> indirectObject1);
   
   pdf1_0::IndirectObject indirectObject2;
   indirectObject2.set<pdf1_0::IndirectReference>();
   std::istringstream istream2("23 1 obj 543 3 R endobj");
   EXPECT_TRUE(istream2 >> indirectObject2);
   EXPECT_EQ(23, indirectObject2.objectNumber());
   EXPECT_EQ(1, indirectObject2.generationNumber());
   EXPECT_EQ(543, 
      indirectObject2.get<pdf1_0::IndirectReference>().objectNumber());
   EXPECT_EQ(3, 
      indirectObject2.get<pdf1_0::IndirectReference>().generationNumber());
}

TEST(IndirectObjectTestSuite, dictionary)
{
   pdf1_0::IndirectObject indirectObject1;
   pdf1_0::Dictionary dictionary1;
   indirectObject1.set(dictionary1);
   std::istringstream istream1("23 1 obj whatever endobj");
   EXPECT_FALSE(istream1 >> indirectObject1);
   
   pdf1_0::IndirectObject indirectObject2;
   pdf1_0::Dictionary dictionary2;
   dictionary2.insert<pdf1_0::Name>(pdf1_0::Name("key"));
   indirectObject2.set(dictionary2);
   std::istringstream istream2("23 1 obj << /key /value >> endobj");
   EXPECT_TRUE(istream2 >> indirectObject2);
   EXPECT_EQ(23, indirectObject2.objectNumber());
   EXPECT_EQ(1, indirectObject2.generationNumber());
   EXPECT_TRUE(
      indirectObject2.get<pdf1_0::Dictionary>().get<pdf1_0::Name>(
      pdf1_0::Name("key")) == "value");
}

TEST(IndirectObjectTestSuite, DISABLED_fileStructureXrefSection_ok)
{
   pdf1_0::IndirectObject indirectObject;
   indirectObject.set<pdf1_0::Stream>();
   unsigned char xref [] = {
      0x38, 0x34, 0x37, 0x30, 0x20, 0x30, 0x20, 0x6f, 0x62, 0x6a, 0x0a, 0x3c,
      0x3c, 0x2f, 0x44, 0x65, 0x63, 0x6f, 0x64, 0x65, 0x50, 0x61, 0x72, 0x6d,
      0x73, 0x3c, 0x3c, 0x2f, 0x43, 0x6f, 0x6c, 0x75, 0x6d, 0x6e, 0x73, 0x20,
      0x35, 0x2f, 0x50, 0x72, 0x65, 0x64, 0x69, 0x63, 0x74, 0x6f, 0x72, 0x20,
      0x31, 0x32, 0x3e, 0x3e, 0x2f, 0x46, 0x69, 0x6c, 0x74, 0x65, 0x72, 0x2f,
      0x46, 0x6c, 0x61, 0x74, 0x65, 0x44, 0x65, 0x63, 0x6f, 0x64, 0x65, 0x2f,
      0x49, 0x44, 0x5b, 0x3c, 0x43, 0x37, 0x32, 0x31, 0x32, 0x31, 0x38, 0x43,
      0x38, 0x42, 0x36, 0x45, 0x42, 0x33, 0x34, 0x30, 0x38, 0x46, 0x30, 0x44,
      0x39, 0x43, 0x45, 0x42, 0x41, 0x43, 0x33, 0x39, 0x37, 0x45, 0x35, 0x41,
      0x3e, 0x3c, 0x45, 0x41, 0x41, 0x45, 0x41, 0x35, 0x32, 0x39, 0x38, 0x35,
      0x37, 0x39, 0x34, 0x42, 0x36, 0x39, 0x41, 0x42, 0x33, 0x39, 0x45, 0x44,
      0x37, 0x38, 0x31, 0x41, 0x37, 0x31, 0x35, 0x42, 0x42, 0x36, 0x3e, 0x5d,
      0x2f, 0x49, 0x6e, 0x64, 0x65, 0x78, 0x5b, 0x38, 0x34, 0x35, 0x34, 0x20,
      0x37, 0x35, 0x35, 0x5d, 0x2f, 0x49, 0x6e, 0x66, 0x6f, 0x20, 0x38, 0x34,
      0x35, 0x33, 0x20, 0x30, 0x20, 0x52, 0x2f, 0x4c, 0x65, 0x6e, 0x67, 0x74,
      0x68, 0x20, 0x31, 0x33, 0x35, 0x2f, 0x50, 0x72, 0x65, 0x76, 0x20, 0x39,
      0x37, 0x35, 0x36, 0x33, 0x36, 0x38, 0x2f, 0x52, 0x6f, 0x6f, 0x74, 0x20,
      0x38, 0x34, 0x35, 0x35, 0x20, 0x30, 0x20, 0x52, 0x2f, 0x53, 0x69, 0x7a,
      0x65, 0x20, 0x39, 0x32, 0x30, 0x39, 0x2f, 0x54, 0x79, 0x70, 0x65, 0x2f,
      0x58, 0x52, 0x65, 0x66, 0x2f, 0x57, 0x5b, 0x31, 0x20, 0x33, 0x20, 0x31,
      0x5d, 0x3e, 0x3e, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6d, 0x0a, 0x68, 0x5c,
      0x44, 0x45, 0x62, 0x62, 0x64, 0x60, 0x10, 0x60, 0x60, 0x62, 0x60, 0x5c,
      0x39, 0x30, 0x7a, 0x0f, 0x22, 0x19, 0x5c, 0x46, 0x46, 0x5c, 0x38, 0x32,
      0x49, 0x3d, 0x10, 0x5c, 0x43, 0x39, 0x70, 0x14, 0xcc, 0x8e, 0x02, 0x5c,
      0x39, 0x33, 0x60, 0x59, 0x5c, 0x46, 0x45, 0x5c, 0x41, 0x46, 0x40, 0x5c,
      0x39, 0x32, 0xc3, 0xa7, 0x01, 0x5c, 0x43, 0x34, 0x5c, 0x45, 0x36, 0x5c,
      0x39, 0x41, 0x05, 0x22, 0x39, 0x5c, 0x38, 0x45, 0x5c, 0x38, 0x33, 0x48,
      0x5c, 0x42, 0x36, 0x5c, 0x41, 0x35, 0x60, 0x5c, 0x46, 0x36, 0x3d, 0x30,
      0x79, 0x16, 0x44, 0x5c, 0x42, 0x32, 0xd7, 0x83, 0xd9, 0xb7, 0x5c, 0x38,
      0x30, 0xe4, 0x8f, 0x80, 0x5c, 0x42, 0x44, 0x0c, 0x4c, 0x5c, 0x38, 0x43,
      0x0c, 0x5c, 0x38, 0x41, 0x5c, 0x44, 0x33, 0x5c, 0x43, 0x31, 0x66, 0x32,
      0x30, 0x5c, 0x38, 0x32, 0x48, 0x5c, 0x45, 0x36, 0x5c, 0x46, 0x46, 0x08,
      0x5c, 0x46, 0x36, 0x28, 0x39, 0x4a, 0x52, 0x5c, 0x38, 0x42, 0x64, 0x5c,
      0x39, 0x43, 0x3b, 0x1a, 0x0e, 0x5c, 0x41, 0x33, 0x5c, 0x45, 0x34, 0x68,
      0x5c, 0x42, 0x41, 0x1a, 0x25, 0x47, 0x5c, 0x44, 0x33, 0x5c, 0x44, 0x35,
      0x28, 0x39, 0x5c, 0x39, 0x41, 0x5c, 0x41, 0x45, 0x46, 0x5c, 0x43, 0x39,
      0x51, 0x72, 0x34, 0x5d, 0x5c, 0x38, 0x44, 0x5c, 0x39, 0x32, 0x5c, 0x41,
      0x33, 0x5c, 0x45, 0x39, 0x6a, 0x5c, 0x39, 0x34, 0x1c, 0x4d, 0x57, 0x43,
      0x5c, 0x39, 0x45, 0x5c, 0x46, 0x43, 0x5c, 0x43, 0x46, 0x5c, 0x46, 0x30,
      0x5c, 0x44, 0x32, 0x5c, 0x45, 0x32, 0x1e, 0x40, 0x5c, 0x38, 0x30, 0x01,
      0x5c, 0x30, 0x30, 0x5c, 0x44, 0x35, 0x30, 0x1f, 0x3f, 0x0a, 0x65, 0x6e,
      0x64, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6d, 0x0a, 0x65, 0x6e, 0x64, 0x6f,
      0x62, 0x6a, 0x0a
   };
   std::stringstream istream;
   istream.write(reinterpret_cast<char *>(xref), sizeof(xref));
   EXPECT_TRUE(istream >> indirectObject);
}

TEST(IndirectObjectTestSuite, outlineTree)
{
   pdf1_0::IndirectObject indirectObject;
   indirectObject.set<pdf1_0::OutlineTree>();
   std::istringstream istream(
      "21 0 obj"
      "<<"
      "/Count 6"
      "/First 22 0 R"
      "/Last 29 0 R"
      ">>"
      "endobj");
   EXPECT_TRUE(istream >> indirectObject);
}

TEST(IndirectObjectTestSuite, outlineTreeEntry)
{
   pdf1_0::IndirectObject indirectObject;
   indirectObject.set<pdf1_0::OutlineTree::Entry>();
   std::istringstream istream(
      "21 0 obj"
      "<<"
      "/Parent 21 0 R"
      "/Dest [ 3 0 R /Top 0 792 0 ]"
      "/Title (Document)"
      "/Next 29 0 R"
      "/First 25 0 R"
      "/Last 28 0 R"
      "/Count 4"
      ">>"
      "endobj");
   EXPECT_TRUE(istream >> indirectObject);
}

TEST(IndirectObjectTestSuite, documentPagesTree1)
{
   pdf1_0::IndirectObject indirectObject;
   indirectObject.set<pdf1_0::DocumentPagesTree>();
   std::istringstream istream(
      "21 0 obj"
      "<<"
      "/Type /Pages"
      "/Kids [ 4 0 R 10 0 R 24 0 R ]"
      "/Count 3"
      "/Parent 25 0 R"
      ">>"
      "endobj");
   EXPECT_TRUE(istream >> indirectObject);
}

TEST(IndirectObjectTestSuite, documentPagesTree2)
{
   pdf1_0::IndirectObject indirectObject;
   indirectObject.set<pdf1_0::DocumentPagesTree>();
   std::istringstream istream(
      "21 0 obj"
      "<</CropBox[0 0 531 666]/Annots[7882 0 R 7880 0 R 7883 0 R"
      " 7881 0 R 7876 0 R 7877 0 R 7878 0 R 7879 0 R]/Parent 109892 0 R"
      "/StructParents 4648/Contents 2027 0 R/Rotate 0"
      "/MediaBox[0 0 531 666]/Resources<</Font<</T1_0 3914 0 R"
      "/T1_1 3912 0 R/T1_2 3957 0 R/T1_3 3944 0 R/T1_4 3931 0 R"
      "/T1_5 4161 0 R/T1_6 4533 0 R>>/ProcSet[/PDF/Text]"
      "/ExtGState<</GS0 333283 0 R>>>>/Type/Page>>"
      "endobj");
   EXPECT_TRUE(istream >> indirectObject);
}

TEST(IndirectObjectTestSuite, info)
{
   pdf1_0::IndirectObject indirectObject;
   indirectObject.set<pdf1_0::Info>();
   std::istringstream istream(
      "1 0 obj"
      "<<"
      "/Creator (Adobe Illustrator)"
      "/CreationDate (Thursday Feb 04 08:06:03 1993)"
      "/Author (Werner Heisenberg)"
      "/Producer (Acrobat Network Distiller 1.0 for Macintosh)"
      ">>"
      "endobj");
   EXPECT_TRUE(istream >> indirectObject);
}
