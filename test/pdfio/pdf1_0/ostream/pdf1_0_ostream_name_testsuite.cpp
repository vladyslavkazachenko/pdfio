#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_0/ostream/write_name.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(NameTestSuite, empty)
{
   pdf1_0::Name name;
   std::ostringstream ostream;
   EXPECT_TRUE(ostream << name);
   EXPECT_TRUE(ostream.str() == "/");
}

TEST(NameTestSuite, name1)
{
   pdf1_0::Name name("name1");
   std::ostringstream ostream;
   EXPECT_TRUE(ostream << name);
   EXPECT_TRUE(ostream.str() == "/name1");
}
