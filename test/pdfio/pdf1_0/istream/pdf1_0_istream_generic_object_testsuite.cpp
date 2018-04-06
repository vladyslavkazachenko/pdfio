#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_0/name.h"
#include "pdfio/pdf1_0/real.h"
#include "pdfio/read_generic_object.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(GenericObjectTestSuite, name)
{
  pdfio::GenericObjectAdaptor<pdf1_0::Name> name{pdf1_0::Name()};
  std::istringstream istream("/name");
  EXPECT_TRUE(istream >> name);
  EXPECT_TRUE(name.object_ == std::string("name"));
}

TEST(GenericObjectTestSuite, real)
{
  pdfio::GenericObjectAdaptor<pdf1_0::Real> real{pdf1_0::Real()};
  pdfio::GenericObject &genericObject = real;
  std::istringstream istream("-.002");
  EXPECT_TRUE(istream >> genericObject);
  EXPECT_EQ(-.002, real.object_);
}