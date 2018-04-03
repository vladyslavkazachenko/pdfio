#include "pdfio/pdf1_0/stream.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(StreamTestSuite, defaultCtor)
{
	pdf1_0::Stream stream;
	EXPECT_TRUE(stream.length() == 0);
	char buffer[256];
	EXPECT_FALSE(stream.iostream().getline(buffer, 256));
	EXPECT_EQ(0, stream.iostream().gcount());
}

TEST(StreamTestSuite, assingment)
{
	pdf1_0::Stream stream;
	stream.length() = 10;
	EXPECT_TRUE(stream << "whatever");
	EXPECT_TRUE(stream.length() == 10);
	char buffer[256];
	EXPECT_TRUE(stream.iostream().getline(buffer, 256));
	EXPECT_EQ(8, stream.iostream().gcount());
	EXPECT_TRUE(std::string(buffer) == "whatever");
}