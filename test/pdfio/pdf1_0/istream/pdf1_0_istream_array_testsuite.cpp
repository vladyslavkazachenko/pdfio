#include <sstream>

#include "pdfio/pdf1_0/indirect_reference.h"
#include "pdfio/pdf1_0/istream/read_hexstring.h"
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
  
  pdf1_0::Array<pdf1_0::HexString> array3;
	std::istringstream istream3("[<B0DCFF11815D46D2A0723B8B6A07897C><CB01C436D5674A45A3942939551EB0ED>]");
	EXPECT_TRUE(istream3 >> array3);
	EXPECT_EQ(2, array3.size());
	EXPECT_EQ(array3[0], "B0DCFF11815D46D2A0723B8B6A07897C");
	EXPECT_EQ(array3[1], "CB01C436D5674A45A3942939551EB0ED");
}

TEST(ArrayTestSuite, wrongContent)
{
	pdf1_0::Array<pdf1_0::IndirectReference> array;
	std::istringstream istream("[234 3 R 432 0 ]");
	EXPECT_FALSE(istream >> array);
}
