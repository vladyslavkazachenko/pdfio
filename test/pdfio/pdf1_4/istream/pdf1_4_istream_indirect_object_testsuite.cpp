#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_4/istream/read_indirect_object.h"
#include "pdfio/pdf1_4/action.h"

namespace pdf1_4 = pdfio::pdf1_4;

TEST(IndirectObjectTestSuite, action1)
{
   pdf1_4::IndirectObject indirectObject;
   indirectObject.set<pdf1_4::Action>();
   pdf1_4::Destination destination;
   std::istringstream istream(
      "629 0 obj"
      "<<"
      "/S /GoTo"
      "/D [ 630 0 R /Fit ]"
      ">>"
      "endobj"
   );
   EXPECT_TRUE(istream >> indirectObject);
   auto &action = indirectObject.get<pdf1_4::Action>();
   EXPECT_TRUE(action.s() == "GoTo");
   EXPECT_TRUE(action.hasD());
   EXPECT_EQ(pdf1_4::Action::Type::kGoTo, action.type());
   EXPECT_EQ(pdf1_4::Destination::Type::kFit, action.d().type());
   EXPECT_EQ(630, action.d().fit().page_.objectNumber());
   EXPECT_EQ(0, action.d().fit().page_.generationNumber());
}
