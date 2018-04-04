#include <sstream>

#include "gtest/gtest.h"
#include "pdfio/pdf1_0/istream/read_literalstring.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(LiteralStringTestSuite, emptyStream)
{
	pdf1_0::LiteralString literalString;
	std::istringstream istream;
	EXPECT_FALSE(istream >> literalString);
}

TEST(LiteralStringTestSuite, ok)
{
	pdf1_0::LiteralString literalString1;
	std::istringstream istream1("(This is a string)");
	EXPECT_TRUE(istream1 >> literalString1);
	EXPECT_TRUE(literalString1 == "This is a string");
	
	pdf1_0::LiteralString literalString2;
	std::istringstream istream2("( This is a string )");
	EXPECT_TRUE(istream2 >> literalString2);
	EXPECT_TRUE(literalString2 == " This is a string ");
	
	pdf1_0::LiteralString literalString3;
	std::istringstream istream3("( This is a string)");
	EXPECT_TRUE(istream3 >> literalString3);
	EXPECT_TRUE(literalString3 == " This is a string");
	
	pdf1_0::LiteralString literalString4;
	std::istringstream istream4("(This is a string )");
	EXPECT_TRUE(istream4 >> literalString4);
	EXPECT_TRUE(literalString4 == "This is a string ");
	
	pdf1_0::LiteralString literalString5;
	std::istringstream istream5("( Strings may contain newlines\n"
		"and such . )");
	EXPECT_TRUE(istream5 >> literalString5);
	EXPECT_TRUE(literalString5 == " Strings may contain newlines\nand such . ");
	
	pdf1_0::LiteralString literalString6;
	std::istringstream istream6("( Strings may contain balanced parentheses ( ) and\r\n"
		"special characters ( * ! & } ^ % and so on ) . )");
	EXPECT_TRUE(istream6 >> literalString6);
	EXPECT_TRUE(literalString6 == " Strings may contain balanced parentheses ( ) and\r\n"
		"special characters ( * ! & } ^ % and so on ) . ");
		
	pdf1_0::LiteralString literalString7;
	std::istringstream istream7("()");
	EXPECT_TRUE(istream7 >> literalString7);
	EXPECT_TRUE(literalString7 == "");
	
	pdf1_0::LiteralString literalString8;
	std::istringstream istream8("( It has zero ( 0 ) length . )");
	EXPECT_TRUE(istream8 >> literalString8);
	EXPECT_TRUE(literalString8 == " It has zero ( 0 ) length . ");
}