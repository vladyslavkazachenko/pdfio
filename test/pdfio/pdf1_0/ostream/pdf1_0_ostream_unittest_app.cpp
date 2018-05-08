#include "gtest/gtest.h"

#include "pdfio/log.h"
#include "pdfio/pdf1_0/ostream/include.h"

int main(int argc, char **argv)
{
   pdfio::gLogErrorHandler = [](const std::string &msg)
   {
      std::clog << "E\t" << msg;
   };
   pdfio::gLogWarningHandler = [](const std::string &msg)
   {
      std::clog << "W\t" << msg;
   };
   pdfio::gLogDebugHandler = [](const std::string &msg)
   {
      std::clog << "D\t" << msg;
   };
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
