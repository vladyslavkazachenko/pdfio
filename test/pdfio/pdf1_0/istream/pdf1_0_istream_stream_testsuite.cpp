#include <sstream>

#include "pdfio/pdf1_0/istream/read_stream.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(StreamTestSuite, emptyStream)
{
   pdf1_0::Stream pdfStream;
   std::istringstream istream;
   EXPECT_FALSE(istream >> pdfStream);
}

TEST(StreamTestSuite, wrongDictionary)
{
   pdf1_0::Stream pdfStream;
   std::istringstream istream("<< >>");
   EXPECT_FALSE(istream >> pdfStream);
}

TEST(StreamTestSuite, wrongStream1stDelimiter)
{
   pdf1_0::Stream pdfStream1;
   std::istringstream istream1("<< /Length 0 >>");
   EXPECT_FALSE(istream1 >> pdfStream1);
   
   pdf1_0::Stream pdfStream2;
   std::istringstream istream2("<< /Length 0 >> whatever");
   EXPECT_FALSE(istream2 >> pdfStream2);
   
   pdf1_0::Stream pdfStream3;
   std::istringstream istream3("<< /Length 0 >> stream");
   EXPECT_FALSE(istream3 >> pdfStream3);
}

TEST(StreamTestSuite, emptyPDFStream)
{
   pdf1_0::Stream pdfStream1;
   std::istringstream istream1("<< /Length 0 >> stream\nendstream");
   EXPECT_TRUE(istream1 >> pdfStream1);
   EXPECT_TRUE(pdfStream1.data() == "");
   
   pdf1_0::Stream pdfStream2;
   std::istringstream istream2("<< /Length 0 >> stream\r\nendstream");
   EXPECT_TRUE(istream2 >> pdfStream2);
   EXPECT_TRUE(pdfStream2.data() == "");
}

TEST(StreamTestSuite, wrongStream2ndDelimiter)
{
   pdf1_0::Stream pdfStream;
   std::istringstream istream("<< /Length 0 >> stream\nwhatever");
   EXPECT_FALSE(istream >> pdfStream);
}

TEST(StreamTestSuite, wrongLength)
{
   pdf1_0::Stream pdfStream;
   std::istringstream istream(
      "<< /Length 7 >> stream\nwhatever\nendstream");
   EXPECT_FALSE(istream >> pdfStream);
}

TEST(StreamTestSuite, ok)
{
   pdf1_0::Stream pdfStream;
   std::istringstream istream(
      "<< /Length 9 >> stream\nwhatever\nendstream");
   EXPECT_TRUE(istream >> pdfStream);
   std::stringstream ss(pdfStream.data());
   std::string buffer;
   ss >> buffer;
   EXPECT_TRUE(buffer == "whatever");
}
