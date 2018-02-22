#include "pdfio/pdf1_0/dictionary.h"
#include "pdfio/pdf1_0/generic_object_type.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

namespace 
{
	const std::string kNameString = "name";
	const pdf1_0::Name kName1("name1");
	const pdf1_0::Name kName2("name2");
}

TEST(DictionaryTestSuite, defaultCtor)
{
	pdf1_0::Dictionary dictionary;
	EXPECT_FALSE(dictionary.contains(kNameString));
	EXPECT_FALSE(dictionary.contains(kName1));
	EXPECT_TRUE(dictionary.keys().empty());
}

TEST(DictionaryTestSuite, insertName)
{
	pdf1_0::Dictionary dictionary;
	dictionary.insert(kName1, kName2);
	EXPECT_TRUE(dictionary.contains(kName1));
	EXPECT_TRUE(kName2 == dictionary.get<pdf1_0::Name>(kName1));
	EXPECT_EQ(1, dictionary.keys().size());
	
	dictionary.insert(kName2, kName1);
	EXPECT_TRUE(dictionary.contains(kName2));
	EXPECT_TRUE(kName1 == dictionary.get<pdf1_0::Name>(kName2));
	EXPECT_EQ(2, dictionary.keys().size());
}

TEST(DictionaryTestSuite, insertInteger)
{
	pdf1_0::Dictionary dictionary;
	pdf1_0::Integer integer;
	dictionary.insert(kName1, integer);
	EXPECT_TRUE(dictionary.contains(kName1));
	EXPECT_TRUE(integer == dictionary.get<pdf1_0::Integer>(kName1));
}

TEST(DictionaryTestSuite, insertIndirectReference)
{
	pdf1_0::Dictionary dictionary;
	pdf1_0::IndirectReference indirectReference;
	dictionary.insert(kName1, indirectReference);
	EXPECT_TRUE(dictionary.contains(kName1));
	EXPECT_EQ(indirectReference, dictionary.get<pdf1_0::IndirectReference>(kName1));
}

TEST(DictionaryTestSuite, insertDictionary)
{
	pdf1_0::Dictionary dictionary1;
	pdf1_0::Dictionary dictionary2;
	dictionary1.insert(kName1, dictionary2);
	EXPECT_TRUE(dictionary1.contains(kName1));
	EXPECT_EQ(dictionary2, dictionary1.get<pdf1_0::Dictionary>(kName1));
}

TEST(DictionaryTestSuite, remove)
{
	pdf1_0::Dictionary dictionary;
	pdf1_0::IndirectReference indirectReference;
	dictionary.insert(kName1, indirectReference);
	dictionary.remove(kName1);
	EXPECT_FALSE(dictionary.contains(kName1));
	EXPECT_TRUE(dictionary.keys().empty());
}