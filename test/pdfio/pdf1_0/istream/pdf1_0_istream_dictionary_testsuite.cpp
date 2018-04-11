#include <sstream>

#include "pdfio/pdf1_0/istream/read_dictionary.h"
#include "pdfio/pdf1_0/generic_object_type.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(DictionaryTestSuite, emptyStream)
{
   pdf1_0::Dictionary dictionary;
   std::istringstream istream;
   EXPECT_FALSE(istream >> dictionary);
}

TEST(DictionaryTestSuite, wrong1stDelimiter)
{
   pdf1_0::Dictionary dictionary1;
   std::istringstream istream1("<");
   EXPECT_FALSE(istream1 >> dictionary1);
   
   pdf1_0::Dictionary dictionary2;
   std::istringstream istream2(">>");
   EXPECT_FALSE(istream2 >> dictionary2);
}

TEST(DictionaryTestSuite, dictionaryWithName)
{
   pdf1_0::Dictionary dictionary;
   dictionary.insert<pdf1_0::Name>(pdf1_0::Name("key"));
   std::istringstream istream("<< /key /value >>");
   EXPECT_TRUE(istream >> dictionary);
   EXPECT_TRUE(dictionary.get<pdf1_0::Name>(std::string("key")) == "value");
}

TEST(DictionaryTestSuite, dictionaryWith2Names)
{
   pdf1_0::Dictionary dictionary;
   dictionary.insert<pdf1_0::Name>(pdf1_0::Name("key1"));
   dictionary.insert<pdf1_0::Name>(pdf1_0::Name("key2"));
   std::istringstream istream("<< /key1 /value1 /key2 /value2 >>");
   EXPECT_TRUE(istream >> dictionary);
   EXPECT_TRUE(dictionary.get<pdf1_0::Name>(std::string("key1")) == "value1");
   EXPECT_TRUE(dictionary.get<pdf1_0::Name>(std::string("key2")) == "value2");
}

TEST(DictionaryTestSuite, dictionaryWithInteger)
{
   pdf1_0::Dictionary dictionary;
   dictionary.insert<pdf1_0::Integer>(pdf1_0::Name("key"));
   std::istringstream istream("<< /key 12345 >>");
   EXPECT_TRUE(istream >> dictionary);
   EXPECT_TRUE(dictionary.get<pdf1_0::Integer>(std::string("key")) == 12345);
}

TEST(DictionaryTestSuite, dictionaryWith2Integers)
{
   pdf1_0::Dictionary dictionary;
   dictionary.insert<pdf1_0::Integer>(pdf1_0::Name("key1"));
   dictionary.insert<pdf1_0::Integer>(pdf1_0::Name("key2"));
   std::istringstream istream("<< /key1 12345 /key2 -56789>>");
   EXPECT_TRUE(istream >> dictionary);
   EXPECT_TRUE(dictionary.get<pdf1_0::Integer>(std::string("key1")) == 12345);
   EXPECT_TRUE(dictionary.get<pdf1_0::Integer>(std::string("key2")) == -56789);
}

TEST(DictionaryTestSuite, wrong2ndDelimiter)
{
   pdf1_0::Dictionary dictionary1;
   std::istringstream istream1("<< /key1 /value1");
   EXPECT_FALSE(istream1 >> dictionary1);
}

TEST(DictionaryTestSuite, dictionaryWithIndirectReference)
{
   pdf1_0::Dictionary dictionary;
   dictionary.insert<pdf1_0::IndirectReference>(pdf1_0::Name("key"));
   std::istringstream istream("<< /key 1 2 R >>");
   EXPECT_TRUE(istream >> dictionary);
   EXPECT_TRUE(dictionary.get<pdf1_0::IndirectReference>(std::string("key")).objectNumber() == 1);
   EXPECT_TRUE(dictionary.get<pdf1_0::IndirectReference>(std::string("key")).generationNumber() == 2);
}

TEST(DictionaryTestSuite, dictionaryWith2IndirectReferences)
{
   pdf1_0::Dictionary dictionary;
   dictionary.insert<pdf1_0::IndirectReference>(pdf1_0::Name("key1"));
   dictionary.insert<pdf1_0::IndirectReference>(pdf1_0::Name("key2"));
   std::istringstream istream("<< /key1 1 2 R /key2 2 3 R >>");
   EXPECT_TRUE(istream >> dictionary);
   EXPECT_TRUE(dictionary.get<pdf1_0::IndirectReference>(std::string("key1")).objectNumber() == 1);
   EXPECT_TRUE(dictionary.get<pdf1_0::IndirectReference>(std::string("key1")).generationNumber() == 2);
   EXPECT_TRUE(dictionary.get<pdf1_0::IndirectReference>(std::string("key2")).objectNumber() == 2);
   EXPECT_TRUE(dictionary.get<pdf1_0::IndirectReference>(std::string("key2")).generationNumber() == 3);
}

