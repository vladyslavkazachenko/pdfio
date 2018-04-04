#include "read_name.h"

namespace pdf1_0 = pdfio::pdf1_0;

static bool isDelimiter(char ch)
{
  return std::isspace(ch) || ch == '[';
}

std::istream &operator>>(std::istream &istream, pdf1_0::Name &name)
{
  char slash = 0;
  if(istream >> slash)
  {
    if(slash != '/')
    {
      istream.setstate(std::ios_base::failbit);
    }
    else
    {
      std::string buffer;
      while(istream && !isDelimiter(istream.peek()))
      {
        auto ch = istream.get();
        if(istream)
        {
          buffer += ch;
        }
      }
      if(istream.eof())
      {
        istream.clear();
      }
      if(istream)
      {
        name = buffer;
      }
    }
  }
  return istream;
}