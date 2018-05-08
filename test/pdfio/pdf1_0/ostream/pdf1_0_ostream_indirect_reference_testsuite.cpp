#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_0/ostream/write_indirect_reference.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(IndirectReferenceTestSuite, test1)
{
   pdf1_0::IndirectReference indirRef;
   std::ostringstream ostream;
   EXPECT_TRUE(ostream << indirRef);
   EXPECT_TRUE(ostream.str() == "0 0 R");
}

TEST(IndirectReferenceTestSuite, test2)
{
   pdf1_0::IndirectReference indirRef;
   indirRef.objectNumber() = 123;
   indirRef.generationNumber() = 1;
   std::ostringstream ostream;
   EXPECT_TRUE(ostream << indirRef);
   EXPECT_TRUE(ostream.str() == "123 1 R");
}
