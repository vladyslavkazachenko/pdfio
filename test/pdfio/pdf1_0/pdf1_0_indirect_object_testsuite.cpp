#include "pdfio/pdf1_0/indirect_object.h"
#include "pdfio/pdf1_0/generic_object_type.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(IndirectObjectTestSuite, defaultCtor)
{
	pdf1_0::IndirectObject indirectObject;
	EXPECT_TRUE(indirectObject.objectNumber() == 0);
	EXPECT_TRUE(indirectObject.generationNumber() == 0);
}

TEST(IndirectObjectTestSuite, assignment)
{
	pdf1_0::IndirectObject indirectObject;
	indirectObject.objectNumber() = 10;
	indirectObject.generationNumber() = 1;
	EXPECT_TRUE(indirectObject.objectNumber() == 10);
	EXPECT_TRUE(indirectObject.generationNumber() == 1);
}

TEST(IndirectObjectTestSuite, setInteger)
{
	pdf1_0::IndirectObject indirectObject;
	indirectObject.set(pdf1_0::Integer(23));
	EXPECT_TRUE(indirectObject.get<pdf1_0::Integer>() == 23);
	EXPECT_EQ(static_cast<int>(pdf1_0::GenericObjectType::kInteger), indirectObject.get().typeId_);
}

TEST(IndirectObjectTestSuite, setName)
{
	pdf1_0::IndirectObject indirectObject;
	indirectObject.set(pdf1_0::Name("name"));
	EXPECT_TRUE(indirectObject.get<pdf1_0::Name>() == "name");
	EXPECT_EQ(static_cast<int>(pdf1_0::GenericObjectType::kName), indirectObject.get().typeId_);
}

TEST(IndirectObjectTestSuite, indirectReference)
{
	pdf1_0::IndirectObject indirectObject;
	indirectObject.set(pdf1_0::IndirectReference(23, 2));
	EXPECT_TRUE(indirectObject.get<pdf1_0::IndirectReference>().objectNumber() == 23);
	EXPECT_TRUE(indirectObject.get<pdf1_0::IndirectReference>().generationNumber() == 2);
	EXPECT_EQ(static_cast<int>(pdf1_0::GenericObjectType::kIndirectReference), indirectObject.get().typeId_);
}

TEST(IndirectObjectTestSuite, setDictionary)
{
	pdf1_0::IndirectObject indirectObject;
	pdf1_0::Dictionary dictionary;
	dictionary.insert(pdf1_0::Name("key1"), pdf1_0::Integer(56));
	dictionary.insert(pdf1_0::Name("key2"), pdf1_0::Name("value2"));
	indirectObject.set(dictionary);
	EXPECT_TRUE(indirectObject.get<pdf1_0::Dictionary>().get<pdf1_0::Integer>(pdf1_0::Name("key1")) == 56);
	EXPECT_TRUE(indirectObject.get<pdf1_0::Dictionary>().get<pdf1_0::Name>(pdf1_0::Name("key2")) == "value2");
	EXPECT_EQ(static_cast<int>(pdf1_0::GenericObjectType::kDictionary), indirectObject.get().typeId_);
}