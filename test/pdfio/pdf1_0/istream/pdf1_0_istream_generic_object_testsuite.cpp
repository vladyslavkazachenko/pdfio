#include <sstream>

#include "pdfio/pdf1_0/istream/read_generic_object.h"
#include "pdfio/pdf1_0/name.h"
#include "gtest/gtest.h"

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
	pdf1_0::GenericObject &object = name;
	std::istringstream istream("/name");
	EXPECT_TRUE(istream >> name);
	EXPECT_TRUE(name.object_ == std::string("name"));
}