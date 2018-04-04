#include "gtest/gtest.h"

#include "pdfio/log.h"

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