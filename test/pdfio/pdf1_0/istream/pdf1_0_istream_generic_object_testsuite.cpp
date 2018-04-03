#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_0/istream/read_generic_object.h"
#include "pdfio/pdf1_0/name.h"
#include "pdfio/pdf1_0/real.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(GenericObjectTestSuite, unknownType)
{
  pdf1_0::GenericObject object(-1);
  std::istringstream istream;
  EXPECT_FALSE(istream >> object);
}

TEST(GenericObjectTestSuite, name)
{
  pdf1_0::GenericObjectAdaptor<pdf1_0::Name> name{pdf1_0::Name()};
  std::istringstream istream("/name");
  EXPECT_TRUE(istream >> name);
  EXPECT_TRUE(name.object_ == std::string("name"));
}

TEST(GenericObjectTestSuite, real)
{
  pdf1_0::GenericObjectAdaptor<pdf1_0::Real> real{pdf1_0::Real()};
  pdf1_0::GenericObject &genericObject = real;
  std::istringstream istream("-.002");
  EXPECT_TRUE(istream >> genericObject);
  EXPECT_EQ(-.002, real.object_);
}