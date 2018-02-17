#include <sstream>

#include "pdfio/pdf1_0/istream/read_name.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(NameTestSuite, emptyStream)
{
	pdf1_0::Name name;
	std::istringstream istream;
	EXPECT_FALSE(istream >> name);
}

TEST(NameTestSuite, emptyName)
{
	pdf1_0::Name name;
	std::istringstream istream("/");
	EXPECT_TRUE(istream >> name);
	EXPECT_TRUE(name == "");
}

TEST(NameTestSuite, simpleName)
{
	pdf1_0::Name name1;
	std::istringstream istream1("/name1");
	EXPECT_TRUE(istream1 >> name1);
	EXPECT_TRUE(name1 == "name1");
	
	pdf1_0::Name name2;
	std::istringstream istream2("/name2  /name3");
	EXPECT_TRUE(istream2 >> name2);
	EXPECT_TRUE(name2 == "name2");
}

TEST(NameTestSuite, wrongName)
{
	pdf1_0::Name name1;
	std::istringstream istream1("name1");
	EXPECT_FALSE(istream1 >> name1);
	
	pdf1_0::Name name2;
	std::istringstream istream2(" /name2");
	EXPECT_FALSE(istream2 >> name2);
}