#include "pdfio/pdf1_0/stream.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(StreamTestSuite, defaultCtor)
{
	pdf1_0::Stream stream;
	EXPECT_TRUE(stream.length() == 0ll);
	char buffer[256];
	EXPECT_FALSE(stream.getline(buffer, 256));
	EXPECT_EQ(0, stream.gcount());
}

TEST(StreamTestSuite, assingment)
{
	pdf1_0::Stream stream;
	stream.length() = 10ll;
	EXPECT_TRUE(stream << "whatever");
	EXPECT_TRUE(stream.length() == 10ll);
	char buffer[256];
	EXPECT_TRUE(stream.getline(buffer, 256));
	EXPECT_EQ(8, stream.gcount());
	EXPECT_TRUE(std::string(buffer) == "whatever");
}