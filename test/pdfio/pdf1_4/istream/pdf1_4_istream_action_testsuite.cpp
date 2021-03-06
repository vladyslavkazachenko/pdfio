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
   EXPECT_TRUE(action.s() == "GoTo");
   EXPECT_TRUE(action.hasD());
   EXPECT_EQ(pdf1_4::Action::Type::kGoTo, action.type());
   EXPECT_EQ(pdf1_4::Destination::Type::kFit, action.d().type());
   EXPECT_EQ(630, action.d().fit().page_.objectNumber());
   EXPECT_EQ(0, action.d().fit().page_.generationNumber());
}
