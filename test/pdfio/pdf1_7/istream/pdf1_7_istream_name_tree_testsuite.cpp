#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_7/istream/read_name_tree.h"

namespace pdf1_7 = pdfio::pdf1_7;

TEST(NameTreeTestSuite, emptyStream)
{
  /*pdf1_7::NameTree nameTree;
  std::istringstream istream;
  EXPECT_FALSE(istream >> nameTree);*/
}