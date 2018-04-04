#include <iostream>

#include "gtest/gtest.h"
#include "pdfio/log.h"

int main(int argc, char **argv)
{
  pdfio::gLogDebugHandler = [](const std::string &msg)
  {
    std::clog << "D\t" << msg;
  };
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}