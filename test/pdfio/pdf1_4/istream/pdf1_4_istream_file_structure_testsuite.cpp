#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_4/istream/read_file_structure.h"

namespace pdf1_4 = pdfio::pdf1_4;

TEST(FileStructureTestSuite, trailer1)
{
  pdf1_4::FileStructure::Trailer trailer;
  std::istringstream istream(
    "trailer\n"
    "<< /Size 22"
    "/Root 2 0 R"
    "/Info 1 0 R"
    "/ID [ < 81b14aafa313db63dbd6f981e49f94f4 >"
    "< 81b14aafa313db63dbd6f981e49f94f4 >"
    "]"
    ">>"
    "startxref\n"
    "18799\n"
    "%%EOF"
  );
  EXPECT_TRUE(istream >> trailer);
  EXPECT_EQ(22, trailer.size());
  EXPECT_TRUE(trailer.hasRoot());
  EXPECT_EQ(2, trailer.root().objectNumber());
  EXPECT_EQ(0, trailer.root().generationNumber());
  EXPECT_TRUE(trailer.hasInfo());
  EXPECT_EQ(1, trailer.info().objectNumber());
  EXPECT_EQ(0, trailer.info().generationNumber());
  EXPECT_TRUE(trailer.hasId());
  EXPECT_EQ(2, trailer.id().size());
  EXPECT_TRUE(trailer.id()[0] == "81b14aafa313db63dbd6f981e49f94f4");
  EXPECT_TRUE(trailer.id()[1] == "81b14aafa313db63dbd6f981e49f94f4");
}
