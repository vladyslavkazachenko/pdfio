#include <sstream>

#include "pdfio/pdf1_0/istream/read_indirect_object.h"
#include "pdfio/pdf1_0/generic_object_type.h"
#include "gtest/gtest.h"

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
	EXPECT_TRUE(indirectObject2.objectNumber() == 23);
	EXPECT_TRUE(indirectObject2.generationNumber() == 1);
	EXPECT_TRUE(indirectObject2.get<pdf1_0::IndirectReference>().objectNumber() == 543);
	EXPECT_TRUE(indirectObject2.get<pdf1_0::IndirectReference>().generationNumber() == 3);
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
	EXPECT_TRUE(indirectObject2.objectNumber() == 23);
	EXPECT_TRUE(indirectObject2.generationNumber() == 1);
	EXPECT_TRUE(indirectObject2.get<pdf1_0::Dictionary>().get<pdf1_0::Name>(pdf1_0::Name("key")) == "value");
}