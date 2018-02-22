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
	EXPECT_TRUE(dictionary.get<pdf1_0::Integer>(std::string("key")) == 12345ll);
}

TEST(DictionaryTestSuite, dictionaryWith2Integers)
{
	pdf1_0::Dictionary dictionary;
	dictionary.insert<pdf1_0::Integer>(pdf1_0::Name("key1"));
	dictionary.insert<pdf1_0::Integer>(pdf1_0::Name("key2"));
	std::istringstream istream("<< /key1 12345 /key2 -56789>>");
	EXPECT_TRUE(istream >> dictionary);
	EXPECT_TRUE(dictionary.get<pdf1_0::Integer>(std::string("key1")) == 12345ll);
	EXPECT_TRUE(dictionary.get<pdf1_0::Integer>(std::string("key2")) == -56789ll);
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
}