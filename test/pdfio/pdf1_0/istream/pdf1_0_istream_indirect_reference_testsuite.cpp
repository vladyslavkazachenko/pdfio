#include <sstream>

#include "pdfio/pdf1_0/istream/read_indirect_reference.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(IndirectReferenceTestSuite, emptyStream)
{
	pdf1_0::IndirectReference indirectReference;
	std::istringstream istream;
	EXPECT_FALSE(istream >> indirectReference);
}

TEST(IndirectReferenceTestSuite, wrongObjectNumber)
{
	pdf1_0::IndirectReference indirectReference;
	std::istringstream istream("whatever");
	EXPECT_FALSE(istream >> indirectReference);
}

TEST(IndirectReferenceTestSuite, wrongGenerationNumber)
{
	pdf1_0::IndirectReference indirectReference1;
	std::istringstream istream1("2");
	EXPECT_FALSE(istream1 >> indirectReference1);
	
	pdf1_0::IndirectReference indirectReference2;
	std::istringstream istream2("2 whatever R");
	EXPECT_FALSE(istream2 >> indirectReference2);
}

TEST(IndirectReferenceTestSuite, wrongReference)
{
	pdf1_0::IndirectReference indirectReference1;
	std::istringstream istream1("2 1");
	EXPECT_FALSE(istream1 >> indirectReference1);
	
	pdf1_0::IndirectReference indirectReference2;
	std::istringstream istream2("2 1 r");
	EXPECT_FALSE(istream2 >> indirectReference2);
}

TEST(IndirectReferenceTestSuite, ok)
{
	pdf1_0::IndirectReference indirectReference1;
	std::istringstream istream1("2 1 R");
	EXPECT_TRUE(istream1 >> indirectReference1);
	EXPECT_EQ(2, indirectReference1.objectNumber());
	EXPECT_EQ(1, indirectReference1.generationNumber());
	
	pdf1_0::IndirectReference indirectReference2;
	std::istringstream istream2("45 2 R");
	EXPECT_TRUE(istream2 >> indirectReference2);
	EXPECT_EQ(45, indirectReference2.objectNumber());
	EXPECT_EQ(2, indirectReference2.generationNumber());
	
	pdf1_0::IndirectReference indirectReference3;
	std::istringstream istream3("8453 0 R/Length");
	EXPECT_TRUE(istream3 >> indirectReference3);
	EXPECT_EQ(8453, indirectReference3.objectNumber());
	EXPECT_EQ(0, indirectReference3.generationNumber());
}