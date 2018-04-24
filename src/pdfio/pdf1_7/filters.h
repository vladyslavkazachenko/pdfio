#pragma once

#include <string>

namespace pdfio
{
   
namespace pdf1_7
{
   
bool FlateDecode(const char *input, std::size_t length, std::string &output);
   
}
   
}
