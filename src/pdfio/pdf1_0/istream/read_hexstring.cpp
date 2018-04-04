#include "read_hexstring.h"

namespace pdf1_0 = pdfio::pdf1_0;

std::istream &operator>>(std::istream &istream, pdf1_0::HexString &hexstring)
{
  char ch;
  if(istream >> ch)
  {
    if(ch == '<')
    {
      while(istream && std::isspace(istream.peek()))
      {
        static_cast<void>(istream.get());
      }
      std::string s;
      while(istream && std::isxdigit(istream.peek()))
      {
        s += istream.get();
      }
      if(istream)
      {
        if(istream >> ch)
        {
          if(ch == '>')
          {
            hexstring = s;
          }
          else
          {
            istream.setstate(std::ios_base::failbit);
          }
        }
      }
    }
    else
    {
      istream.setstate(std::ios_base::failbit);
    }
  }
	return istream;
}