#include "gtest/gtest.h"
#include "pdfio/pdf1_7/array.h"
#include "pdfio/pdf1_7/hexstring.h"

namespace pdf1_7 = pdfio::pdf1_7;

TEST(ArrayTestSuite, defaultCtor)
{
   pdf1_7::Array<pdf1_7::HexString> array;
   EXPECT_TRUE(array.empty());
   EXPECT_EQ(0, array.size());
}

TEST(ArrayTestSuite, ctor)
{
   pdf1_7::Array<pdf1_7::HexString> array(5);
   EXPECT_FALSE(array.empty());
   EXPECT_EQ(5, array.size());
   for(std::size_t i = 0; i < array.size(); ++i)
   {
      EXPECT_TRUE(array[i] == "");;
   }
}

TEST(ArrayTestSuite, assignment)
{
   pdf1_7::Array<pdf1_7::HexString> array(1);
   array[0] = "55fd";
   EXPECT_TRUE(array[0] == "55fd");
}

TEST(ArrayTestSuite, resize)
{
   pdf1_7::Array<pdf1_7::HexString> array;
   array.resize(1);
   EXPECT_FALSE(array.empty());
   EXPECT_EQ(1, array.size());
   array[0] = "55fd";
   EXPECT_TRUE(array[0] == "55fd");
}
