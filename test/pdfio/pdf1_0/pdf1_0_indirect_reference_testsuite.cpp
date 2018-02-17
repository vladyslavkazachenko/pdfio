#include "pdfio/pdf1_0/indirect_reference.h"
#include "gtest/gtest.h"

namespace 
{
	const int kDefaultObjectNumber = 0;
	const int kDefaultGenerationNumber = 0;
	const int kObjectNumber = 12;
	const int kGenerationNumber = 2;
}

namespace pdf1_0 = pdfio::pdf1_0;

TEST(IndirectReferenceTestSuite, defaultCtor)
{
	pdf1_0::IndirectReference indirectReference;
	EXPECT_EQ(kDefaultObjectNumber, indirectReference.objectNumber());
	EXPECT_EQ(kDefaultGenerationNumber, indirectReference.generationNumber());
}

TEST(IndirectReferenceTestSuite, ctor)
{
	pdf1_0::IndirectReference indirectReference(kObjectNumber, kGenerationNumber);
	EXPECT_EQ(kObjectNumber, indirectReference.objectNumber());
	EXPECT_EQ(kGenerationNumber, indirectReference.generationNumber());
}

TEST(IndirectReferenceTestSuite, copyCtor)
{
	pdf1_0::IndirectReference indirectReference1(kObjectNumber, kGenerationNumber);
	pdf1_0::IndirectReference indirectReference2(indirectReference1);
	EXPECT_EQ(kObjectNumber, indirectReference2.objectNumber());
	EXPECT_EQ(kGenerationNumber, indirectReference2.generationNumber());
	
	pdf1_0::IndirectReference indirectReference3 = indirectReference1;
	EXPECT_EQ(kObjectNumber, indirectReference3.objectNumber());
	EXPECT_EQ(kGenerationNumber, indirectReference3.generationNumber());
}

TEST(IndirectReferenceTestSuite, assignment)
{
	pdf1_0::IndirectReference indirectReference1(kObjectNumber, kGenerationNumber);
	pdf1_0::IndirectReference indirectReference2;
	indirectReference2 = indirectReference1;
	EXPECT_EQ(kObjectNumber, indirectReference2.objectNumber());
	EXPECT_EQ(kGenerationNumber, indirectReference2.generationNumber());
	
	indirectReference2.objectNumber() = kGenerationNumber;
	indirectReference2.generationNumber() = kObjectNumber;
	EXPECT_EQ(kGenerationNumber, indirectReference2.objectNumber());
	EXPECT_EQ(kObjectNumber, indirectReference2.generationNumber());
}

TEST(IndirectReferenceTestSuite, comparation)
{
	pdf1_0::IndirectReference indirectReference1(kObjectNumber, kGenerationNumber);
	pdf1_0::IndirectReference indirectReference2(kObjectNumber, kGenerationNumber);
	pdf1_0::IndirectReference indirectReference3;
	EXPECT_TRUE(indirectReference1 == indirectReference2);
	EXPECT_FALSE(indirectReference1 == indirectReference3);
	EXPECT_FALSE(indirectReference2 == indirectReference3);
}