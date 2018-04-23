#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_0/istream/read_info.h"


namespace pdf1_0 = pdfio::pdf1_0;

TEST(InfoTestSuite, emptyStream)
{
   pdf1_0::Info info;
   std::istringstream istream;
   EXPECT_FALSE(istream >> info);
}

TEST(InfoTestSuite, ok1)
{
   pdf1_0::Info info;
   std::istringstream istream(
      "<<"
      "/Creator (Adobe Illustrator)"
      "/CreationDate (Thursday Feb 04 08:06:03 1993)"
      "/Author (Werner Heisenberg)"
      "/Producer (Acrobat Network Distiller 1.0 for Macintosh)"
      ">>");
   EXPECT_TRUE(istream >> info);
   EXPECT_TRUE(info.creator().literalString_ == "Adobe Illustrator");
   EXPECT_TRUE(info.creationDate().literalString_ == 
      "Thursday Feb 04 08:06:03 1993");
   EXPECT_TRUE(info.author().literalString_ == "Werner Heisenberg");
   EXPECT_TRUE(info.producer().literalString_ == 
      "Acrobat Network Distiller 1.0 for Macintosh");
}
