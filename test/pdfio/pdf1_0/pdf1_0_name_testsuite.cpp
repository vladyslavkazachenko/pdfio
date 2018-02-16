#include "pdfio/pdf1_0/name.h"
#include "gtest/gtest.h"

namespace 
{
	const std::string nameValue = "name";
}

namespace pdf1_0 = pdfio::pdf1_0;

TEST(NameTestSuite, defaultCtor)
{
	pdf1_0::Name name;
	EXPECT_TRUE(name == "");
}

TEST(NameTestSuite, ctor)
{
	pdf1_0::Name name(nameValue);
	EXPECT_TRUE(name == nameValue);
	EXPECT_FALSE(name == "");
}

TEST(NameTestSuite, copyCtor)
{
	pdf1_0::Name name1(nameValue);
	pdf1_0::Name name2(name1);
	EXPECT_TRUE(name2 == nameValue);
	
	pdf1_0::Name name3 = name1;
	EXPECT_TRUE(name3 == nameValue);
}

TEST(NameTestSuite, assignment)
{
	pdf1_0::Name name1;
	name1 = nameValue;
	EXPECT_TRUE(name1 == nameValue);
	
	pdf1_0::Name name2;
	name2 = name1;
	EXPECT_TRUE(name2 == nameValue);
	EXPECT_TRUE(name1 == name2);
}