TEST(DictionaryTestSuite, dictionaryWithDictionary)
{
   pdf1_0::Dictionary dictionary1;
   pdf1_0::Dictionary dictionary2;
   dictionary2.insert<pdf1_0::IndirectReference>(pdf1_0::Name("key1"));
   dictionary2.insert<pdf1_0::IndirectReference>(pdf1_0::Name("key2"));
   dictionary1.insert(pdf1_0::Name("key3"), dictionary2);
   std::istringstream istream("<< /key3 << /key1 1 2 R /key2 2 3 R >> >>");
   EXPECT_TRUE(istream >> dictionary1);
   EXPECT_TRUE(dictionary1.get<pdf1_0::Dictionary>(std::string("key3")).get<pdf1_0::IndirectReference>(std::string("key1")).objectNumber() == 1);
   EXPECT_TRUE(dictionary1.get<pdf1_0::Dictionary>(std::string("key3")).get<pdf1_0::IndirectReference>(std::string("key1")).generationNumber() == 2);
   EXPECT_TRUE(dictionary1.get<pdf1_0::Dictionary>(std::string("key3")).get<pdf1_0::IndirectReference>(std::string("key2")).objectNumber() == 2);
   EXPECT_TRUE(dictionary1.get<pdf1_0::Dictionary>(std::string("key3")).get<pdf1_0::IndirectReference>(std::string("key2")).generationNumber() == 3);
   
   pdf1_0::Dictionary dictionary3;
   pdf1_0::Dictionary dictionary4;
   dictionary4.insert<pdf1_0::Integer>(pdf1_0::Name("Columns"));
   dictionary4.insert<pdf1_0::Integer>(pdf1_0::Name("Predictor"));
   dictionary3.insert(pdf1_0::Name("DecodeParms"), dictionary4);
   std::istringstream istream2("<</DecodeParms<</Columns 5/Predictor 12>>>>");
   EXPECT_TRUE(istream2 >> dictionary3);
}

TEST(DictionaryTestSuite, dictionaryWithHexStringArray)
{
   pdf1_0::Dictionary dictionary1;
   dictionary1.insert<pdf1_0::Array<pdf1_0::HexString>>(pdf1_0::Name("ID"));
   std::istringstream istream1("<< /ID [ < 81b14aafa313db63dbd6f981e49f94f4 > < 81b14aafa313db63dbd6f981e49f94f4 > ] >>");
   EXPECT_TRUE(istream1 >> dictionary1);
   EXPECT_TRUE(dictionary1.get<pdf1_0::Array<pdf1_0::HexString>>(std::string("ID")).size() == 2);
  
  pdf1_0::Dictionary dictionary2;
  dictionary2.insert<pdf1_0::Integer>(pdf1_0::Name("Size"));
  dictionary2.insert<pdf1_0::Integer>(pdf1_0::Name("Prev"));
  dictionary2.insert<pdf1_0::IndirectReference>(pdf1_0::Name("Root"));
  dictionary2.insert<pdf1_0::IndirectReference>(pdf1_0::Name("Info"));
   dictionary2.insert<pdf1_0::Array<pdf1_0::HexString>>(pdf1_0::Name("ID"));
   std::istringstream istream2("<</Size 4963/Prev 1513589/Root 1047 0 R/Info 1045 0 R"
    "/ID[<B0DCFF11815D46D2A0723B8B6A07897C><CB01C436D5674A45A3942939551EB0ED>]>>");
   EXPECT_TRUE(istream2 >> dictionary2);
  EXPECT_EQ(4963, dictionary2.get<pdf1_0::Integer>(pdf1_0::Name("Size")));
  EXPECT_TRUE(dictionary2.contains(pdf1_0::Name("Prev")));
  EXPECT_EQ(1513589, dictionary2.get<pdf1_0::Integer>(pdf1_0::Name("Prev")));
   EXPECT_TRUE(dictionary2.get<pdf1_0::Array<pdf1_0::HexString>>(std::string("ID")).size() == 2);
}

TEST(DictionaryTestSuite, dictionaryWithIndirectReferenceAndInteger)
{
   pdf1_0::Dictionary dictionary;
   dictionary.insert<pdf1_0::IndirectReference>(pdf1_0::Name("Info"));
   dictionary.insert<pdf1_0::Integer>(pdf1_0::Name("Length"));
   std::istringstream istream("<</Info 8453 0 R/Length 135>>");
   EXPECT_TRUE(istream >> dictionary);
}

TEST(DictionaryTestSuite, dictionaryWithUnknownKey1)
{
   pdf1_0::Dictionary dictionary;
   std::istringstream istream("<</Info 8453 0 R>>");
   EXPECT_TRUE(istream >> dictionary);
   EXPECT_TRUE(dictionary.keys().empty());
}

TEST(DictionaryTestSuite, dictionaryWithUnknownKey2)
{
   pdf1_0::Dictionary dictionary;
   std::istringstream istream(
      "<<"
      "/Type /Catalog"
      "/Pages 18 0 R"
      "/PieceInfo <<"
      "/CVPI <<"
      "/LastModified (D:20131214172321+02'00')"
      "/Private <<"
      "/Mode /Stream"
      "/Build (3.1.34)"
      ">>"
      ">>"
      ">>"
      ">>");
   EXPECT_TRUE(istream >> dictionary);
   EXPECT_TRUE(dictionary.keys().empty());
}