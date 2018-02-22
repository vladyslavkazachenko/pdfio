#include "pdfio/pdf1_0/dictionary.h"
#include "pdfio/pdf1_0/integer.h"
#include "pdfio/pdf1_0/indirect_reference.h"
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
}

TEST(DictionaryTestSuite, insertName)
{
	pdf1_0::Dictionary dictionary;
	dictionary.insert(kName1, kName2);
	EXPECT_TRUE(dictionary.contains(kName1));
	EXPECT_TRUE(kName2 == dictionary.get<pdf1_0::Name>(kName1));
	
	dictionary.insert(kName2, kName1);
	EXPECT_TRUE(dictionary.contains(kName2));
	EXPECT_TRUE(kName1 == dictionary.get<pdf1_0::Name>(kName2));
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