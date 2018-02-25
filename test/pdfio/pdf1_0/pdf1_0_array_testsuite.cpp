#include "pdfio/pdf1_0/array.h"
#include "pdfio/pdf1_0/indirect_reference.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(ArrayTestSuite, defaultCtor)
{
	pdf1_0::Array<pdf1_0::IndirectReference> array;
	EXPECT_TRUE(array.empty());
	EXPECT_EQ(0, array.size());
}

TEST(ArrayTestSuite, ctor)
{
	pdf1_0::Array<pdf1_0::IndirectReference> array(5);
	EXPECT_FALSE(array.empty());
	EXPECT_EQ(5, array.size());
	for(std::size_t i = 0; i < array.size(); ++i)
	{
		EXPECT_TRUE(array[i].objectNumber() == 0ll);
		EXPECT_TRUE(array[i].generationNumber() == 0ll);
	}
}

TEST(ArrayTestSuite, assignment)
{
	pdf1_0::Array<pdf1_0::IndirectReference> array(1);
	array[0].objectNumber() = 45ll;
	array[0].generationNumber() = 1ll;
	EXPECT_TRUE(array[0].objectNumber() == 45ll);
	EXPECT_TRUE(array[0].generationNumber() == 1ll);
}

TEST(ArrayTestSuite, resize)
{
	pdf1_0::Array<pdf1_0::IndirectReference> array;
	array.resize(1);
	EXPECT_FALSE(array.empty());
	EXPECT_EQ(1, array.size());
	array[0].objectNumber() = 45ll;
	array[0].generationNumber() = 1ll;
	EXPECT_TRUE(array[0].objectNumber() == 45ll);
	EXPECT_TRUE(array[0].generationNumber() == 1ll);
}