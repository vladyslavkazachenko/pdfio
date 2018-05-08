#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_0/ostream/write_dictionary.h"
#include "pdfio/pdf1_0/indirect_reference.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(DictionaryTestSuite, empty)
{
   pdf1_0::Dictionary dictionary;
   std::ostringstream ostream;
   EXPECT_TRUE(ostream << dictionary);
   EXPECT_TRUE(ostream.str() == "<<>>");
}

TEST(DictionaryTestSuite, name)
{
   pdf1_0::Dictionary dictionary;
   dictionary.insert<pdf1_0::Name>(pdf1_0::Name("key"));
   std::ostringstream ostream;
   EXPECT_TRUE(ostream << dictionary);
   EXPECT_TRUE(ostream.str() == "<</key />>");
}

TEST(DictionaryTestSuite, twoNames)
{
   pdf1_0::Dictionary dictionary;
   dictionary.insert(pdf1_0::Name("key1"), pdf1_0::Name("value1"));
   dictionary.insert(pdf1_0::Name("key2"), pdf1_0::Name("value2"));
   std::ostringstream ostream;
   EXPECT_TRUE(ostream << dictionary);
   EXPECT_TRUE(ostream.str() == "<</key1 /value1/key2 /value2>>");
}

TEST(DictionaryTestSuite, indirectReference)
{
   pdf1_0::Dictionary dictionary;
   dictionary.insert<pdf1_0::IndirectReference>(pdf1_0::Name("key"));
   std::ostringstream ostream;
   EXPECT_TRUE(ostream << dictionary);
   EXPECT_TRUE(ostream.str() == "<</key 0 0 R>>");
}

TEST(DictionaryTestSuite, twoIndirectReferences)
{
   pdf1_0::Dictionary dictionary;
   dictionary.insert(pdf1_0::Name("key1"), pdf1_0::IndirectReference(213, 1));
   dictionary.insert(pdf1_0::Name("key2"), pdf1_0::IndirectReference(313, 2));
   std::ostringstream ostream;
   EXPECT_TRUE(ostream << dictionary);
   EXPECT_TRUE(ostream.str() == "<</key1 213 1 R/key2 313 2 R>>");
}
