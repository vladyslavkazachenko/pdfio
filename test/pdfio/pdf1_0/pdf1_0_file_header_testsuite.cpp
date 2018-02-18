#include "pdfio/pdf1_0/file_header.h"
#include "gtest/gtest.h"

namespace pdf1_0 = pdfio::pdf1_0;

TEST(FileHeaderTestSuite, defaultCtor)
{
	pdf1_0::FileHeader fileHeader;
}