#include <sstream>

#include "pdfio/pdf1_0/indirect_reference.h"
#include "pdfio/pdf1_0/istream/read_array.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(ArrayTestSuite, emptyStream)
{
	pdf1_0::Array<pdf1_0::IndirectReference> array;
	std::istringstream istream;
	EXPECT_FALSE(istream >> array);
}

TEST(ArrayTestSuite, simpleArray)
{
	pdf1_0::Array<pdf1_0::IndirectReference> array1;
	std::istringstream istream1("[ 234 3 R ]");
	EXPECT_TRUE(istream1 >> array1);
	EXPECT_EQ(1, array1.size());
	EXPECT_TRUE(array1[0].objectNumber() == 234);
	EXPECT_TRUE(array1[0].generationNumber() == 3);
	
	pdf1_0::Array<pdf1_0::IndirectReference> array2;
	std::istringstream istream2("[ 234 3 R 432 0 R ]");
	EXPECT_TRUE(istream2 >> array2);
	EXPECT_EQ(2, array2.size());
	EXPECT_TRUE(array2[0].objectNumber() == 234);
	EXPECT_TRUE(array2[0].generationNumber() == 3);
	EXPECT_TRUE(array2[1].objectNumber() == 432);
	EXPECT_TRUE(array2[1].generationNumber() == 0);
}

TEST(ArrayTestSuite, wrong1stDelimiter)
{
	pdf1_0::Array<pdf1_0::IndirectReference> array;
	std::istringstream istream("[234 3 R 432 0 R ]");
	EXPECT_FALSE(istream >> array);
}

TEST(ArrayTestSuite, wrong2ndDelimiter)
{
	pdf1_0::Array<pdf1_0::IndirectReference> array1;
	std::istringstream istream1("[ 234 3 R 432 0 R");
	EXPECT_FALSE(istream1 >> array1);
	
	pdf1_0::Array<pdf1_0::IndirectReference> array2;
	std::istringstream istream2("[ 234 3 R 432 0 R ]]");
	EXPECT_FALSE(istream2 >> array2);
}

TEST(ArrayTestSuite, wrongContent)
{
	pdf1_0::Array<pdf1_0::IndirectReference> array;
	std::istringstream istream("[234 3 R 432 0 ]");
	EXPECT_FALSE(istream >> array);
}