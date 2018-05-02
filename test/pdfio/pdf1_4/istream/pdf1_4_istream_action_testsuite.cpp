#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_4/istream/read_action.h"

namespace pdf1_4 = pdfio::pdf1_4;

TEST(ActionTestSuite, goto1)
{
   pdf1_4::Action action;
   std::istringstream istream(
      "<<"
      "/S /GoTo"
      "/D [ 630 0 R /Fit ]"
      ">>"
   );
   EXPECT_TRUE(istream >> action);
   EXPECT_EQ(pdf1_4::Action::Type::kGoTo, action.type());
}
