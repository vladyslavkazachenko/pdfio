#include "gtest/gtest.h"

#include "pdfio/log.h"
#include "pdfio/pdf1_0/istream/include.h"

int main(int argc, char **argv)
{
#ifdef PDF_LOG
	pdfio::gLogDebugHandler = [](const std::string &msg)
	{
		std::clog << "D\t" << msg;
	};
	pdfio::gLogErrorHandler = [](const std::string &msg)
	{
		std::clog << "D\t" << msg;
	};
#endif 
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}